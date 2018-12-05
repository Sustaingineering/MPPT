#include "DSP28x_Project.h"
//
#include "adc.h"
#include "clk.h"
#include "cpu.h"
#include "gpio.h"
#include "pie.h"
#include "pwm.h"
#include "pll.h"
#include "timer.h"
#include "wdog.h"

#include "sensors.h"
#include "mppt.h"
#include "particle.h"
#include "swarm.h"


// Prototype statements for functions found within this file.
__interrupt void cpu_timer0_isr(void);
__interrupt void cpu_timer1_isr(void);
__interrupt void adc_isr(void);

void setDutyCycle(double duty);

void InitEGpio(void);
void InitEPwm(void);
void InitSys(void);
void InitAdc(void);
void InitTimer(void);
void InitInterrupts(void);

#define SAMPLE_PERIOD0 0.5f//period for changing duty cycle interrupt
#define SAMPLE_PERIOD1 5.0f //period for global search interrupt

typedef enum {INIT, MEASURE, DONE} state;
state current_state = INIT;

uint16_t iter_count, particle_count; //keep track of iteration, and which particle being assessed
uint16_t sample_count = 0;

uint16_t voltage_in[MAX_SAMPLES];
uint16_t current_in[MAX_SAMPLES];

double voltage = 0;
double current = 0;
double power = 0;
double power_max = 0;
double power_sum = 0;

double duty = 0.0; // x 100% for duty cycle percentage

double voltage_prev = 0;
double current_prev = 0;
double power_prev = 0;

ADC_Handle myAdc;
CLK_Handle myClk;
//FLASH_Handle myFlash;
GPIO_Handle myGpio;
PIE_Handle myPie;
PWM_Handle myPwm;
TIMER_Handle myTimer0;
TIMER_Handle myTimer1;
CPU_Handle myCpu;
PLL_Handle myPll;
WDOG_Handle myWDog;

struct Swarm * s;
struct Particle * particles[NUM_PARTICLES];

/* CHANGING NUMBER OF PARTICLES
 * To change the number of particles in PSO, some modifications to the code must be made.
 * 1) Macro NUM_PARTICLES in swarm.h must be changed to however many particles desired
 * 2) More particles must be declared in main.c (see the commented out declaration line 94)
 * 3) In particle.h, change the function declaration to incorporate more particles (see commented out code)
 * 4) In particle.c, change the function definition to match declaration (see commented out code)
 * 5) In particle.c, add the switch case for the new particles (see commented out code)
 */

void main(void) {

    struct Particle p1;
    struct Particle p2;
    struct Particle p3;

    //add as many particles as required here
    //struct Particle p4;

    struct Swarm swarm;

    InitParticles(particles, NUM_PARTICLES, &p1, &p2, &p3);
    //InitParticles(particles, NUM_PARTICLES, &p1, &p2, &p3, &p4);

    s = &swarm;
    InitSwarm(s, NUM_PARTICLES, C1, C1_MIN, C2, C2_MIN, W, ITERATIONS, particles);

//    // Initialize all the handles needed for this application
    myAdc = ADC_init((void *)ADC_BASE_ADDR, sizeof(ADC_Obj));
    myClk = CLK_init((void *)CLK_BASE_ADDR, sizeof(CLK_Obj));
    myCpu = CPU_init((void *)NULL, sizeof(CPU_Obj));
    //myFlash = FLASH_init((void *)FLASH_BASE_ADDR, sizeof(FLASH_Obj));
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

    InitSys();
    InitAdc();
    InitTimer();
    InitEPwm();
    InitEGpio();
    InitInterrupts();

    for(;;)
    {
        __asm(" NOP");
    }
}

__interrupt void cpu_timer1_isr(void) {

    GPIO_toggle(myGpio, GPIO_Number_1);
    resetSwarm(s);
    current_state = INIT;
}

__interrupt void cpu_timer0_isr(void) {

    int i;

    voltage = getVoltage(voltage_in, MAX_SAMPLES);
    current = getCurrent(current_in, MAX_SAMPLES);
    power = voltage * current;
    power_sum += power;

    switch(current_state) {
        case INIT :

            iter_count = 0;
            particle_count = 0;

            current_state = MEASURE;
            duty = s->particles[particle_count]->position;
            power_sum = 0;
            break;

        case MEASURE :

            if (power > s->particles[particle_count]->position_best_power) {
                s->particles[particle_count]->position_best_power = power;
                s->particles[particle_count]->position_best = s->particles[particle_count]->position;

                if (power > s->swarm_best_power) {
                    s->swarm_best_power = power;
                    s->swarm_best = s->particles[particle_count]->position;
                }
            }

            if (particle_count < NUM_PARTICLES - 1) {
                particle_count++;
                current_state = MEASURE;
            }
            else {

                particle_count = 0;

                for (i = 0; i < NUM_PARTICLES; i++) {
                    updatePosition(s->particles[i], s);
                }

                if (iter_count < s->max_iter - 1) {

                    if (iter_count % 2 == 0)
                        sortSwarm(s, DESCENDING);
                    else
                        sortSwarm(s, ASCENDING);

                    adjustConstants(s, iter_count);

                    iter_count++;
                }

                else {

                    iter_count = 0;
                    duty = s->swarm_best;
                    current_state = DONE;
                    break;
                }
            }

            duty = s->particles[particle_count]->position;

            break;

        case DONE :

            duty = s->swarm_best;
            break;

        default :

            duty = 0.5;
            current_state = INIT;
            break;
    }

    GPIO_toggle(myGpio, GPIO_Number_0);

    if (power > power_max * 0.9) {
        power_max = power;
        GPIO_setHigh(myGpio, GPIO_Number_3);
    }
    else
        GPIO_setLow(myGpio, GPIO_Number_3);


    // Acknowledge this interrupt to receive more interrupts from group 1


    voltage_prev = voltage;
    current_prev = current;
    power_prev = power;
    //duty = 0.5;

    setDutyCycle(duty);

    PIE_clearInt(myPie, PIE_GroupNumber_1);

    return;
}

__interrupt void adc_isr(void)
{
    GPIO_toggle(myGpio, GPIO_Number_2);
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


void InitEPwm() {

    EALLOW;
    CLK_disableTbClockSync(myClk);
    EDIS;

    CLK_enablePwmClock(myClk, PWM_Number_3);

    PWM_setPeriod(myPwm, PERIOD);    // Set timer period
    PWM_setPhase(myPwm, 0x0000);   // Phase is 0
    PWM_setCount(myPwm, 0x0000);   // Clear counter

    PWM_setCounterMode(myPwm, PWM_CounterMode_UpDown);// Count up
    PWM_disableCounterLoad(myPwm);                    // Disable phase loading

    PWM_setHighSpeedClkDiv(myPwm, PWM_HspClkDiv_by_1);

    PWM_setClkDiv(myPwm, PWM_ClkDiv_by_1);

    PWM_setCmpA(myPwm, PERIOD/2);

    PWM_setActionQual_CntUp_CmpA_PwmA(myPwm, PWM_ActionQual_Set);
    PWM_setActionQual_CntDown_CmpA_PwmA(myPwm, PWM_ActionQual_Clear);

    PWM_setActionQual_CntUp_CmpA_PwmB(myPwm, PWM_ActionQual_Clear);
    PWM_setActionQual_CntDown_CmpA_PwmB(myPwm, PWM_ActionQual_Set);

    PWM_setDeadBandOutputMode(myPwm,
                          PWM_DeadBandOutputMode_EPWMxA_Rising_EPWMxB_Falling);
    PWM_setDeadBandPolarity(myPwm, PWM_DeadBandPolarity_EPWMxB_Inverted);
    PWM_setDeadBandInputMode(myPwm,
                             PWM_DeadBandInputMode_EPWMxA_Rising_and_Falling);
    PWM_setDeadBandRisingEdgeDelay(myPwm, 0);
    PWM_setDeadBandFallingEdgeDelay(myPwm, 0);

    PWM_enableSocAPulse(myPwm);
    PWM_setSocAPeriod(myPwm, PWM_SocPeriod_FirstEvent);
    PWM_setSocAPulseSrc(myPwm, PWM_SocPulseSrc_CounterEqualZero);


    EALLOW;
    CLK_enableTbClockSync(myClk);
    EDIS;

    return;
}

void InitEGpio(void) {

    EALLOW;

    GPIO_setPullUp(myGpio, GPIO_Number_4, GPIO_PullUp_Disable);
    GPIO_setPullUp(myGpio, GPIO_Number_5, GPIO_PullUp_Disable);

    GPIO_setMode(myGpio, GPIO_Number_4, GPIO_4_Mode_EPWM3A);
    GPIO_setMode(myGpio, GPIO_Number_5, GPIO_5_Mode_EPWM3B);

    // Configure GPIO 0-3 as outputs
    GPIO_setMode(myGpio, GPIO_Number_0, GPIO_0_Mode_GeneralPurpose);
    GPIO_setMode(myGpio, GPIO_Number_1, GPIO_0_Mode_GeneralPurpose);
    GPIO_setMode(myGpio, GPIO_Number_2, GPIO_0_Mode_GeneralPurpose);
    GPIO_setMode(myGpio, GPIO_Number_3, GPIO_0_Mode_GeneralPurpose);

    GPIO_setDirection(myGpio, GPIO_Number_0, GPIO_Direction_Output);
    GPIO_setDirection(myGpio, GPIO_Number_1, GPIO_Direction_Output);
    GPIO_setDirection(myGpio, GPIO_Number_2, GPIO_Direction_Output);
    GPIO_setDirection(myGpio, GPIO_Number_3, GPIO_Direction_Output);

    GPIO_setLow(myGpio, GPIO_Number_0);
    GPIO_setLow(myGpio, GPIO_Number_1);
    GPIO_setLow(myGpio, GPIO_Number_2);
    GPIO_setLow(myGpio, GPIO_Number_3);

    GPIO_toggle(myGpio, GPIO_Number_0);
    GPIO_toggle(myGpio, GPIO_Number_1);
    GPIO_toggle(myGpio, GPIO_Number_2);
    GPIO_toggle(myGpio, GPIO_Number_3);

    EDIS;

    return;
}



void InitSys(void) {

    EALLOW;

    // XCLKOUT to SYSCLKOUT ratio.  By default XCLKOUT = 1/4 SYSCLKOUT
    //SysCtrlRegs.XCLK.bit.XCLKOUTDIV=2; // Set XCLKOUT = SYSCLKOUT/1
    //SysCtrlRegs.LOSPCP.all = 0x0002;
    CLK_setLowSpdPreScaler(myClk, CLK_LowSpdPreScaler_SysClkOut_by_4);
    CLK_setClkOutPreScaler(myClk, CLK_ClkOutPreScaler_SysClkOut_by_1);

    CLK_enableAdcClock(myClk);
    CLK_enablePwmClock(myClk, PWM_Number_3);
    CLK_enableTbClockSync(myClk);
    CLK_enableCpuTimerClock(myClk, CLK_CpuTimerNumber_0);
    CLK_enableCpuTimerClock(myClk, CLK_CpuTimerNumber_1);

    // Perform basic system initialization
    WDOG_disable(myWDog);
    (*Device_cal)();

    // Select the internal oscillator 1 as the clock source
    CLK_setOscSrc(myClk, CLK_OscSrc_Internal);

    // Setup the PLL for x10 /2 which will yield 50 MHz = 10 MHz * 10 / 2
    PLL_setup(myPll, PLL_Multiplier_10, PLL_DivideSelect_ClkIn_by_2);

    EDIS;

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

