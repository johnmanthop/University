#include <algorithm>
#include <cassert>

#include "Dataset.h"

void Dataset::sort()
{
    // create custom lambda comparator
    // could also be done with an overloaded operator
    std::sort(dataset.begin(), dataset.end(), [](const Distance_Data &d1, const Distance_Data &d2) 
                                                { 
                                                    return d1.timestamp < d2.timestamp;
                                                });
}

std::vector<double> Dataset::get_distances_from_beacons(int index, int lower_lim, int upper_lim) const
{
    auto timestamp = dataset[index];
    std::vector<double> result;

    // copy distance values of lower_lim beacon to upper_lim beacon
    std::copy(timestamp.distances.begin() + lower_lim, timestamp.distances.begin() + upper_lim, result.begin());

    return result;
}

void Dataset::filter_matrix()
{
    for (auto it = dataset.begin(); it != dataset.end();)
    {
        bool contaminated = false;

        for (auto distance: it->distances)
        {
            if (distance <= 0) contaminated = true;
        }
        
        // earse contaminated data entries
        if (contaminated)
        {
            dataset.erase(it);
        }
        else 
        {
            it++;
        }
    }
}

void Dataset::correctness_check() const
{
    for (auto it = dataset.cbegin(); it != dataset.cend(); it++)
    {
        for (auto distance: it->distances)
        {
            // hopefully this is always true
            assert(distance > 0);
        }
    }
}