#ifdef __linux__

#include "betriebsmittelverwaltung.h"
#include <sys/time.h>                // for gettimeofday()

static double lastTime = 0.0;

void timer1_simulate()
{
    struct timeval t1;
    double elapsedTime, steps = 0;

    // start timer
    gettimeofday(&t1, NULL);

    // compute and print the elapsed time in millisec
    elapsedTime = t1.tv_sec * 1000.0;      // sec to ms
    elapsedTime += t1.tv_usec / 1000.0;   // us to ms

    if(lastTime != 0.0) 
    {
        steps = (int)((elapsedTime - lastTime) / 10);
        lastTime += steps * 10;
        timer_value[TIMER_LEITZENTRALE]+=steps;
    }
    else
    {
        lastTime = elapsedTime;
    }
}

#else

#include "betriebsmittelverwaltung.h"
#include <windows.h> 

static double lastTime = 0.0;

void timer1_simulate()
{
    LARGE_INTEGER frequency;    // ticks per second
    LARGE_INTEGER t1;           // ticks
    double elapsedTime, steps = 0;

    // get ticks per second
    QueryPerformanceFrequency(&frequency);

    // start timer
    QueryPerformanceCounter(&t1);

    // compute and print the elapsed time in millisec
    elapsedTime = t1.QuadPart * 1000.0 / frequency.QuadPart;

    if(lastTime != 0.0) 
    {
        steps = (int)((elapsedTime - lastTime) / 10);
        lastTime += steps * 10;
        timer_value[TIMER_LEITZENTRALE]+=steps;
    }
    else 
    {
        lastTime = elapsedTime;
    }
}


#endif
