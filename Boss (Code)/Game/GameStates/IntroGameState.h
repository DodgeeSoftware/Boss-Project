#ifndef IntroGameState_H
#define IntroGameState_H

#include <cstdio>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_Image.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_net.h>

#include "IState.h"
#include "Timer.h"
#include <cmath>
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#include "luabind/luabind.hpp"

class IntroGameState : public IState
{
    public:
        IntroGameState(Game* game) : IState(game) {}
        virtual ~IntroGameState() {}
        virtual void onEnter();
        virtual void think();
        virtual void update();
        virtual void draw();
        virtual void onExit();

    private:
        Timer introSequenceTimer;

};

#endif // IntroGameState_H
