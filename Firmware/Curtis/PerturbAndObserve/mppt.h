/*
 * mppt.h
 *
 *  Created on: Jul 19, 2018
 *      Author: ccatt.stu
 */

#ifndef MPPT_H_
#define MPPT_H_

#define DELTA 0.025f
#define DUTY_MIN 0.25f
#define DUTY_MAX 0.90f
#define DUTY_INIT 0.30f

double perturbAndObserve(void);
double incrementalConductance(void);

#endif /* MPPT_H_ */
