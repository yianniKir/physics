#include <assert.h>
#include "particle.h"

void Particle::integrate(float duration){
    
    if (inverseMass <= 0.0f){
    
        return;

    }

    //assert(duration > 0.0);

    //Update linear position
    //position = position + velocity * duration
    position = position + velocity * duration;
    
    //work out the acceleration from the force
    //(used for generating forces later)

    glm::vec2 resultingAccel = acceleration;

    //update linear velocity
    //velocity = velocity + acceleration * duration
    velocity = velocity + acceleration * duration;

    //damping?
    //velocity = velocity* damping^duration
    //velocity *= real_pow(damping, duration);

   // clearAccumulator();
}

glm::vec2 Particle::posNDC(){
    return glm::vec2(position.x/SCRADJUST, position.y/SCRADJUST);
}