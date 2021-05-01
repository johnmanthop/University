#include <queue>
#include <memory>
#include <set>
#include "Table.h"

std::shared_ptr<Table> BFS(std::shared_ptr<Table> initial, std::shared_ptr<Table> end)
{
    std::queue<std::shared_ptr<Table>> frontier;
    std::set  <std::string> expanded;
    
    frontier.push(initial);
    
    while (!frontier.empty()) {

        auto node = frontier.front();
        frontier.pop();
        
        if (expanded.count(node->hash()) == 0) {
            
            if (*node == *end) {
                return node;
            }
            
            expanded.insert(node->hash());
            
            for (auto c : node->expand()) {
                if (expanded.count(c->hash()) == 0) {
                    frontier.push(c);
                }
            }
        }
    }
    
    return { nullptr };
}