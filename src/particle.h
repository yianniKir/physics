#ifndef PARTICLE_H
#define PARTICLE_H

#include "physics.h"

class Particle{

    public:
        glm::vec2 position;

        glm::vec2 velocity;

        glm::vec2 acceleration;

        float damping;

        float mass;

        void integrate(float duration);

        glm::vec2 posNDC();

        //Mass-aggregate

        glm::vec2 forceAccum = glm::vec2(0.0f,0.0f);
        void clearAccumulator();

        void addForce(const glm::vec2 &force);

};

#endif