/*
 * mppt.c
 *
 *  Created on: Jul 19, 2018
 *      Author: ccatt.stu
 */

#include "mppt.h"

#include <math.h>

extern double duty;
extern double duty_prev;
extern double power;
extern double power_prev;
extern double voltage;
extern double voltage_prev;
extern double current;
extern double current_prev;

double perturbAndObserve() {

    if (power > power_prev) {
        if (voltage > voltage_prev)
            duty = duty_prev + DELTA;
        else
            duty = duty_prev - DELTA;
    }
    else {
        if (voltage > voltage_prev)
            duty = duty_prev - DELTA;
        else
            duty = duty_prev + DELTA;
    }

    return duty;

}

double incrementalConductance() {

        double delta_i, delta_v;

        delta_i = current -  current_prev;
        delta_v = voltage - voltage_prev;

        if (fabs(delta_v) < 0.05)
        {
            if (fabs(delta_i) < 0.000001)
            {
                duty = duty_prev;
            }
            else
            {
                if (fabs(delta_i) < 0.05)
                    duty = duty_prev + DELTA;
                else
                    duty = duty_prev - DELTA;
            }
        }

        else
        {
            if (delta_i/delta_v == -current/voltage)
            {
                duty = duty_prev;
            }
            else
            {
                if (delta_i/delta_v > -current/voltage)
                {
                    duty = duty_prev + DELTA;
                }
                else
                {
                    duty = duty_prev - DELTA;
                }
            }
        }

    return duty;
}

double globalSearchCount(double search_delta) {
    if (search_delta > 0)
        return ceil(1/search_delta) - 1;
    else
        return 1;
}

