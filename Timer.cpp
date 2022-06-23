#include "Timer.h"

Timer::Timer()
{
    tick = pause = false;
    startPauseTime = startTime = stopTime = allPauseTime = 0;
}

Timer::~Timer()
{
    //dtor
}

void Timer::Start() {
    tick = true;
    pause = false;
    startPauseTime = allPauseTime = 0;
    startTime = SDL_GetTicks();
}

void Timer::Stop(){
    if (!tick) return;

    tick = false;
    if (pause) allPauseTime += SDL_GetTicks() - startPauseTime;
    stopTime = SDL_GetTicks();

    pause = false;
}

void Timer::Pause(){
    if (pause || !tick) return;

    pause = true;
    startPauseTime = SDL_GetTicks();
}

void Timer::Unpause(){
    if (!pause || !tick) return;

    pause = false;
    allPauseTime += SDL_GetTicks() - startPauseTime;
}

void Timer::Reset(){
    tick = pause = false;
    startPauseTime = startTime = stopTime = allPauseTime = 0;
}

Uint32 Timer::GetMilliseconds(){
    if (tick && !pause)
        return SDL_GetTicks() - startTime - allPauseTime;
    else if (tick && pause)
        return startPauseTime - startTime - allPauseTime;
    else if (!tick)
        return stopTime - startTime - allPauseTime;
}
