#ifndef BESTFS_H
#define BESTFS_H
#include <memory>
#include "Table.h"

std::shared_ptr<Table> BESTFS(std::shared_ptr<Table> initial, std::shared_ptr<Table> end);

#endif