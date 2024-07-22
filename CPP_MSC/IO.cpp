#include "IO.h"

void IO_Utility::print_help() const
{
    std::cout << "CPP lab project for Radio-Electronics MSC\n"
              << "Usage:\n"
              << "./m -b <beacon csv input> -d <distances csv input> -p <path csv output> -db <optional debug output> \n"
              << "    -db automatically enables debug messages, disabled otherwise\n";
}

int IO_Utility::parse_cmd(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout << "Use -h or --help for help message\n";
        return -1;
    }
    else if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")
    {
        print_help();
        return -2;
    }
    else if (argc < 4)
    {
        std::cout << "Not enough arguments\n";
        return -3;
    } 

    // parse the cmd arguments onto their corresponding variables
    for (int i = 1; i < argc; ++i)
    {
        if (std::string(argv[i]) == "-b")   beacons_file    = std::string(argv[i+1]);
        if (std::string(argv[i]) == "-d")   distances_file  = std::string(argv[i+1]);
        if (std::string(argv[i]) == "-p")   path_file       = std::string(argv[i+1]);
        if (std::string(argv[i]) == "-db")  
        {
            Log::enabled = true;
            debug_file   = std::string(argv[i+1]);
        }
    }

    if (beacons_file.empty() || distances_file.empty() || path_file.empty())
    {
        return -4;
    }

    return 0;
}

std::vector<std::string> IO_Utility::tokenize_string(const std::string &str, char delimiter) const
{ 
    std::vector<std::string> token_list;
    token_list.push_back("");
    
    int token_counter = 0;
    for (char character: str)
    {
        // if current character is the delimiter
        if (character == delimiter)
        {
            // add a new token to the list
            token_list.push_back("");
            token_counter++;
        }
        else 
        {
            // else add the character to the current token being written
            token_list[token_counter] += character;
        }
    }

    return token_list;
}

std::vector<Distance_Data> IO_Utility::parse_distances_csv() const
{
    std::vector<Distance_Data> matrix;

    std::ifstream csv(distances_file);
    if (!csv.is_open())
    {
        std::cout << "Could not open CSV file\n";
        return {{}};
    }

    std::string line;
    while (std::getline(csv, line))
    {
        // skip empty lines
        if (line.size() < 10) continue;

        auto token_list = tokenize_string(line, ',');

        // add matrix element
        // timestamp is an integer
        // distances is an array of 6 doubles
        matrix.push_back(
            {
                std::stoi(token_list[0]), // timestamp
                {{
                    std::stod(token_list[1]), // 6 distances
                    std::stod(token_list[2]),
                    std::stod(token_list[3]),
                    std::stod(token_list[4]),
                    std::stod(token_list[5]),
                    std::stod(token_list[6])
                }}
            });
    }

    csv.close();

    return matrix;
}

std::array<Point, 6> IO_Utility::parse_beacons_csv() const
{
    std::array<Point, 6> array;

    std::ifstream csv(beacons_file);
    if (!csv.is_open())
    {
        std::cout << "Could not open CSV file\n";
        return {{}};
    }

    std::string line;
    int index = 0;
    while (std::getline(csv, line))
    {
        // skip empty lines
        if (line.size() < 5) continue;

        auto token_list = tokenize_string(line, ',');

        array[index].x = std::stod(token_list[0]); // beacon x
        array[index].y = std::stod(token_list[1]); // beacon y

        index++;
    }

    csv.close();

    return array;
}

void IO_Utility::dump_path(const std::vector<Position_Data> &path)
{
    std::ofstream path_ofstream(path_file);

    for (auto p: path)
    {
        // write each path data element to the output stream
        path_ofstream << p.timestamp << "," << p.position.x << "," << p.position.y << "\n";
    }

    path_ofstream.close();
}

void IO_Utility::dump_debug(const std::stringstream &debug_internal_stream)
{
    assert(!debug_file.empty());

    std::ofstream debug_ofstream(debug_file);

    // write all debug logs to the debug output stream
    debug_ofstream << debug_internal_stream.str();

    debug_ofstream.close();
}