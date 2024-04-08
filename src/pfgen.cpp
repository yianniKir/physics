#include "pfgen.h"

void ParticleForceRegistry::updateForces(float duration){

    std::vector<ParticleForceRegistration>::iterator i = registrations.begin();

    for(; i != registrations.end(); i++){
        i->fg->updateForce(i->particle, duration);
    }
}

void ParticleGravity::updateForce(Particle* particle, float duration) {
    particle->addForce(gravity * particle->mass); 
}
