#include "object.h"

void Object::Draw(){
    sprite.drawSprite(particle.posNDC(), size, rotation, color);
}

void Object::SetDestroyable(bool b){
    destroyable = b;
}

bool Object::IsDestroyed(){
    return destroyable;
}

void Object::Lock(){
    m_lock = true;
}

void Object::Unlock(){
    m_lock = false;
}

bool Object::IsLocked(){
    return m_lock;
}