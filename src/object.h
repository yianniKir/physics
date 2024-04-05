#ifndef OBJECT_H
#define OBJECT_H

#include "physics.h"

#include "particle.h"

#include "sprite.h"
class Object
{
    public:
        Particle particle;
        glm::vec2 size;
        glm::vec3 color;
        float rotation;

        Object(Sprite &sprite): sprite(sprite) {};
        Object(Sprite &sprite, glm::vec2 position, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec2 acceleration = glm::vec2(0.0f,0.0f)) : sprite(sprite), color(color), size(size){
            particle.position = position;
            particle.velocity = velocity;
            particle.acceleration = acceleration;

            rotation = 0.0f;

            particle.inverseMass = 1.0f;
            destroyed = false;
        };
    

        void draw(){
            sprite.drawSprite(particle.posNDC(), size, rotation, color);

        }

        void destroy(){
            destroyed = true;
        }
    private:
        Sprite sprite;
        bool destroyed;
};

#endif