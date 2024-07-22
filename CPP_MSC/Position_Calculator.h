#ifndef POSITION_CALCULATOR_H
#define POSITION_CALCULATOR_H

#include <utility>

#include "Dataset.h"
#include "Plane.h"

/**
 * Structure representing a position in space at a given timestamp
 * A list of position_data is the path taken by the robot
 */
struct Position_Data
{
    int timestamp;
    Point position;

    Position_Data(int t, const Point &p):
        timestamp(t), position(p)
    {  }
    Position_Data() {  }
};

class Position_Calculator
{
private:
    Dataset dataset;
    Plane plane;
private:
    /**
     * Implementation of 3-point trilateration, see README.MD for details
     * @param points    Array containing 3 beacon points
     * @param distances Array containing 3 distance values
     * @return          The calculated antenna position
     */
    Point trilateration(const std::array<Point, 3> &points, const std::array<double, 3> &distances) const;

    /**
     * Finds the average point of an input set of points
     * @param points    A set of points
     * @return          The average (center) point
     */
    Point find_center_point(const std::vector<Point> &points) const;

    /**
     * Breaks the beacon set onto subsets containing 3 beacons each
     * @return The list of subsets
     */
    std::vector<std::array<Point, 3>> create_beacon_triplet_set() const;

    /**
     * Braks the distance values set onto subsets containing 3 values each
     * @param index     The timestamp index to read the values from
     * @return          The list of subsets
     */
    std::vector<std::array<double, 3>> create_distance_triplet_set(int index) const;

    /**
     * Utility function to calculate the euclidean distance between 2 points
     * @param a, b
     * @return The distance between a and b
     */
    double distance(const Point &a, const Point &b) const;
public:
    Position_Calculator(const Dataset &d, const Plane &p):
        dataset(d), plane(p) 
    {  }

    /**
     * Calculates the path taken by the robot, see README.MD for details
     * @return The list of position data (path)
     */
    std::vector<Position_Data> calculate_path() const;
};

#endif