#ifndef AS_H
#define AS_H
#include <memory>
#include "Table.h"

std::shared_ptr<Table> AS(std::shared_ptr<Table> initial, std::shared_ptr<Table> end);

#endif