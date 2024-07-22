#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <vector>
#include <string>
#include <array>

/**
 * Point in 2d space
 */
struct Point
{
    double x, y;

    Point(double x_, double y_):
        x(x_), y(y_)
    {  }
    Point() {}
};

std::ostream &operator<<(std::ostream &os, const Point &p);

/**
 * Internal representation of a 2d plane
 */
class Plane
{
private:
    std::array<Point, 6> beacons;

public:
    Plane(const std::array<Point, 6> &b);

    int get_no_of_beacons() const { return beacons.size(); }
    Point get_beacon(int index) const;

    /**
     * Get a list of beacons based on lower_lim to upper_lim range
     * @param lower_lim
     * @param upper_lim
     * @return A list of beacon points from lower_lim to upper_lim
     */
    std::vector<Point> get_beacons(int lower_lim, int upper_lim) const;
};

#endif 