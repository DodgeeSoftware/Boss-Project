#include "Entity.h"

Entity::Entity()
{
    falling = false;
    xVelocity = 0.0f;
    yVelocity = 0.0f;
}

Entity::~Entity()
{
    //dtor
}


void Entity::update()
{
    this->x = this->x + this->xVelocity;
    this->y = this->y + this->yVelocity;
}


