#ifndef TIMER_H
#define TIMER_H


class TIMER
{
public:
    TIMER();
    ~TIMER();

    void start();
    void stop(); 
    void paused();
    void unpaused();

    void dead();

    int get_ticks();


    bool is_started_();
    bool is_paused_();


private:
    int start_tick;
    int pause_tick;

    bool is_paused;
    bool is_started;
};




#endif