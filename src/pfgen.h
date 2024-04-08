#ifndef PFGEN_H
#define PFGEN_H

#include "physics.h"
#include "particle.h"

class ParticleForceGenerator{
    public:
        virtual void updateForce(Particle *particle, float duration) = 0;
};

class ParticleForceRegistry{
    protected:
        struct ParticleForceRegistration{
            Particle *particle;
            ParticleForceGenerator *fg;
        };

        std::vector<ParticleForceRegistration> registrations;
        
    public:
        void add(Particle *particle, ParticleForceGenerator *fg);

        void remove(Particle *particle, ParticleForceGenerator *fg);

        void clear();

        void updateForces(float duration);
};

class ParticleGravity : public ParticleForceGenerator{
    glm::vec2 gravity;

    public:
        ParticleGravity(const glm::vec2 &gravity) : gravity(gravity) {} ;

        virtual void updateForce(Particle *particle, float duration);
};

#endif