#include "BattleGameState.h"
#include "Game.h"

void BattleGameState::onEnter()
{
    srand (time(NULL));
    SDL_ShowCursor(SDL_FALSE);

    this->game->pBossScript = luaL_newstate();
    if (this->game->pBossScript == NULL)
    {
        std::cout << "Could not create Lua State for Boss." << std::endl;
    }
    else
    {

        luaL_openlibs(this->game->pBossScript);
        luabind::open(this->game->pBossScript);
        // Tool Chain Lua State
        Boss::bind(this->game->pBossScript);
        Timer::bindToLua(this->game->pBossScript);
        Game::bindToLua(this->game->pBossScript);
        BattleGameState::bindToLua(this->game->pBossScript);
        Player::bindToLua(this->game->pBossScript);
        luaL_dofile(this->game->pBossScript, "media/BossScript.lua");
        luabind::globals(this->game->pBossScript)["Game"] = Game::getInstance();
        luabind::globals(this->game->pBossScript)["BattleGameState"] = this;
        luabind::globals(this->game->pBossScript)["Player"] = &(this->game->player);
        luabind::globals(this->game->pBossScript)["this"] = &(this->game->boss);
    }
    restart();
}

void BattleGameState::think()
{
    if (this->game->pKeys[SDLK_ESCAPE])
    {
        this->game->isRunning = false;
    }
    if (this->game->pKeys[SDLK_F4])
    {
        restart();
    }
    if (this->game->player.getHealth() > 0)
    {
        doPlayer();
        doPlayerBullets();
    }
    if (this->game->boss.isDead() == false)
    {
        doBoss();
        doBossBullets();
        if (this->game->boss.getHealth() <= 0 && this->game->boss.isDead() == false)
        {
            this->game->boss.setDead(true);
            Mix_PlayMusic(this->game->victoryMusic, 0);
            explodeEffectTimer.start();
            youWinTimer.start();
            this->game->boss.setXVelocity(0.0f);
            this->game->boss.setYVelocity(0.0f);
        }
    }
    if (youWinTimer.getTicks() > 30000)
    {
        //this->game->isRunning = false;
        this->game->changeState(this->game->pDefaultGameState);
    }
}

void BattleGameState::update()
{
    this->game->boss.update();
    for (std::vector<Bullet>::iterator iter = this->game->bossBullets.begin(); iter != this->game->bossBullets.end(); iter++)
    {
        (*iter).update();
    }
    this->game->player.update();
    for (std::vector<Bullet>::iterator iter = this->game->playerBullets.begin(); iter != this->game->playerBullets.end(); iter++)
    {
        (*iter).update();
    }
}

void BattleGameState::draw()
{
//        SDL_Color debugColour;
//        debugColour.r = 255;
//        debugColour.g = 255;
//        debugColour.b = 255;
//        char buffer[50];
//        sprintf(buffer, "Boss Bullets: %i", this->game->bossBullets.size());
//        FontUtils::drawString(this->game->pFont, debugColour, buffer, 0, 200, this->game->pScreen);
//        sprintf(buffer, "Player Bullets: %i", this->game->playerBullets.size());
//        FontUtils::drawString(this->game->pFont, debugColour, buffer, 0, 200+45, this->game->pScreen);

    if (this->game->boss.isDead() == false)
    {
        if (underAttackTimer.getTicks() > 0)
        {
            filledCircleRGBA(this->game->pScreen, this->game->boss.getX(), this->game->boss.getY(), this->game->boss.getRadius(), 160, 160, 255, 255);
            circleRGBA(this->game->pScreen, this->game->boss.getX(), this->game->boss.getY(), this->game->boss.getRadius(), 255, 255, 255, 255);
            if (underAttackTimer.getTicks()> 100)
                underAttackTimer.stop();
        }
        else
        {
            filledCircleRGBA(this->game->pScreen, this->game->boss.getX(), this->game->boss.getY(), this->game->boss.getRadius(), 160, 160, 255, 255);
        }
    }
    else
    {
        SDL_Color winColour;
        winColour.r = 255;
        winColour.g = 255;
        winColour.b = 255;

        FontUtils::drawString(this->game->pFont, winColour, "YOU WIN!!!", 260, 240-22, this->game->pScreen);
        filledCircleRGBA(this->game->pScreen, this->game->boss.getX(), this->game->boss.getY(), this->game->boss.getRadius(), 0, 0, 0, 255);


        if (explodeEffectTimer.getTicks() > 500)
        {
            Mix_PlayChannel(-1, this->game->bossExplodeSound, 0);
            explodeEffectTimer.stop();
            explodeEffectTimer.start();
        }
        for(int i = 0; i < 100; i++)
        {
            float dx = ((float)(rand() / (float)RAND_MAX) -((float)rand() / (float)RAND_MAX));
            float dy = ((float)(rand() / (float)RAND_MAX) -((float)rand() / (float)RAND_MAX));

            filledCircleRGBA(this->game->pScreen, this->game->boss.getX()+dx*this->game->boss.getRadius(), this->game->boss.getY()+dy*this->game->boss.getRadius(), 5, 255, 255, 0, 255);
        }
    }

    if (this->game->mouse.getButton1() == true)
    {
        // Draw Player
        filledCircleRGBA(this->game->pScreen, this->game->player.getX(), this->game->player.getY(), this->game->player.getRadius(), 160, 160, 255, 255);
        circleRGBA(this->game->pScreen, this->game->player.getX(), this->game->player.getY(), this->game->player.getRadius(), 255, 255, 255, 255);
    }
    else
    {
        // Draw Player
        filledCircleRGBA(this->game->pScreen, this->game->player.getX(), this->game->player.getY(), this->game->player.getRadius(), 160, 160, 255, 255);
    }

    // Draw Players Gun
    float dx = (this->game->mouse.getX() - this->game->player.getX());
    float dy = (this->game->mouse.getY() - this->game->player.getY());
    float dm = sqrt(dx * dx + dy * dy);
    if (fabs(dm) < 1) dm = 1;
    dx = (dx / dm) * this->game->player.getRadius();
    dy = (dy / dm) * this->game->player.getRadius();
    lineRGBA(this->game->pScreen, this->game->player.getX(), this->game->player.getY(), this->game->player.getX() + dx, this->game->player.getY() + dy, 0, 0, 0, 255);
    filledCircleRGBA(this->game->pScreen, this->game->player.getX() + dx, this->game->player.getY() + dy, 2, 0, 0,0, 255);

    for (std::vector<Bullet>::iterator iter = this->game->playerBullets.begin(); iter != this->game->playerBullets.end(); iter++)
    {
        filledCircleRGBA(this->game->pScreen, (*iter).getX(), (*iter).getY(), (*iter).getRadius(), 255, 255, 0, 255);
    }

    for (std::vector<Bullet>::iterator iter = this->game->bossBullets.begin(); iter != this->game->bossBullets.end(); iter++)
    {
        filledCircleRGBA(this->game->pScreen, (*iter).getX(), (*iter).getY(), (*iter).getRadius(), 255, 255, 0, 255);
    }

    SDL_Circle bossCircle;
    bossCircle.x = this->game->boss.getX();
    bossCircle.y = this->game->boss.getY();
    bossCircle.radius = this->game->boss.getRadius();

    SDL_Circle mouseCircle;
    mouseCircle.x = this->game->mouse.getX();
    mouseCircle.y = this->game->mouse.getY();
    mouseCircle.radius = 20;

    if (Physics::isCollision(bossCircle, mouseCircle) && this->game->boss.isDead() == false)
    {
        circleRGBA(this->game->pScreen, this->game->mouse.getX(), this->game->mouse.getY(), 2, 255, 0, 0, 255);
        boxRGBA(this->game->pScreen, this->game->mouse.getX()-1, this->game->mouse.getY() - 10, this->game->mouse.getX()+1, this->game->mouse.getY() - 20, 255, 0, 0, 255);
        boxRGBA(this->game->pScreen, this->game->mouse.getX()-1, this->game->mouse.getY() + 10, this->game->mouse.getX()+1, this->game->mouse.getY() + 20, 255, 0, 0, 255);
        boxRGBA(this->game->pScreen, this->game->mouse.getX()-10, this->game->mouse.getY()-1, this->game->mouse.getX()-20, this->game->mouse.getY() + 1, 255, 0, 0, 255);
        boxRGBA(this->game->pScreen, this->game->mouse.getX()+10, this->game->mouse.getY()-1, this->game->mouse.getX()+20, this->game->mouse.getY() + 1, 255, 0, 0, 255);
    }
    else
    {
        circleRGBA(this->game->pScreen, this->game->mouse.getX(), this->game->mouse.getY(), 2, 0, 255, 0, 255);
        boxRGBA(this->game->pScreen, this->game->mouse.getX()-1, this->game->mouse.getY() - 10, this->game->mouse.getX()+1, this->game->mouse.getY() - 20, 0, 255, 0, 255);
        boxRGBA(this->game->pScreen, this->game->mouse.getX()-1, this->game->mouse.getY() + 10, this->game->mouse.getX()+1, this->game->mouse.getY() + 20, 0, 255, 0, 255);
        boxRGBA(this->game->pScreen, this->game->mouse.getX()-10, this->game->mouse.getY()-1, this->game->mouse.getX()-20, this->game->mouse.getY() + 1, 0, 255, 0, 255);
        boxRGBA(this->game->pScreen, this->game->mouse.getX()+10, this->game->mouse.getY()-1, this->game->mouse.getX()+20, this->game->mouse.getY() + 1, 0, 255, 0, 255);
    }
    SDL_Flip(this->game->pScreen);
    boxRGBA(this->game->pScreen, 0, 0, 640, 480, 64, 64, 224, 255);
    boxRGBA(this->game->pScreen, 0, 0, 640, 45, 0, 0, 0, 255);
    //boxRGBA(this->game->pScreen, 0, 45, 640, 65, 128, 128, 128, 255);
    boxRGBA(this->game->pScreen, 0, 440, 640, 480, 0, 0, 0, 255);

}

void BattleGameState::onExit()
{
}

void BattleGameState::doPlayer()
{
    // Reset Player speed
    this->game->player.setXVelocity(0.0f);
    this->game->player.setYVelocity(0.0f);
    // Make the player move based on input
    if (this->game->pKeys[SDLK_w])
    {
        this->game->player.setYVelocity(-this->game->playerSpeed);
    }
    if (this->game->pKeys[SDLK_a])
    {
        this->game->player.setXVelocity(-this->game->playerSpeed);
    }
    if (this->game->pKeys[SDLK_s])
    {
        this->game->player.setYVelocity(this->game->playerSpeed);
    }
    if (this->game->pKeys[SDLK_d])
    {
        this->game->player.setXVelocity(this->game->playerSpeed);
    }
    // Keep player restricted to Screen Bounds
    if (this->game->player.getX() - this->game->player.getRadius() < 0)
    {
        this->game->player.setX(0 + this->game->player.getRadius());
    }
    if (this->game->player.getX() > 640 - this->game->player.getRadius())
    {
        this->game->player.setX(640 - this->game->player.getRadius());
    }
    if (this->game->player.getY() - this->game->player.getRadius() < 45)
    {
        this->game->player.setY(45 + this->game->player.getRadius());
    }
    if (this->game->player.getY() > 440 - this->game->player.getRadius())
    {
        this->game->player.setY(440 - this->game->player.getRadius());
    }
    // Make the player shoot
    if (this->game->mouse.isLeftClick() == true || this->game->pKeys[SDLK_SPACE])
    {
        float dx = (this->game->mouse.getX() - this->game->player.getX());
        float dy = (this->game->mouse.getY() - this->game->player.getY());
        float dm = sqrt(dx * dx + dy * dy);
        if (fabs(dm) < 1) dm = 1;
        dx = (dx / dm);
        dy = (dy / dm);
        Bullet bullet;
        bullet.setRadius(5.0f);
        bullet.setX(this->game->player.getX() + dx * (this->game->player.getRadius() + bullet.getRadius()));
        bullet.setY(this->game->player.getY() + dy * (this->game->player.getRadius() + bullet.getRadius()));
        bullet.setXVelocity(dx*5);
        bullet.setYVelocity(dy*5);
        this->game->playerBullets.push_back(bullet);
        Mix_PlayChannel(-1, this->game->playerShootSound, 0);
    }
//    if (this->game->mouse.isLeftClick() == true)
//    {
//        createBossBullet(this->game->player.getX(), this->game->player.getY(), 1, 0);
//    }

}

void BattleGameState::doPlayerBullets()
{
    SDL_Circle bossCircle;
    bossCircle.x = this->game->boss.getX();
    bossCircle.y = this->game->boss.getY();
    bossCircle.radius = this->game->boss.getRadius();
    int numberOfBulletsHittingBoss = 0;
    for (std::vector<Bullet>::iterator iter = this->game->playerBullets.begin(); iter != this->game->playerBullets.end(); iter++)
    {
        SDL_Circle bullet;
        bullet.x = (*iter).getX();
        bullet.y = (*iter).getY();
        bullet.radius = (*iter).getRadius();
        if (Physics::isCollision(bossCircle, bullet))
        {
            this->game->playerBullets.erase(iter);
            iter--;
            if (this->game->boss.isImmuneToDamage() == false)
            {
                this->game->boss.setUnderAttack(true);
                underAttackTimer.start();
                numberOfBulletsHittingBoss++;
                this->game->boss.setHealth(this->game->boss.getHealth() - 2);
                Mix_PlayChannel(-1, this->game->bossHitSound, 0);
            }
            continue;
        }

        if ((*iter).getX() + (*iter).getRadius() < 0)
        {
            this->game->playerBullets.erase(iter);
            iter--;
            continue;
        }
        if ((*iter).getX() - (*iter).getRadius() > 640)
        {
            this->game->playerBullets.erase(iter);
            iter--;
            continue;
        }
        if ((*iter).getY() + (*iter).getRadius() < 55)
        {
            this->game->playerBullets.erase(iter);
            iter--;
            continue;
        }
        if ((*iter).getY() - (*iter).getRadius() > 425)
        {
            this->game->playerBullets.erase(iter);
            iter--;
            continue;
        }
    }
    if (numberOfBulletsHittingBoss == 0 && this->game->boss.isUnderAttack() == true)
    {
        this->game->boss.setUnderAttack(false);
    }
}

void BattleGameState::doBoss()
{
    lua_getglobal(this->game->pBossScript, "main");
    lua_call(this->game->pBossScript, 0, 0);
    // Draw the Boss bar
    boxRGBA(this->game->pScreen, 640/2-100, 10, 640/2+100,30, 255, 0, 0, 255 ); // draw boss bar background
    unsigned int modifier = ((float)this->game->boss.getHealth()/ (float)this->game->boss.getMaxHealth()) * 200.0f; // Calculate health space
    boxRGBA(this->game->pScreen, 640/2-100, 10, 640/2-100 + modifier,30, 255, 255, 0, 255 ); // draw boss bar
}

void BattleGameState::doBossBullets()
{
    for (std::vector<Bullet>::iterator iter = this->game->bossBullets.begin(); iter != this->game->bossBullets.end(); iter++)
    {
        if ((*iter).getX() + (*iter).getRadius() < 0)
        {
            this->game->bossBullets.erase(iter);
            iter--;
            continue;
        }
        if ((*iter).getX() - (*iter).getRadius() > 640)
        {
            this->game->bossBullets.erase(iter);
            iter--;
            continue;
        }
        if ((*iter).getY() + (*iter).getRadius() < 0)
        {
            this->game->bossBullets.erase(iter);
            iter--;
            continue;
        }
        if ((*iter).getY() - (*iter).getRadius() > 480)
        {
            this->game->bossBullets.erase(iter);
            iter--;
            continue;
        }
    }
}

void BattleGameState::createBossBullet(float x, float y, float xVel, float yVel)
{
    Bullet bullet;
    bullet.setRadius(5.0f);
    bullet.setX(x);
    bullet.setY(y);
    bullet.setXVelocity(xVel);
    bullet.setYVelocity(yVel);
    this->game->bossBullets.push_back(bullet);
}

void BattleGameState::bossSpeak(const char* text)
{
    SDL_Color debugColour;
    debugColour.r = 255;
    debugColour.g = 255;
    debugColour.b = 255;
    FontUtils::drawString(this->game->pFont, debugColour, text, 0, 480-45, this->game->pScreen);
}

void BattleGameState::bindToLua(lua_State* luaState)
{
    luabind::module(luaState)
    [
        luabind::class_<BattleGameState>("BattleGameState")
        .def("bossSpeak", (void(BattleGameState::*)(const char*))& BattleGameState::bossSpeak)
        .def("createBossBullet", (void(BattleGameState::*)(float x, float y, float xVel, float yVel))& BattleGameState::createBossBullet)
    ];
}

void BattleGameState::restart()
{
    Mix_VolumeMusic(MIX_MAX_VOLUME/2);
    Mix_PlayMusic(this->game->battleMusic, -1);
    this->game->player.setRadius(20);
    this->game->player.setX(140);
    this->game->player.setY(480/2);
    this->game->playerSpeed = 2.0f;
    this->game->player.setHealth(100);
    this->game->player.setMaxHealth(100);

    this->game->boss.setRadius(50);
    this->game->boss.setX(500);
    this->game->boss.setY(480/2);
    this->game->boss.setMaxHealth(300);
    this->game->boss.setHealth(300);
    this->game->boss.setUnderAttack(false);
    this->game->boss.setState("");
    this->game->boss.setDead(false);
    youWinTimer.stop();
    explodeEffectTimer.stop();
    this->game->bossBullets.clear();
    this->game->playerBullets.clear();
}


