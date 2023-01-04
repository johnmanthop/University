#include <iostream>
#include <string>

#include "error.h"

void error(std::string msg)
{ 
    std::cout << "Error: " << msg << '\n'; 
    for(;;) {} 
}