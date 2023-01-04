#ifndef RANDOM_EVENT_GEN
#define RANDOM_EVENT_GEN

#define NO_OF_TASKS 52000

enum EV_TYPE { A, D, D1, D2 };
struct Event
{
    EV_TYPE type;
    double time;
};

std::vector<Event> produce_events();

#endif