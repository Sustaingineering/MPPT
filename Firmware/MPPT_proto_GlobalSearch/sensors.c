/*
 * sensors.c
 *
 *  Created on: Jul 19, 2018
 *      Author: ccatt.stu
 */

#include "sensors.h"

extern uint16_t voltage_in[MAX_SAMPLES];
extern uint16_t current_in[MAX_SAMPLES];

double getVoltage(uint16_t voltage_in[MAX_SAMPLES], uint16_t readings) {

    double tmp_voltage, sum;
    int i;

    sum = 0;

    for (i = 0; i < readings; i++)
        sum += voltage_in[i] / (V_DIVIDER * (4095/V_REF_HI));

    tmp_voltage = sum / readings;

    if (tmp_voltage >= 0)
        return tmp_voltage;
    else
        return 0;
}

double getCurrent(uint16_t current_in[MAX_SAMPLES], uint16_t readings) {

    double sum, tmp_current;
    int i;

    sum = 0;

    for (i = 0; i < readings; i++)
        sum += current_in[i];

    sum = sum / readings; //take average of all but the first reading
    //tmp_current = (sum * (V_REF_HI / 4095)) / (V_GAIN * R_SHUNT) ;

    tmp_current = (sum - OFFSET) / I_GAIN;

    if (tmp_current >= 0)
        return tmp_current;
    else
        return 0;
}

double convertDuty(double duty) {

    if (duty * PERIOD > PERIOD)
        return PERIOD;
    else if (duty * PERIOD < 0)
        return 0;
    else
        return duty * PERIOD;

}
