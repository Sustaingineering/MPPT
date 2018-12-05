/*
 * mppt.h
 *
 *  Created on: Jul 19, 2018
 *      Author: ccatt.stu
 */

#ifndef MPPT_H_
#define MPPT_H_

#define DELTA 0.025f
#define GLOBAL_SEARCH_DELTA 0.1f

#define DUTY_MIN 0.15f
#define DUTY_MAX 0.90f

double perturbAndObserve(void);
double incrementalConductance(void);
double globalSearchCount(double);

#endif /* MPPT_H_ */
