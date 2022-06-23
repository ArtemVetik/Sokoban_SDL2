#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

class Timer
{
    public:
        Timer();
        ~Timer();

        void Start();
        void Pause();
        void Unpause();
        void Stop();
        void Reset();

        Uint32 GetMilliseconds();

    private:
        bool tick, pause;
        Uint32 startTime, stopTime, startPauseTime, allPauseTime;

};

#endif // TIMER_H
