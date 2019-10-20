#ifndef TIMER_H
#define TIMER_H

#include "SDL/SDL.h"
#include "LuaBind/LuaBind.hpp"

/** A general purpose timer class. All values are in milliseconds (m/secs) */
class Timer
{
    public:
        //! Constructor
        Timer() : startTime( 0 ), pausedTime( 0 ), totalPausedTime( 0 ), paused( false ) {}
        //! Destructor
        virtual ~Timer() {}

        //! must call this function to start the timer
        /** calling start again will reset the timer
        use pause and resume to suspend the timer */
        void start();

        //! stop the timer
        /** must use start() if using same timer again */
        void stop();

        //! pause the timer
        /** tracks how much time passes while paused */
        void pause();

        //! resume the current timer
        /** adjusts game time to not count the paused time */
        void resume();

        //! number of m/secs since start() was executed
        /** \return the number of msecs passed since game start
        or 0 if not started or is paused */
        unsigned getTicks();

        //! tracks how many m/secs have passed since the function was last called.
        /** Useful for general purpose timing.
        When used once only in an update and draw cycle for example.
        \return m/secs passed since getDelta() last called */
        unsigned getDelta();

        //! tracks how many m/secs have passed while paused.
        /** Probably useful only for general stats.
        \return m/secs passed in paused state */
        unsigned getTotalPausedTime();

        //! has timer started */
        /** \return true if timer has started */
        bool isStarted();

        //! has timer paused */
        /** \return true if timer is paused */
        bool isPaused();

        //! Bind this class to a lua state
        static void bindToLua(lua_State* pLuaState);

    private:
        //! the system time when the timer starts
        unsigned startTime;
        //! time at which the pause method was called
        unsigned pausedTime;
        //! time passed during a pause
        unsigned totalPausedTime;
        //! timer has paused
        bool paused;
};

inline bool Timer::isStarted()
{
    // if the startTime is 0 then not started yet
    return ( startTime ) ? true : false;
}

inline bool Timer::isPaused()
{
    return paused;
}

inline unsigned int Timer::getTotalPausedTime()
{
    return totalPausedTime;
}

#endif // TIMER_H
