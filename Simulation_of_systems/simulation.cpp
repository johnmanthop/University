#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#include "simulation.h"
#include "random_event_gen.h"
#include "error.h"

void print_events(const std::vector<Event> &ev_list)
{
    int k = 0;
    for (Event ev: ev_list)
    {
        std::cout << k++ << "> ";
        if (ev.type == A) std::cout << "Arrival at: ";
        else if (ev.type == D1) std::cout << "Departure1 at: ";
        else std::cout << "Departure2 at: ";

        std::cout << ev.time << '\n';
    }
}

void print_tasks(const std::vector<Task*> &task_list)
{
    int k = 0;
    for (auto task: task_list)
    {
        std::cout << k++ << "> ";
        std::cout << "arrival at: " << task->arrival_time <<
                     " service at: " << task->serve_time <<
                     " departure at: " << task->departure_time << '\n';
    }
}

/*
 * Takes as input the event list and produces the corresponding task list
 */
std::tuple<std::vector<Task*>, unsigned, unsigned> simulate(const std::vector<Event> &ev_list)
{
    std::vector<Task*> task_list;
    Server s;
    // at first server is idle-idle
    s.s1 = nullptr;
    s.s2 = nullptr;

    double area_under_queue = 0;
    double area_under_system = 0;
    // previous event time
    double last_event = 0;

    // for every event
    for (auto ev: ev_list)
    {
        // if event is arrival
        if (ev.type == A)
        {
            // if server is Idle-Idle
            if (s.s1 == nullptr && s.s2 == nullptr)
            {
                // add a new task to s1
                // the task's arrival time and service time is the event time
                // the departure time will be calculated later
                s.s1 = new Task { ev.time, ev.time, -1 };
            }
            // same if server is idle-busy
            else if (s.s1 == nullptr && s.s2 != nullptr)
            {
                s.s1 = new Task { ev.time, ev.time, -1 };
            }
            // if server is busy-idle
            // add the task to s2
            else if (s.s1 != nullptr && s.s2 == nullptr)
            {
                s.s2 = new Task { ev.time, ev.time, -1 };
            }
            else // if both are busy
            {
                // if both are busy add task to queue
                // in this case only arrival time is known
                // both service and departure time will be calculated later
                s.Q.push(new Task { ev.time, -1, -1 });
            }
        }
        else // if event is departure
        {
            if (s.s1 == nullptr && s.s2 == nullptr) error("Can't have departure on empty system"); // cant have departure on empty system
            // if server is idle-busy
            else if (s.s1 == nullptr && s.s2 != nullptr)
            {
                if (s.Q.size()) error("Can't have non-empty queue and an idle server"); // cant have non empty Q and an idle server
                else // if queue is empty (it should be) 
                {
                    // if for some reason event does not correlate to the system state, go to error
                    if (ev.type != D2) error("Wrong departure correlation");

                    // otherwise remove task from s2, set its departure time and add it to task list
                    s.s2->departure_time = ev.time;
                    task_list.push_back(s.s2);
                    s.s2 = nullptr;
                }
            }
            // same if server is busy-idle
            else if (s.s1 != nullptr && s.s2 == nullptr)
            {
                if (s.Q.size()) error("Can't have non-empty queue and an idle server"); // cant have non empty Q and an idle serve
                else 
                {
                    if (ev.type != D1) error("Wrong departure correlation");

                    // remove task from s1, set its departure time and add to task list
                    s.s1->departure_time = ev.time;
                    task_list.push_back(s.s1);
                    s.s1 = nullptr;
                }
            }
            else // if both are busy
            {
                // if departure from s1
                if (ev.type == D1)
                {
                    // remove from s1 same as before
                    s.s1->departure_time = ev.time;
                    task_list.push_back(s.s1);
                    s.s1 = nullptr;
                }
                else 
                {
                    // remove from s2 as before
                    s.s2->departure_time = ev.time;
                    task_list.push_back(s.s2);
                    s.s2 = nullptr;
                }
                // but before leaving, if the Q is non empty, add next task imidiately
                if (s.Q.size())
                {
                    auto next_task = s.Q.front();
                    s.Q.pop();
                    // if the task is from queue, its service time needs to be set now
                    if (ev.type == D1)
                    {
                        next_task->serve_time = ev.time;
                        s.s1 = next_task;
                    }
                    else 
                    {
                        next_task->serve_time = ev.time;
                        s.s2 = next_task;
                    }
                }
            }
        }
        // area under queue is the queue size every time step
        area_under_queue  += s.Q.size() * (ev.time - last_event);
        // area under system is queue size plus 0, 1 or 2 depending on how many tasks are in the server currently
        area_under_system += (s.Q.size() + 
                             ((s.s1 == nullptr)?0:1) + 
                             ((s.s2 == nullptr)?0:1)) * (ev.time - last_event);
        // save last event's time
        last_event = ev.time;
    }

    // sort task list according to arrival time, not required but for simplicity
    std::sort(task_list.begin(), task_list.end(), [](Task *a, Task *b) {
        return (a->arrival_time < b->arrival_time);
    });
    // return task list and area under two curves
    return { task_list, area_under_queue, area_under_system };
}

Metrics calculate_metrics(const std::tuple<std::vector<Task*>, unsigned, unsigned> &simulation)
{
    Metrics metrics { 0, 0, 0, 0, 0, 0, 0, 0 };

    auto task_list = std::get<0>(simulation);

    for (auto task: task_list)
    {
        // accumulate response and waiting times
        metrics.total_response_time += (task->departure_time - task->arrival_time);
        metrics.total_waiting_time += (task->serve_time - task->arrival_time);
    }
    // divide by number of tasks to find average
    metrics.avg_response_time = (metrics.total_response_time / NO_OF_TASKS);
    metrics.avg_waiting_time = (metrics.total_waiting_time / NO_OF_TASKS);

    // find last departure
    Task *last_departed = *std::max_element(task_list.begin(), task_list.end(), [](Task *a, Task *b) 
    {
        return a->departure_time < b->departure_time;
    });
    // time of simulation ends at last departure time
    double last_departure = last_departed->departure_time;

    double area_under_queue  = std::get<1>(simulation);
    double area_under_system = std::get<2>(simulation);
    // divide area by total time to find avg
    metrics.avg_no_of_tasks_in_queue  = area_under_queue / last_departure;
    metrics.avg_no_of_tasks_in_system = area_under_system / last_departure;

    return metrics;
}

void print_metrics(const Metrics &metrics)
{
    std::cout << "Metrics: \n";
    std::cout << "Average response time: " << metrics.avg_response_time << '\n';
    std::cout << "Average waiting time: " << metrics.avg_waiting_time << '\n';
    std::cout << "Average no of tasks in queue: " << metrics.avg_no_of_tasks_in_queue << '\n';
    std::cout << "Average no of tasks in system: " << metrics.avg_no_of_tasks_in_system << '\n';
}