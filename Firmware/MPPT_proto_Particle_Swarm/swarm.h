/*
 * Swarm.h
 *
 *  Created on: Jul 9, 2018
 *      Author: ccatt.stu
 */

#include "particle.h"

#ifndef SWARM_H_
#define SWARM_H_

#define ASCENDING 1
#define DESCENDING 0
#define NUM_PARTICLES 3 //this can't be changed without modifying source code
#define ITERATIONS 10
#define C1 0.75f
#define C1_MIN 0.25f
#define C2 0.75f
#define C2_MIN 0.25f
#define W 0.5f

struct Swarm {
    struct Particle ** particles;
    float swarm_best;
    float swarm_best_power;

    float c1, c1_min, c1_max;
    float c2, c2_min, c2_max;
    float w;

    int max_iter;
    int num_particles;
};

void InitSwarm(struct Swarm * swarm, int num_particles, float c1,
               float c1_min, float c2, float c2_min, float w, int max_iter, struct Particle * particles[]);
void resetSwarm(struct Swarm * s);
void sortSwarm(struct Swarm *s, int direction);
void swap(struct Swarm * s, int i, int j);
void adjustConstants(struct Swarm *s, int iteration);

#endif /* SWARM_H_ */
