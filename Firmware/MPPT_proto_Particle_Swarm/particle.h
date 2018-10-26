/*
 * Particle.h
 *
 *  Created on: Jul 9, 2018
 *      Author: ccatt.stu
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "swarm.h"

struct Particle {
    float position; // duty cycle
    float velocity;
    float position_best; // best duty cycle
    float position_best_power; // power of best duty cycle
};

void InitParticles(struct Particle * particles[], int num_particles,
                   struct Particle *p1, struct Particle *p2, struct Particle *p3);
void InitParticle(struct Particle * particle, float position, float velocity);
void updateVelocity(struct Particle * p, struct Swarm * s);
void updatePosition(struct Particle * p, struct Swarm * s);

/*
 void InitParticles(struct Particle * particles[], int num_particles,
                   struct Particle *p1, struct Particle *p2, struct Particle *p3,
                   struct Particle *p4);
*/

#endif /* PARTICLE_H_ */
