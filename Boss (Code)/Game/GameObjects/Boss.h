#ifndef BOSS_H
#define BOSS_H

#include "Entity.h"


using namespace luabind;

class Boss : public Entity
{
    public:
        Boss() {}
        virtual ~Boss() {}

        static void bind(lua_State* luaState);

        void setUnderAttack(bool underAttack);
        bool isUnderAttack();
        bool isDead();
        void setDead(bool dead);
        void setImmuneToDamage(bool immuneToDamage);
        bool isImmuneToDamage();

    protected:

    private:
        bool underAttack;
        bool dead;
        bool immuneToDamage;
};

inline void Boss::setUnderAttack(bool underAttack) { this->underAttack = underAttack; }
inline bool Boss::isUnderAttack() { return this->underAttack; }
inline bool Boss::isDead() { return this->dead; }
inline void Boss::setDead(bool dead) { this->dead = dead; }
inline void Boss::setImmuneToDamage(bool immuneToDamage) { this->immuneToDamage = immuneToDamage; }
inline bool Boss::isImmuneToDamage() { return this->immuneToDamage; }

#endif // BOSS_H
