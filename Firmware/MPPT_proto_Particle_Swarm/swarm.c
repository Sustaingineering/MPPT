/*
 * Swarm.c
 *
 *  Created on: Jul 9, 2018
 *      Author: ccatt.stu
 */

#include "Swarm.h"
#include "Particle.h"
#include <stdlib.h>
#include <math.h>

void InitSwarm(struct Swarm * swarm, int num_particles, float c1,
               float c1_min, float c2, float c2_min, float w, int max_iter, struct Particle * particles[]) {

    swarm->c1 = c1;
    swarm->c1_max = c1;
    swarm->c1_min = c1_min;
    swarm->c2 = c2;
    swarm->c2_max = c2;
    swarm->c2_min = c2_min;
    swarm->w = w;

    swarm->max_iter = max_iter;
    swarm->num_particles = num_particles;

    swarm->particles = particles;

    return;
}

void resetSwarm(struct Swarm *s) {

    int i;
    float inc, pos, vel;

    s->swarm_best = 0;
    s->swarm_best_power = 0;

    s->c1 = s->c1_max;
    s->c2 = s->c2_max;

    inc = (float) 1/(s->num_particles + 1);

    for (i = 0; i < s->num_particles; i++) {
        pos = (i+1) * inc;
        vel = (rand() / (float) RAND_MAX) * (0.2) - 0.1; //return a number in range [-0.1, 0.1]
        InitParticle(s->particles[i], pos, vel);
    }

    return;
}

void sortSwarm(struct Swarm *s, int direction) {

    int i, j;

    for (i = 0; i < s->num_particles - 1; i++) {
        for (j = i; j < s->num_particles; j++) {
            if (s->particles[i]->position > s->particles[j]->position && direction == 1)
                swap(s, i, j);

            else if (s->particles[i]->position < s->particles[j]->position && direction == 0)
                swap(s, i, j);
        }
    }

    return;
}

void swap(struct Swarm * s, int i, int j) {
    struct Particle *tmp = s->particles[i];
    s->particles[i] = s->particles[j];
    s->particles[j] = tmp;

    return;
}

void adjustConstants(struct Swarm *s, int iteration) {

    s->c1 = s->c1_max - (float)iteration/s->max_iter*(s->c1_max - s->c1_min);
    s->c2 = s->c2_max - (float)iteration/s->max_iter*(s->c2_max - s->c2_min);

    return;
}
