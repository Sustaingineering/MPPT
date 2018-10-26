//#############################################################################
// MPPT PWM prototype code to be run on Chorizo Board
// Maryam Baksh & Curtis Catt
// Last updated: July 4, 2018
//#############################################################################

#include "DSP28x_Project.h"     // Device Header File and Examples Include File

#include "mppt.h"
#include "sensors.h"

#include "common/include/adc.h"
#include "common/include/clk.h"
#include "common/include/flash.h"
#include "common/include/gpio.h"
#include "common/include/pie.h"
#include "common/include/pwm.h"
#include "common/include/pll.h"
#include "common/include/timer.h"
#include "common/include/wdog.h"

// Prototype statements for functions found within this file.
__interrupt void cpu_timer0_isr(void);
__interrupt void cpu_timer1_isr(void);
__interrupt void adc_isr(void);

void setDutyCycle(double);

void InitEGpio(void);
void InitEPwm(void);
void InitSys(void);
void InitAdc(void);
void InitTimer(void);
void InitInterrupts(void);

#define SAMPLE_PERIOD0 0.5f //sampling period in seconds
#define SAMPLE_PERIOD1 5.0f //sampling period in seconds

uint16_t sample_count = 1;
uint16_t search_count = 0; //for global search
uint16_t max_search_count;

uint16_t voltage_in[MAX_SAMPLES];
uint16_t current_in[MAX_SAMPLES];

double voltage = 0;
double current = 0;
double power = 0;
double power_max = 0;
double duty = 0.0; // x 100% for duty cycle percentage
double power_max_duty = 0; //duty cycle for which we find max power
double power_sum = 0;
double power_theoretical = 0;

double voltage_prev = 0;
double current_prev = 0;
double power_prev = 0;
double duty_prev = 0.0;
double delta_i = 0;
double delta_v = 0;

float duty_constant = 0.5;

int track = 1;

typedef enum {INIT, SEARCH, DONE} state;
state current_state = INIT;

ADC_Handle myAdc;
CLK_Handle myClk;
FLASH_Handle myFlash;
GPIO_Handle myGpio;
PIE_Handle myPie;
PWM_Handle myPwm;
TIMER_Handle myTimer0;
TIMER_Handle myTimer1;
CPU_Handle myCpu;
PLL_Handle myPll;
WDOG_Handle myWDog;

void main(void) {

//    // Initialize all the handles needed for this application
    myAdc = ADC_init((void *)ADC_BASE_ADDR, sizeof(ADC_Obj));
    myClk = CLK_init((void *)CLK_BASE_ADDR, sizeof(CLK_Obj));
    myCpu = CPU_init((void *)NULL, sizeof(CPU_Obj));
    myFlash = FLASH_init((void *)FLASH_BASE_ADDR, sizeof(FLASH_Obj));
    myGpio = GPIO_init((void *)GPIO_BASE_ADDR, sizeof(GPIO_Obj));
    myPie = PIE_init((void *)PIE_BASE_ADDR, sizeof(PIE_Obj));
    myPll = PLL_init((void *)PLL_BASE_ADDR, sizeof(PLL_Obj));
    myPwm = PWM_init((void *)PWM_ePWM3_BASE_ADDR, sizeof(PWM_Obj));
    myTimer0 = TIMER_init((void *)TIMER0_BASE_ADDR, sizeof(TIMER_Obj));
    myTimer1 = TIMER_init((void *)TIMER1_BASE_ADDR, sizeof(TIMER_Obj));
    myWDog = WDOG_init((void *)WDOG_BASE_ADDR, sizeof(WDOG_Obj));
//
//    // If running from flash copy RAM only functions to RAM
#ifdef _FLASH
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
#endif

    max_search_count = globalSearchCount(GLOBAL_SEARCH_DELTA);

    InitSys();
    InitAdc();
    InitTimer();
    InitEPwm();
    //InitEGpio();
    InitInterrupts();

    for(;;)
    {
        __asm(" NOP");
    }
}

__interrupt void cpu_timer1_isr(void) {

    GPIO_toggle(myGpio, GPIO_Number_1);
    current_state = INIT;

    return;
}

__interrupt void cpu_timer0_isr(void) {

    voltage = getVoltage(voltage_in, MAX_SAMPLES);
    current = getCurrent(current_in, MAX_SAMPLES);
    power = voltage * current;
    power_sum += power;

    GPIO_toggle(myGpio, GPIO_Number_0);

    switch (current_state) {

        case INIT :

            search_count = 0;
            duty = GLOBAL_SEARCH_DELTA; // reset duty cycle for a global search
            duty_prev = duty;
            power_max = 0;
            power_max_duty = 0;
            current_state = SEARCH;
            power_sum = 0;
            power_theoretical = 0;
            break;

        case SEARCH :

            if (search_count < max_search_count) {
                if ( power > power_max ) {
                    power_max = power;
                    power_max_duty = duty;
                }

                duty += GLOBAL_SEARCH_DELTA;
            }

            else {
                current_state = DONE;
                duty = power_max_duty;
                power_theoretical = power_max * SAMPLE_PERIOD1 / SAMPLE_PERIOD0;
            }

            break;

        case DONE :
            break;

        default :
            current_state = INIT;
            break;
    }

    if (track == 0) {
        duty = duty_constant;
        duty_prev = duty;
    }

    voltage_prev = voltage;
    current_prev = current;
    power_prev = power;
    duty_prev = duty;

    search_count++;

    setDutyCycle(duty);

    PIE_clearInt(myPie, PIE_GroupNumber_1); // Acknowledge this interrupt to receive more interrupts from group 1

    return;
}

__interrupt void adc_isr(void)
{

    voltage_in[sample_count] = ADC_readResult(myAdc, ADC_ResultNumber_0);
    current_in[sample_count] = ADC_readResult(myAdc, ADC_ResultNumber_1);

    // If MAX_SAMPLES conversions have been logged, start over
    if(sample_count == MAX_SAMPLES-1)
    {
        sample_count = 0;
    }
    else
    {
        sample_count++;
    }

    ADC_clearIntFlag(myAdc, ADC_IntNumber_1);
    PIE_clearInt(myPie, PIE_GroupNumber_10);

    return;
}

void
InitEPwm() {


    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    CLK_enablePwmClock(myClk, PWM_Number_3);

    EPwm3Regs.TBPRD = PERIOD;                      // Set timer period
    EPwm3Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
    EPwm3Regs.TBCTR = 0x0000;                      // Clear counter

    // Setup TBCLK
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
    EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT

    // Slow so we can observe on the scope
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Setup compare
    EPwm3Regs.CMPA.half.CMPA = PERIOD/2;

    // Set actions
    EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;              // Set PWM3A on Zero
    EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm3Regs.AQCTLB.bit.CAU = AQ_CLEAR;            // Set PWM3B on Zero
    EPwm3Regs.AQCTLB.bit.CAD = AQ_SET;

    // Active high complementary PWMs - Setup the dead band
    EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm3Regs.DBRED = 0;
    EPwm3Regs.DBFED = 0;

    PWM_enableSocAPulse(myPwm);
    PWM_setSocAPeriod(myPwm, PWM_SocPeriod_ThirdEvent);
    PWM_setSocAPulseSrc(myPwm, PWM_SocPulseSrc_CounterEqualZero);


    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

}

void
InitEGpio(void) {

    EALLOW;

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;    // Disable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;    // Disable pull-up on GPIO5 (EPWM3B)

    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B

    // Configure GPIO 0-3 as outputs
//   GPIO_setMode(myGpio, GPIO_Number_0, GPIO_0_Mode_GeneralPurpose);
//   GPIO_setMode(myGpio, GPIO_Number_1, GPIO_0_Mode_GeneralPurpose);
//   GPIO_setMode(myGpio, GPIO_Number_2, GPIO_0_Mode_GeneralPurpose);
//   GPIO_setMode(myGpio, GPIO_Number_3, GPIO_0_Mode_GeneralPurpose);
//
//   GPIO_setDirection(myGpio, GPIO_Number_0, GPIO_Direction_Output);
//   GPIO_setDirection(myGpio, GPIO_Number_1, GPIO_Direction_Output);
//   GPIO_setDirection(myGpio, GPIO_Number_2, GPIO_Direction_Output);
//   GPIO_setDirection(myGpio, GPIO_Number_3, GPIO_Direction_Output);
//
//   GPIO_setLow(myGpio, GPIO_Number_0);
//   GPIO_setLow(myGpio, GPIO_Number_1);
//   GPIO_setLow(myGpio, GPIO_Number_2);
//   GPIO_setLow(myGpio, GPIO_Number_3);
//
//   GPIO_toggle(myGpio, GPIO_Number_0);
//   GPIO_toggle(myGpio, GPIO_Number_1);
//   GPIO_toggle(myGpio, GPIO_Number_2);
//   GPIO_toggle(myGpio, GPIO_Number_3);

    EDIS;

    return;
}



void InitSys(void) {

    EALLOW;

    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 3;  // GPIO18 = XCLKOUT
    SysCtrlRegs.LOSPCP.all = 0x0002;

    // XCLKOUT to SYSCLKOUT ratio.  By default XCLKOUT = 1/4 SYSCLKOUT
    SysCtrlRegs.XCLK.bit.XCLKOUTDIV=2; // Set XCLKOUT = SYSCLKOUT/1

    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;       // ADC
    SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;     // EPWM3
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;      // Enable TBCLK within the EPWM
    SysCtrlRegs.PCLKCR3.bit.CPUTIMER0ENCLK = 1; // CPU Timer-0
    SysCtrlRegs.PCLKCR3.bit.CPUTIMER1ENCLK = 1; // CPU Timer-1

    EDIS;

    // Perform basic system initialization
    WDOG_disable(myWDog);
    CLK_enableAdcClock(myClk);
    (*Device_cal)();

    // Select the internal oscillator 1 as the clock source
    CLK_setOscSrc(myClk, CLK_OscSrc_Internal);

    // Setup the PLL for x10 /2 which will yield 50 MHz = 10 MHz * 10 / 2
    PLL_setup(myPll, PLL_Multiplier_10, PLL_DivideSelect_ClkIn_by_2);


    return;
}

void InitAdc(void) {

    //configure the ADC
    ADC_enableBandGap(myAdc);
    ADC_enableRefBuffers(myAdc);
    ADC_powerUp(myAdc);
    ADC_enable(myAdc);
    ADC_setVoltRefSrc(myAdc, ADC_VoltageRefSrc_Int);

    ADC_setIntPulseGenMode(myAdc, ADC_IntPulseGenMode_Prior);
    ADC_enableInt(myAdc, ADC_IntNumber_1);
    ADC_setIntMode(myAdc, ADC_IntNumber_1, ADC_IntMode_ClearFlag);
    ADC_setIntSrc(myAdc, ADC_IntNumber_1, ADC_IntSrc_EOC1);
    ADC_setSocChanNumber (myAdc, ADC_SocNumber_0, ADC_SocChanNumber_A6); //analog pin a6 to be used for voltage
    ADC_setSocChanNumber (myAdc, ADC_SocNumber_1, ADC_SocChanNumber_A7); //analog pin a7 to be used for current
    ADC_setSocSampleWindow(myAdc, ADC_SocNumber_0,
                           ADC_SocSampleWindow_37_cycles);
    ADC_setSocSampleWindow(myAdc, ADC_SocNumber_1,
                           ADC_SocSampleWindow_37_cycles);

    ADC_setSocTrigSrc(myAdc, ADC_SocNumber_1, ADC_SocTrigSrc_EPWM3_ADCSOCA);
    ADC_setSocTrigSrc(myAdc, ADC_SocNumber_0, ADC_SocTrigSrc_EPWM3_ADCSOCA);

    return;
}

void InitInterrupts(void) {

    //WORKS!!

    PIE_disable(myPie);
    PIE_disableAllInts(myPie);
    CPU_disableGlobalInts(myCpu);
    CPU_clearIntFlags(myCpu);


    PIE_setDebugIntVectorTable(myPie);
    PIE_enableAdcInt(myPie, ADC_IntNumber_1);
    PIE_enableTimer0Int(myPie);
    PIE_enable(myPie);

    EALLOW;  // This is needed to write to EALLOW protected registers

    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_1, PIE_SubGroupNumber_7, (intVec_t)&cpu_timer0_isr);
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_10, PIE_SubGroupNumber_1, (intVec_t)&adc_isr);
    PIE_registerSystemIntHandler(myPie, PIE_SystemInterrupts_TINT1, (intVec_t)&cpu_timer1_isr);


    EDIS;    // This is needed to disable write to EALLOW protected registers


    CPU_enableInt(myCpu, CPU_IntNumber_1);

    CPU_enableInt(myCpu, CPU_IntNumber_13);


    CPU_enableGlobalInts(myCpu); // Enable Global interrupt INTM
    CPU_enableDebugInt(myCpu); // Enable Global realtime interrupt DBGM

    CPU_enableInt(myCpu, CPU_IntNumber_10); //Enable ADC CPU int
    //WORKS \

    return;
}

void InitTimer(void) {

    // Configure CPU-Timer 0 interrupt
    TIMER_stop(myTimer0);
    TIMER_setPeriod(myTimer0, 50000000 * SAMPLE_PERIOD0);
    TIMER_setPreScaler(myTimer0, 0);
    TIMER_reload(myTimer0);
    TIMER_setEmulationMode(myTimer0, TIMER_EmulationMode_StopAfterNextDecrement);
    TIMER_enableInt(myTimer0);

    TIMER_stop(myTimer1);
    TIMER_setPeriod(myTimer1, 50000000 * SAMPLE_PERIOD1);
    TIMER_setPreScaler(myTimer1, 0);
    TIMER_reload(myTimer1);
    TIMER_setEmulationMode(myTimer1, TIMER_EmulationMode_StopAfterNextDecrement);
    TIMER_enableInt(myTimer1);

    TIMER_start(myTimer0);
    TIMER_start(myTimer1);
    return;
}

void setDutyCycle(double duty) {

    if (duty >= DUTY_MAX)
        PWM_setCmpA(myPwm, convertDuty(DUTY_MAX));
    else if (duty <= DUTY_MIN)
        PWM_setCmpA(myPwm, convertDuty(DUTY_MIN));
    else
        PWM_setCmpA(myPwm, convertDuty(duty));

    return;
}

