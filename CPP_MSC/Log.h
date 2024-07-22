#ifndef LOG_H
#define LOG_H

#include <vector>
#include <iostream>
#include <string>

/**
 * Static Log class to write debug messages from every part of the codebase
 */
class Log 
{
private:
    static std::vector<std::string> logs;
public:
    static bool enabled;

    /**
     * Write a debug string
     * @param str
     */
    static void append(const std::string &str); 

    /**
     * Dump the debug data on any writable stream
     * @param T The type of the output stream, for example ostream (cout) or ofstream (output file)
     * @param stream
     */
    template<typename T>
    static void dump(T &stream)
    {
        for (auto &str: logs)
        {
            stream << str;
        }
    }
};

#endif