#include "IntroGameState.h"
#include "Game.h"

void IntroGameState::onEnter()
{
    SDL_ShowCursor(SDL_TRUE);
    Mix_VolumeMusic(MIX_MAX_VOLUME/2);
    Mix_PlayMusic(this->game->introMusic, -1);
    introSequenceTimer.start();
}

void IntroGameState::think()
{
    if (this->game->pKeys[SDLK_ESCAPE] == SDL_TRUE)
    {
        this->game->isRunning = false;
    }
    if (this->game->pKeys[SDLK_SPACE] == SDL_TRUE)
    {
        //this->game->changeState(this->game->pBattleGameState);
        this->game->changeState(this->game->pMainMenuGameState);
    }
    if (this->game->mouse.isLeftClick())
    {
        //this->game->changeState(this->game->pBattleGameState);
        this->game->changeState(this->game->pMainMenuGameState);
    }
    if (introSequenceTimer.getTicks() > 30000)
    {
        this->game->changeState(this->game->pMainMenuGameState);
    }
}

void IntroGameState::update()
{

}

void IntroGameState::draw()
{
    SDL_Color winColour;
    winColour.r = 255;
    winColour.g = 255;
    winColour.b = 255;
    FontUtils::drawString(this->game->pFont, winColour, "IntroGameState", 200, 200, this->game->pScreen);

    char buffer[50];
    snprintf(buffer, 50, "Count Down: %i", 30000 - introSequenceTimer.getTicks());
    FontUtils::drawString(this->game->pFont, winColour, buffer, 200, 200 + 45, this->game->pScreen);
    SDL_Flip(game->pScreen);
    boxRGBA(this->game->pScreen, 0, 0, 640, 480, 64, 64, 224, 255);
}

void IntroGameState::onExit()
{

}
