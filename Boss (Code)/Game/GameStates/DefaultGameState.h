#ifndef DEFAULTGAMESTATE_H
#define DEFAULTGAMESTATE_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_Image.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_net.h>

#include "IState.h"
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#include "luabind/luabind.hpp"

class DefaultGameState : public IState
{
    public:
        DefaultGameState(Game* game) : IState(game) {}
        virtual ~DefaultGameState() {}
        virtual void onEnter();
        virtual void think();
        virtual void update();
        virtual void draw();
        virtual void onExit();

    private:

};

#endif // DEFAULTGAMESTATE_H
