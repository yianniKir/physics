#ifndef OBJECT_H
#define OBJECT_H

#include "physics.h"

#include "particle.h"

#include "sprite.h"

class Object : public Particle
{
    public:
        glm::vec2 size;
        glm::vec3 color;
        float rotation;

        Object(Sprite &sprite): sprite(sprite) {};
        Object(Sprite &sprite, glm::vec2 positionVEC, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocityVEC = glm::vec2(0.0f, 0.0f), glm::vec2 accelerationVEC = glm::vec2(0.0f,0.0f)) : sprite(sprite), color(color), size(size){
            position = positionVEC;
            velocity = velocityVEC;
            acceleration = accelerationVEC;

            rotation = 0.0f;
            destroyable = true;
            mass = 5.0f;
            damping = 0.99999f;
        };
    
        void Draw();
        void SetDestroyable(bool b);
        bool IsDestroyed();
        void Lock();
        void Unlock();
        bool IsLocked();

    private:
        bool m_lock;
        bool destroyable;
        Sprite sprite;
};

#endif