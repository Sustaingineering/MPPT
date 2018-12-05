/*
 * Particle.c
 *
 *  Created on: Jul 9, 2018
 *      Author: ccatt.stu
 */

#include "Particle.h"
#include "Swarm.h"

#include <stdlib.h>

//void InitParticles(struct Particle * particles[], int num_particles, struct Particle *p1,
//                   struct Particle *p2, struct Particle *p3, struct Particle *p4) {
void InitParticles(struct Particle * particles[], int num_particles, struct Particle *p1, struct Particle *p2, struct Particle *p3) {

    int i;
    float pos, vel, inc;

    inc = (float) 1/(num_particles + 1);

    for (i = 0; i < num_particles; i++) {

        pos = (i+1) * inc;
        vel = (rand() / (float) RAND_MAX) * (0.2) - 0.1; //return a number in range [-0.1, 0.1]

        switch(i) {

            case 0:
                particles[0] = p1;
                break;
            case 1:
                particles[1] = p2;
                break;
            case 2:
                particles[2] = p3;
                break;
//            case 3:
//                particles[3] = p4;
//                break;
            default:
                break;

        }

        InitParticle(particles[i], pos, vel);
    }

    return;
}

void InitParticle(struct Particle * particle, float position, float velocity) {

    particle->position = position;
    particle->velocity = velocity;
    particle->position_best = 0;
    particle->position_best_power = 0;

}

void updateVelocity(struct Particle * p, struct Swarm * s) {

    float r1, r2;

    r1 = (rand() / (float) RAND_MAX);
    r2 = (rand() / (float) RAND_MAX);

    p->velocity = s->w*p->velocity + s->c1*r1*(p->position_best - p->position) + s->c2*r2*(s->swarm_best - p->position);

    return;
}

void updatePosition(struct Particle * p, struct Swarm * s) {

    updateVelocity(p, s);

    float new_pos = p->velocity + p->position;

    if (new_pos >= 1)
        p->position = 1;
    else if (new_pos <= 0)
        p->position = 0;
    else
        p->position = new_pos;

    return;
}
