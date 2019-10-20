#include "Timer.h"

void Timer::start()
{
    // set the time at which the time started
    startTime = SDL_GetTicks();
    // set paused status to false
    paused = false;
    // reset the amount of time this time has been caused
    totalPausedTime = 0;
}

void Timer::stop()
{
    // set the start time to 0
    startTime = 0;
    // set paused status to false
    paused = false;
}

void Timer::pause()
{
    // if the timer is not already paused then pause it
    if ( paused == false )
    {
        // set paused status to true
        paused = true;
        // store the time at which the pause instruction was executed
        pausedTime = SDL_GetTicks();
    }
}

void Timer::resume()
{
    // if the timer is paused then resume it
    if ( paused == true )
    {
        // set paused status to false
        paused = false;
        // save total time level timer has been paused
        totalPausedTime += SDL_GetTicks() - pausedTime;
    }
}

unsigned int Timer::getTicks()
{
    // if the timer is paused and has not been stopped
    if ( paused == true && startTime != 0 )
    {
        // return the time at which the timer was paused
        return pausedTime - startTime - totalPausedTime;
    }
    // if the timer has been stopped
    if ( startTime == 0 )
    {
        // return zero because the timer has been stopped
        return 0;
    }
    // return the total time running minus time paused
    return SDL_GetTicks() - startTime - totalPausedTime;

}

unsigned int Timer::getDelta()
{
    // keep a record of the last time this function was called
    static unsigned timeLast = this->getTicks();
    // get the current time ( relative to this timer )
    unsigned timeNow = this->getTicks();
    // the number of m/secs since last called
    unsigned timeDelta = timeNow - timeLast;
    // save the current time
    timeLast = timeNow;
    // the amount of time since the last access to this function
    return timeDelta;
}

void Timer::bindToLua(lua_State* pLuaState)
{
    // Bind functions to lua state
    luabind::module(pLuaState)
    [
        luabind::class_<Timer>("Timer")
        .def(luabind::constructor<>())
        .def("start", &Timer::start )
        .def("stop", &Timer::stop )
        .def("pause", &Timer::pause )
        .def("resume", &Timer::resume )
        .def("getTicks", &Timer::getTicks )
        .def("getDelta", &Timer::getDelta )
        .def("getTotalPausedTime", &Timer::getTotalPausedTime )
        .def("isStarted", &Timer::isStarted )
        .def("isPaused", &Timer::isPaused )
    ];
}

