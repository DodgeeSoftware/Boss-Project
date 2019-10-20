#ifndef BattleGameState_H
#define BattleGameState_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_Image.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_net.h>

#include "IState.h"
#include "Timer.h"
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#include "luabind/luabind.hpp"

class BattleGameState : public IState
{
    public:
        BattleGameState(Game* game) : IState(game) {}
        virtual ~BattleGameState() {}
        virtual void onEnter();
        virtual void think();
        virtual void update();
        virtual void draw();
        virtual void onExit();

        void bossSpeak(const char* text);
        void createBossBullet(float x, float y, float xVel, float yVel);
        static void bindToLua(lua_State* luaState);

    private:
        void restart();
        void doPlayer();
        void doBoss();
        void doPlayerBullets();
        void doBossBullets();

        Timer underAttackTimer;
        Timer explodeEffectTimer;
        Timer youWinTimer;
};

#endif // BattleGameState_H
