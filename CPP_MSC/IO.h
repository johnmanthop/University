#ifndef IO_H
#define IO_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <sstream>

#include "Log.h"
#include "Position_Calculator.h"
#include "Dataset.h"
#include "Plane.h"

/**
 * Utility tool that parses cmd arguments and the csv files
 */
class IO_Utility
{
private:
    std::string beacons_file;
    std::string distances_file;
    std::string path_file;
    std::string debug_file;
private:
    void print_help() const;
    
    /**
     * Tokenize a given string and return a list of tokens
     * @param str
     * @param delimiter The character according to which to parse the string
     * @return A vector of string tokens
     */
    std::vector<std::string> tokenize_string(const std::string &str, char delimiter) const;
public:

    /**
     * Parse the command line arguments
     */
    int parse_cmd(int argc, char **argv);

    /**
     * Dump the path result onto the path output file
     * @param path The list of position data making up the resulting path
     */
    void dump_path(const std::vector<Position_Data> &path);

    /**
     * Dump the debug data onto the [optional] debug output file
     * @param debug_stream The string stream thath contains the debug logs
     */
    void dump_debug(const std::stringstream &debug_stream);

    /**
     * Parse the distance csv file
     * @return A list of distance data objects
     */

    std::vector<Distance_Data>  parse_distances_csv() const;
    /**
     * Parse the beacons csv file
     * @return A list of size 6 that contains the positions of the 6 beacons
     */
    std::array<Point, 6>        parse_beacons_csv() const;
};

#endif