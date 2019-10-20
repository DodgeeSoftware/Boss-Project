#include "MainMenuGameState.h"
#include "Game.h"

void MainMenuGameState::onEnter()
{
    SDL_ShowCursor(SDL_TRUE);
    Mix_VolumeMusic(MIX_MAX_VOLUME/2);
    Mix_PlayMusic(this->game->menuMusic, -1);
    mainMenuSequenceTimer.stop();
    mainMenuSequenceTimer.start();
}

void MainMenuGameState::think()
{
    if (this->game->pKeys[SDLK_ESCAPE] == SDL_TRUE)
    {
        this->game->isRunning = false;
    }
    if (this->game->pKeys[SDLK_SPACE] == SDL_TRUE)
    {
        this->game->changeState(this->game->pBattleGameState);
    }
    if (this->game->mouse.isLeftClick())
    {
        this->game->changeState(this->game->pBattleGameState);
    }
    if (mainMenuSequenceTimer.getTicks() > 30000)
    {
        this->game->changeState(this->game->pIntroGameState);
    }
}

void MainMenuGameState::update()
{

}

void MainMenuGameState::draw()
{
    SDL_Color winColour;
    winColour.r = 255;
    winColour.g = 255;
    winColour.b = 255;
    FontUtils::drawString(this->game->pFont, winColour, "MainMenuGameState", 200, 200 + 45 * 0, this->game->pScreen);
    FontUtils::drawString(this->game->pFont, winColour, "New", 200, 200 + 45 * 1, this->game->pScreen);
    FontUtils::drawString(this->game->pFont, winColour, "Load Game", 200, 200 + 45 * 2, this->game->pScreen);
    FontUtils::drawString(this->game->pFont, winColour, "Options", 200, 200 + 45 * 3, this->game->pScreen);
    FontUtils::drawString(this->game->pFont, winColour, "Credits", 200, 200 + 45 * 4, this->game->pScreen);
    FontUtils::drawString(this->game->pFont, winColour, "Exit", 200, 200 + 45 * 5, this->game->pScreen);

    char buffer[50];
    snprintf(buffer, 50, "Count Down: %i", 30000 - mainMenuSequenceTimer.getTicks());
    FontUtils::drawString(this->game->pFont, winColour, buffer, 200, 200 - 45*2, this->game->pScreen);

    SDL_Flip(game->pScreen);
    boxRGBA(this->game->pScreen, 0, 0, 640, 480, 64, 64, 224, 255);
}

void MainMenuGameState::onExit()
{

}
