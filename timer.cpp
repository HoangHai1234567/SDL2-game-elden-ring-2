#include "timer.h"
#include "commnonfunct.h"


TIMER :: TIMER()
{
    start_tick = 0;
    pause_tick = 0;
    is_paused = false;
    is_started = false;
}

TIMER :: ~TIMER()
{

}

void TIMER :: start()
{
    is_started = true;
    is_paused = false;
    start_tick = SDL_GetTicks();
    //cout << start_tick << endl;
}

void TIMER :: stop()
{
    is_paused = false;
    is_started = false;
}

void TIMER :: paused()
{
    if ( is_started == true && is_paused == false )
    {
        is_paused = true;
        pause_tick = SDL_GetTicks() - start_tick;
    }
}

void TIMER :: unpaused()
{
    if (is_paused == true)
    {
        is_paused = false;
        start_tick = SDL_GetTicks() - pause_tick;
        pause_tick = 0;
    }
}

int TIMER :: get_ticks()
{
    if ( is_started == true )
    {
        return pause_tick;
    }
    else
    {
        return SDL_GetTicks() - start_tick;
    }

    return 0;
}

bool TIMER :: is_started_()
{
    return is_started;
}

bool TIMER :: is_paused_()
{
    return is_paused;
}



