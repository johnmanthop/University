#ifndef DFS_H
#define DFS_H
#include <memory>
#include "Table.h"

std::shared_ptr<Table> DFS(std::shared_ptr<Table> initial, std::shared_ptr<Table> end);

#endif