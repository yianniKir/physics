#ifndef OBJECT_H
#define OBJECT_H

#include "physics.h"

#include "sprite.h"
class Object
{
    public:
        glm::vec2   position, size, velocity, acceleration;
        glm::vec3   color;
        float       rotation;

        

        Object(Sprite &sprite): sprite(sprite) {};
        Object(Sprite &sprite, glm::vec2 position, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec2 acceleration = glm::vec2(0.0f,0.0f)) : sprite(sprite), position(position), size(size), color(color), velocity(velocity){
            rotation = 0.0f;
        };

        void update(float dt){
            if(!(acceleration == glm::vec2(0.0f))){
                velocity += acceleration * dt;
            }
                
            position += velocity * dt;
        }
    

        void draw(){
            sprite.drawSprite(glm::vec2(position.x/SCRADJUST, position.y/SCRADJUST), size, rotation, color);
        }
    private:
        Sprite sprite;
};

#endif