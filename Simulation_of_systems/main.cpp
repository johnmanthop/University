#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <queue>

#include "simulation.h"
#include "random_event_gen.h"
#include "error.h"

/*
 * Ioannis Manthopoulos
 * 3579
 */

int main()
{
    // produce random events
    auto ev_list = produce_events();
    // from the events create the tasks
    auto simulation = simulate(ev_list);

    Metrics metrics = calculate_metrics(simulation);
    print_metrics(metrics);

    return 0;
}