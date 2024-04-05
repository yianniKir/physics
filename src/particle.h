#ifndef PARTICLE_H
#define PARTICLE_H

#include "physics.h"

class Particle{

    public:
        glm::vec2 position;

        glm::vec2 velocity;

        glm::vec2 acceleration;

        float damping;

        float inverseMass;

        void integrate(float duration);

        glm::vec2 posNDC();

};

#endif