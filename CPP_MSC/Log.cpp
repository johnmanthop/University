#include "Log.h"

// static members need to be declared like this
std::vector<std::string> Log::logs;
bool Log::enabled = false;

void Log::append(const std::string &str)
{
    logs.push_back(str);
}