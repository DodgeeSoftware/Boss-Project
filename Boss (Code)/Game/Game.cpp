#include "Game.h"

Game* Game::pInstance = NULL;

Game* Game::getInstance()
{
    if (pInstance != NULL) return pInstance;
    pInstance = new Game();
    return pInstance;
}

int Game::run(int argc, char *argv[])
{
    if (init() == true)
    {
        this->changeState(pDefaultGameState);
        while (this->isRunning == true)
        {
            this->collectInput();
            this->think();
            this->update();
            this->draw();
        }
    }
    this->quit();
    return EXIT_SUCCESS;
}

bool Game::init()
{
    std::cout << "Game::init()" << std::endl;
    if (initWindow() == false) return false;
    if (initAudio() == false) return false;
    if (initText() == false) return false;
    this->isRunning = true;
    return true;
}

bool Game::initWindow()
{
    std::cout << "Game::initWindow()" << std::endl;
    pScreen = SDL_SetVideoMode(640, 480, 32, SDL_DOUBLEBUF | SDL_SWSURFACE);
    SDL_ShowCursor(SDL_FALSE);
    return true;
}

bool Game::initAudio()
{
    std::cout << "Game::initAudio()" << std::endl;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        std::cout << "Could load background." << std::endl;
        std::cout << "Mix_Open Audio: " << Mix_GetError() << std::endl;
        return false;
    }
    playerShootSound = Mix_LoadWAV("media/playerShoot.wav");
    if (playerShootSound == NULL)
    {
        std::cout << "Could load media/playerShoot.wav" << std::endl;
        return false;
    }
    bossHitSound = Mix_LoadWAV("media/bossHitSound.wav");
    if (bossHitSound == NULL)
    {
        std::cout << "Could load media/bossHitSound.wav" << std::endl;
        return false;
    }
    bossExplodeSound = Mix_LoadWAV("media/bossExplode.wav");
    if (bossExplodeSound == NULL)
    {
        std::cout << "Could load media/bossExplode.wav" << std::endl;
        return false;
    }
    battleMusic = Mix_LoadMUS("media/sonic2_boss.ogg");
    if (battleMusic == NULL)
    {
        std::cout << "Could load media/media/0-kru.xm" << std::endl;
        return false;
    }
    victoryMusic = Mix_LoadMUS("media/Victory_Fanfare.ogg");
    if (battleMusic == NULL)
    {
        std::cout << "Could load media/media/Victory_Fanfare.ogg" << std::endl;
        return false;
    }
    menuMusic = Mix_LoadMUS("media/am-fm_-_raining_stars.xm");
    if (menuMusic == NULL)
    {
        std::cout << "Could load media/media/am-fm_-_raining_stars.xm" << std::endl;
        return false;
    }
    introMusic = Mix_LoadMUS("media/4mat-intro_music.mod");
    if (introMusic == NULL)
    {
        std::cout << "Could load media/media/4mat-intro_music.mod.mod" << std::endl;
        return false;
    }
    return true;
}

bool Game::initText()
{
    std::cout << "Game::initText()" << std::endl;
    if (TTF_Init()==-1)
    {
        std::cout << "TTF_Init: " << (TTF_GetError()) << std::endl;
        return false;
    }
    pFont = TTF_OpenFont("media/arial.ttf", 32);
    if (pFont == NULL )
    {
        std::cout << "Could not open font." << std::endl;
    }
    return true;
}

void Game::collectInput()
{
    // Get Operating System Messages
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            this->isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                default:
                    break;
            }
            break;
        default:
            break;
    };

    // Get Keyboard State
    pKeys = SDL_GetKeyState(NULL);
    mouse.update();
}

void Game::think()
{
    if (gameState != NULL) this->gameState->think();
}

void Game::update()
{
    if (gameState != NULL) this->gameState->update();
}

void Game::draw()
{
    if (gameState != NULL) this->gameState->draw();
}

void Game::quit()
{
    std::cout << "Game::quit()" << std::endl;
}

void Game::changeState(IState* gameState)
{
    if (this->gameState != gameState)
    {
        if (this->gameState != NULL) this->gameState->onExit();
        this->gameState = gameState;
        this->gameState->onEnter();
    }
}

void Game::bindToLua(lua_State* luaState)
{
    luabind::module(luaState)
    [
        luabind::class_<Game>("Game")
        //.def("", (void(Game::*)())& Game::)
    ];
}


