#ifndef TIMER_HPP
#define TIMER_HPP

class timerClass
{
public:
    void start();
    void update();
    double getTime();
private:
    double time;
};

#endif

