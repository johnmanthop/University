#ifndef BFS_H
#define BFS_H
#include <memory>
#include "Table.h"

std::shared_ptr<Table> BFS(std::shared_ptr<Table> initial, std::shared_ptr<Table> end);

#endif