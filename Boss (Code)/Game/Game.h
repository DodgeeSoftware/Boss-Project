#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <map>
#include <vector>
#include <Time.h>
#include <SDL/sdl.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_Image.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_net.h>

#include "SDL_Mouse.h"
#include "FontUtils.h"
#include "Physics.h"


#include "IState.h"
#include "DefaultGameState.h"
#include "BattleGameState.h"
#include "IntroGameState.h"
#include "MainMenuGameState.h"
#include "Timer.h"
#include "Player.h"
#include "Boss.h"
#include "Bullet.h"

class Game
{
    friend class DefaultGameState;
    friend class BattleGameState;
    friend class IntroGameState;
    friend class MainMenuGameState;

    public:
        static Game* getInstance();
        int run(int argc, char *argv[]);

    protected:

    private:
        static Game* pInstance;
        Game()
        {
            isRunning = false;
            pScreen = NULL;
            gameState = NULL;
            pDefaultGameState = new DefaultGameState(this);
            pBattleGameState = new BattleGameState(this);
            pIntroGameState = new IntroGameState(this);
            pMainMenuGameState = new MainMenuGameState(this);
        }
        Game(const Game& other) {}
        bool init();
        bool initWindow();
        bool initAudio();
        bool initText();
        void collectInput();
        void think();
        void update();
        void draw();
        void quit();
        void changeState(IState* gameState);
        static void bindToLua(lua_State* luaState);

        bool isRunning;
        SDL_Surface* pScreen;
        SDL_Event event;
        SDL_Mouse mouse;
        Uint8* pKeys;
        IState* gameState;

        DefaultGameState* pDefaultGameState;
        BattleGameState* pBattleGameState;
        IntroGameState* pIntroGameState;
        MainMenuGameState* pMainMenuGameState;

        // Global Asset Pool - Start
        Mix_Music* introMusic;
        Mix_Music* battleMusic;
        Mix_Music* menuMusic;
        Mix_Music* victoryMusic;
        TTF_Font* pFont;
        Mix_Chunk* playerShootSound;
        Mix_Chunk* bossHitSound;
        Mix_Chunk* bossExplodeSound;
        lua_State* pBossScript;
        // Global Asset Pool - End

        // Game Objects (World) - Start
        Player player;
        float gravity;
        float playerSpeed;
        Boss boss;
        std::vector<Bullet> bossBullets;
        std::vector<Bullet> playerBullets;
        // Game Objects (World) - End



};

#endif // GAME_H
