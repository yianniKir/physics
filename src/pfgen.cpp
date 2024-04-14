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

void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator *fg)
{
    ParticleForceRegistration registration;
    registration.particle = particle;
    registration.fg = fg;
    registrations.push_back(registration);
}

void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* fg)
{
    // Iterator to traverse the registrations vector
    std::vector<ParticleForceRegistration>::iterator i = registrations.begin();

    // Loop through registrations to find the matching entry
    for (; i != registrations.end(); ++i)
    {
        // Check if the current registration matches the provided particle and force generator
        if (i->particle == particle && i->fg == fg)
        {
            // Remove the registration entry
            registrations.erase(i);
            return; // Exit the function after removal
        }
    }
}

void ParticleForceRegistry::clear(){
    registrations.clear();
}

void ParticleDrag::updateForce(Particle  *particle, float duration){
    glm::vec2 force;
    force = (*particle).velocity; //same as force->

    float dragCoeff = glm::length(force);
    //formula
    dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

    //calculate final foce
    glm::normalize(force);
    force = force * -dragCoeff;
    (*particle).addForce(force);
}