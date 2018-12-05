/*
 * sensors.h
 *
 *  Created on: Jul 19, 2018
 *      Author: ccatt.stu
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#include <stdint.h>

#include "mppt.h"

#define OFFSET -7.72f //experimentally found offset used for calibration
#define I_GAIN 566.9
#define V_GAIN 10 //op-amp gain
#define R_SHUNT 0.05f
#define V_DIVIDER 0.0625f // From the voltage divider, V_ref = V_DIVIDE * V_in
#define V_REF_HI 3.3f

#define PERIOD 125.0f // (125 -> 200kHz)
#define MAX_SAMPLES 32

double getVoltage(uint16_t[MAX_SAMPLES], uint16_t);
double getCurrent(uint16_t[MAX_SAMPLES], uint16_t);
double convertDuty(double);


#endif /* SENSORS_H_ */
