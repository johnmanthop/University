/*
 * CPP lab project 2023-2024
 * Ioannis Manthopoulos
 */

#include <iostream>
#include <cassert>
#include <sstream>

#include "Log.h"
#include "Position_Calculator.h"
#include "Dataset.h"
#include "Plane.h"
#include "IO.h"

int main(int argc, char **argv)
{
    IO_Utility io;
    
    if (io.parse_cmd(argc, argv) != 0)
    {
        return -1;
    }
    
    auto matrix = io.parse_distances_csv();     // construct a matrix with the distance data
    auto beacons = io.parse_beacons_csv();      // construct a list with the beacon's distances

    Plane plane(beacons);                       // plane represents the 2d plane that the beacons occupy
    Dataset dataset(matrix);                    // dataset represents the distances data
    
    dataset.filter_matrix();                    // filter the distances of zero and negative values
    dataset.correctness_check();                // sanity check after the filtering
    dataset.sort();                             // make sure data is sorted according to timestamp
    
    Position_Calculator calculator(dataset, plane);
    auto path = calculator.calculate_path();

    io.dump_path(path);                         // dump the path data to the path output file

    // if debug logs are enabled dump them onto the debug output file
    if (Log::enabled)
    {
        std::stringstream debug_stream;

        Log::dump(debug_stream);                // write the logs onto the debug string stream
        io.dump_debug(debug_stream);            // dump the debug string stream to the output file
    }

    return 0;
}