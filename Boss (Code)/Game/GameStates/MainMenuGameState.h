#ifndef MainMenuGameState_H
#define MainMenuGameState_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_Image.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_net.h>
#include "Timer.h"
#include "IState.h"
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#include "luabind/luabind.hpp"

class MainMenuGameState : public IState
{
    public:
        MainMenuGameState(Game* game) : IState(game) {}
        virtual ~MainMenuGameState() {}
        virtual void onEnter();
        virtual void think();
        virtual void update();
        virtual void draw();
        virtual void onExit();

    private:
        Timer mainMenuSequenceTimer;
};

#endif // MainMenuGameState_H
