#ifndef ISTATE_H
#define ISTATE_H

class Game;

class IState
{
    public:
        IState(Game* game)
        {
            this->game = game;
        }
        virtual ~IState() {}
        virtual void onEnter() = 0;
        virtual void think() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual void onExit() = 0;

    protected:
        Game* game;
};

#endif // ISTATE_H
