#ifndef SIMULATION
#define SIMULATION

#include <queue>

#include "random_event_gen.h"

struct Task
{
    // if we have these three we can calculate response and waiting time
    double arrival_time;
    double serve_time;
    double departure_time;
};

struct Server
{
    // server can have 2 tasks at hand, or nullptr if no task is executed
    Task *s1;
    Task *s2;

    std::queue<Task*> Q; // and one queue of waiting tasks
};

struct Metrics
{
    double total_response_time; // total time tasks spent in the system
    double total_waiting_time;  // total time tasks waited in the system

    double avg_response_time; 
    double avg_waiting_time;

    int area_under_queue;
    int area_under_system;

    double avg_no_of_tasks_in_system;
    double avg_no_of_tasks_in_queue;
};

std::tuple<std::vector<Task*>, unsigned, unsigned> simulate(const std::vector<Event> &ev_list);
Metrics calculate_metrics(const std::tuple<std::vector<Task*>, unsigned, unsigned> &simulation);
void print_metrics(const Metrics &metrics);

#endif