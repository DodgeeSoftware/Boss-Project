#ifndef Entity_H
#define Entity_H

#include <SDL/sdl.h>
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#include "luabind/luabind.hpp"

class Entity
{
    public:
        Entity();
        virtual ~Entity();
        float getX();
        float getY();
        float getRadius();
        float getXVelocity();
        float getYVelocity();
        void setX(float x);
        void setY(float y);
        void setRadius(float width);
        void setXVelocity(float xVelocity);
        void setYVelocity(float yVelocity);

        std::string getState();
        void setState(std::string state);

        void update();

        int getHealth();
        int getMaxHealth();
        void setHealth(int health);
        void setMaxHealth(int maxHealth);

    protected:

    private:
        float x;
        float y;
        float radius;
        float xVelocity;
        float yVelocity;
        bool falling;
        int health;
        int maxHealth;
        std::string state;
};

inline float Entity::getX() { return x; }
inline float Entity::getY() { return y; }
inline float Entity::getRadius() { return radius; }
inline float Entity::getXVelocity() { return xVelocity; }
inline float Entity::getYVelocity() { return yVelocity; }
inline void Entity::setX(float x) { this->x = x; }
inline void Entity::setY(float y) { this->y = y; }
inline void Entity::setRadius(float radius) { this->radius = radius; }
inline void Entity::setXVelocity(float xVelocity) { this->xVelocity = xVelocity; }
inline void Entity::setYVelocity(float yVelocity) { this->yVelocity = yVelocity; }
inline int Entity::getHealth() { return this->health; }
inline int Entity::getMaxHealth() { return this->maxHealth; }
inline void Entity::setHealth(int health) { this->health = health; }
inline void Entity::setMaxHealth(int maxHealth) { this->maxHealth = maxHealth; }
inline std::string Entity::getState() { return this->state; }
inline void Entity::setState(std::string state) { this->state = state; }

#endif // Entity_H
