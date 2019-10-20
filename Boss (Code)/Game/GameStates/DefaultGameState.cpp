#include "DefaultGameState.h"
#include "Game.h"

void DefaultGameState::onEnter()
{
    SDL_ShowCursor(SDL_TRUE);
    SDL_WM_SetCaption( "Dodgee Software: Boss Tech Demo 2012", NULL );
    this->game->changeState(this->game->pIntroGameState);
}

void DefaultGameState::think()
{
    if (this->game->pKeys[SDLK_ESCAPE] == SDL_TRUE)
    {
        this->game->isRunning = false;
    }
}

void DefaultGameState::update()
{

}

void DefaultGameState::draw()
{
    SDL_Color winColour;
    winColour.r = 255;
    winColour.g = 255;
    winColour.b = 255;
    FontUtils::drawString(this->game->pFont, winColour, "DefaultGameState", 200, 200, this->game->pScreen);
    SDL_Flip(game->pScreen);
    boxRGBA(this->game->pScreen, 0, 0, 640, 480, 64, 64, 224, 255);
    SDL_Flip(game->pScreen);
    boxRGBA(this->game->pScreen, 0, 0, 640, 480, 64, 64, 224, 255);
}

void DefaultGameState::onExit()
{

}
