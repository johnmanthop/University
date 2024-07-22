#include "Log.h"
#include "Plane.h"

Plane::Plane(const std::array<Point, 6> &b):
    beacons(b)
{
    if (Log::enabled)
    {
        std::string log;
    
        for (int i = 0; i < beacons.size(); ++i)
        {
            log += "beacon[" + std::to_string(i) + "] = (" + std::to_string(beacons[i].x) + ", " + std::to_string(beacons[i].y) + ")\n";
        }

        log += "\n";
        
        Log::append(log);
    }
}

Point Plane::get_beacon(int index) const 
{
    return beacons[index];
}

std::vector<Point> Plane::get_beacons(int lower_lim, int upper_lim) const 
{
    std::vector<Point> result;

    std::copy(beacons.begin() + lower_lim, beacons.begin() + upper_lim, result.begin());

    return result;
}

std::ostream &operator<<(std::ostream &os, const Point &p)
{
    // output operator overload
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}