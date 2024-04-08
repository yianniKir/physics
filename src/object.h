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
            destroyable = true;
            particle.mass = 5.0f;
            particle.damping = 0.99999f;
        };
    

        void draw(){
            sprite.drawSprite(particle.posNDC(), size, rotation, color);
        }

        void setDestroy(bool b){
            destroyable = b;
        }

        bool isDestroyable(){
            return destroyable;
        }

        void lock(){
            lockk = true;
        }

        void unlock(){
            lockk = false;
        }

        bool isLocked(){
            return lockk;
        }

    private:
        bool lockk;
        bool destroyable;
        Sprite sprite;
};

#endif