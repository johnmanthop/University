#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <array>

/**
 * Structure representing a set of 6 meassured distances
 */
struct Distance_Data
{
    int timestamp;
    std::array<double, 6> distances; 

    Distance_Data() {}
    Distance_Data(int t, const std::array<double, 6> d):
        timestamp(t), distances(d)
    {}
};

/**
 * Internal representation of the list of distance data
 */
class Dataset
{
private:
    std::vector<Distance_Data> dataset;
public:
    Dataset(const std::vector<Distance_Data> &d):
        dataset(d)
    {  }

    int                 get_dataset_size()                              const { return dataset.size(); }
    int                 get_timestamp(int index)                        const { return dataset[index].timestamp; }
    double              get_distance_from_beacon(int index, int beacon) const { return dataset[index].distances[beacon]; }

    /**
     * Returns a list of distances based on a range of beacons
     * @param index
     * @param lower_lim
     * @param upper_lim
     * @return A list of distance values from the index timestamp and the lower_lim to upper_lim beacon index 
     */
    std::vector<double> get_distances_from_beacons(int index, int lower_lim, int upper_lim) const;

    /**
     * Sort the dataset according to timestamp
     */
    void sort();

    /**
     * Filter dataset of zero and negative distances
     */
    void filter_matrix();

    /**
     * Sanity check of the filter_matrix function 
     */
    void correctness_check() const;
};

#endif 