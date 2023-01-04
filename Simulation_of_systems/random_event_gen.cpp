#include <vector>
#include <algorithm>
#include <random>

#include "random_event_gen.h"
#include "error.h"

static std::vector<Event> produce_raw_events()
{
    //exponential distribution with rate 2.1
    std::random_device rd1;
    std::exponential_distribution<> exp(2.1);

    //uniform real distribution in range [0.4, 0.6]
    std::random_device rd2;
    std::uniform_real_distribution<> uni(0.4, 0.6);

    // for each task there is one arrival and one departure
    std::vector<Event> arrival_list(NO_OF_TASKS);
    std::vector<Event> departure_list(NO_OF_TASKS);

    // for now make only D events, later they will be converted to either D1 or D2
    for (int i = 0; i < NO_OF_TASKS; ++i)
    {
        // create random arrivals and departures
        arrival_list[i] = { A, exp(rd1) };
        departure_list[i] = { D, uni(rd2) };
    }
    // sort arrivals according to time
    std::sort(arrival_list.begin(), arrival_list.end(), []( const Event &ev1, const Event &ev2)
    {
        return (ev1.time < ev2.time);
    });
    // create the actual departure times
    // by adding departure [0.4, 0.6] to arrival time
    for (int i = 0; i < NO_OF_TASKS; ++i)
    {
        departure_list[i].time = arrival_list[i].time + departure_list[i].time;
    }
    // sort departures by time
    std::sort(departure_list.begin(), departure_list.end(), []( const Event &ev1, const Event &ev2)
    {
        return (ev1.time < ev2.time);
    });

    std::vector<Event> ev_list;
    // merge arrivals and departures to one big sorted event list
    std::merge(arrival_list.begin(), arrival_list.end(), 
               departure_list.begin(), departure_list.end(),
               std::back_inserter(ev_list), []( const Event &ev1, const Event &ev2)
    {
        return (ev1.time < ev2.time);
    });

    return ev_list;
}

std::vector<Event> produce_events()
{
    std::random_device rd;
    std::uniform_int_distribution<> binary(0, 1);
    // this list contains only A and D events
    auto raw_ev_list = produce_raw_events();
    // we need to convert to D1 and D2 events

    // state = 0 means Idle Idle
    // state = 1 means Idle Busy
    // state = 2 means Busy Idle
    // state = 3 means Busy Busy
    // state > 3 means Busy Busy and non empty queue
    unsigned state = 0;

    for (Event &ev: raw_ev_list)
    {
        if (ev.type == A) state++; // on arrival add one to state
        else 
        {
            if (state == 0) error("Can't have departure on empty system"); // cant have a departure on empty system
            else if (state == 1) ev.type = D1; // if departure on IDLE-BUSY state set to D1
            else if (state == 2) ev.type = D2; // if departure on BUSY-IDLE state set to D2
            else                 ev.type = (binary(rd))? D1 : D2; // else departure is random
            
            state--; // decremen the state variable
        }
    }

    return raw_ev_list;
}