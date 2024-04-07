#include <assert.h>
#include "particle.h"

void Particle::integrate(float duration){

    //assert(duration > 0.0);

    //Update linear position
    //position = position + velocity * duration
    position = position + velocity * duration;
    
    //work out the acceleration from the force
    //(used for generating forces later)

    glm::vec2 resultingAccel = acceleration;
    addForce(glm::vec2(0.0f, -mass*9.81f));
    resultingAccel = resultingAccel + forceAccum/ mass;
    //update linear velocity
    //velocity = velocity + acceleration * duration
    velocity = velocity + resultingAccel * duration;

    clearAccumulator();
    
   // clearAccumulator();
}

void Particle::clearAccumulator(){
    forceAccum.x = 0.0f;
    forceAccum.y = 0.0f;
}

glm::vec2 Particle::posNDC(){
    return glm::vec2(position.x/SCRADJUST, position.y/SCRADJUST);
}

void Particle::addForce(const glm::vec2 &force){
    forceAccum += force;
}