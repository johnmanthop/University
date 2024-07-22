#include <numeric>
#include <cassert>
#include <iostream>
#include <sstream>
#include <cmath>

#include "Log.h"
#include "Position_Calculator.h"

// I don't trust the standard lib for this
double abs(double x)
{
    return (x >= 0)?x:(-1.0*x);
}

// see README.MD for details
Point Position_Calculator::trilateration(const std::array<Point, 3> &points, const std::array<double, 3> &distances) const
{
    // 3 point trilateration is a solved linear system
    Point p;

    double r0 = distances[0];
    double r1 = distances[1];
    double r2 = distances[2];

    double a = (2*points[1].x - 2*points[0].x);
    double b = (2*points[1].y - 2*points[0].y);
    double c = (r0*r0 - r1*r1 - points[0].x*points[0].x + points[1].x*points[1].x - points[0].y*points[0].y + points[1].y*points[1].y);

    double d = (2*points[2].x - 2*points[1].x);
    double e = (2*points[2].y - 2*points[1].y);
    double f = (r1*r1 - r2*r2 - points[1].x*points[1].x + points[2].x*points[2].x - points[1].y*points[1].y + points[2].y*points[2].y);

    p.x = (c*e - f*b) / (a*e - b*d);
    p.y = (c*d - a*f) / (b*d - a*e);

    // this is a proof of concept, but in actual practice this if statement would considerably slow down the performance
    if (Log::enabled)
    {
        std::stringstream strm;
        strm << "Trilateration points:    ";
        strm << points[0] << ", " << points[1] << ", " << points[2] << "\n";
        strm << "Trilateration distances: ";
        strm << distances[0] << ", " << distances[1] << ", " << distances[2] << "\n";
        strm << "Calculated position:     ";
        strm << p << "\n\n";

        Log::append(strm.str());
    }

    return p;
}

std::vector<std::array<Point, 3>> Position_Calculator::create_beacon_triplet_set() const 
{
    std::vector<std::array<Point, 3>> set;
    
    for (int i = 0; i < plane.get_no_of_beacons() - 2; ++i)
    {
        set.push_back({});

        set[i][0] = plane.get_beacon(i);
        set[i][1] = plane.get_beacon(i + 1);
        set[i][2] = plane.get_beacon(i + 2);
    }

    // last triplet wraps around to 0
    set.push_back({});
    set[4][0] = plane.get_beacon(4);
    set[4][1] = plane.get_beacon(5);
    set[4][2] = plane.get_beacon(0);

    return set;
}

std::vector<std::array<double, 3>> Position_Calculator::create_distance_triplet_set(int index) const 
{
    std::vector<std::array<double, 3>> set;

    for (int i = 0; i < plane.get_no_of_beacons() - 2; ++i)
    {
        set.push_back({});

        set[i][0] = dataset.get_distance_from_beacon(index, i);
        set[i][1] = dataset.get_distance_from_beacon(index, i + 1);
        set[i][2] = dataset.get_distance_from_beacon(index, i + 2);
    }
    
    // last triplet wraps around to 0
    set.push_back({});
    set[4][0] = dataset.get_distance_from_beacon(index, 4);
    set[4][1] = dataset.get_distance_from_beacon(index, 5);
    set[4][2] = dataset.get_distance_from_beacon(index, 0);

    return set;
}

double Position_Calculator::distance(const Point &a, const Point &b) const 
{
    return std::sqrt( (b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y) );
}

Point Position_Calculator::find_center_point(const std::vector<Point> &points) const
{
    double avg_x = 0, avg_y = 0;

    for (auto p: points)
    {
        avg_x += p.x;
        avg_y += p.y;
    }
    
    avg_x /= ((double)points.size());
    avg_y /= ((double)points.size());

    return { avg_x, avg_y };
}

std::vector<Position_Data> Position_Calculator::calculate_path() const
{
    std::vector<Position_Data> path;
    path.reserve(dataset.get_dataset_size());

    const double epsilon = 0.1;

    // a vector of possible beacon triplets
    // first triplet is 0, 1, 2
    // second is 1, 2, 3
    // third is 2, 3, 4
    // fourth is 3, 4, 5
    // fifth i 4, 5, 0
    auto beacon_triplets = create_beacon_triplet_set();

    for (int i = 0; i < dataset.get_dataset_size(); ++i)
    {
        auto distance_triplets = create_distance_triplet_set(i);
        assert(beacon_triplets.size() == distance_triplets.size());

        std::vector<Point> points_computed;
        for (int j = 0; j < beacon_triplets.size(); ++j)
        {
            Point p = trilateration(beacon_triplets[j], distance_triplets[j]);

            points_computed.push_back(p);
        }

        Point center_point = find_center_point(points_computed);

        path.push_back({ dataset.get_timestamp(i), center_point });
    }

    return path;
}