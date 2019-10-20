#ifndef PLAYER_H
#define PLAYER_H

#include <SDL/sdl.h>
#include "Entity.h"

class Player : public Entity
{
    public:
        Player() {}
        virtual ~Player() {}
        static void bindToLua(lua_State* luaState);

    protected:

    private:

};

#endif // PLAYER_H
