#include <memory>
#include <queue>
#include <set>
#include "Table.h"

std::shared_ptr<Table> BESTFS(std::shared_ptr<Table> initial, std::shared_ptr<Table> end)
{
    auto comparator = [](std::shared_ptr<Table> a, std::shared_ptr<Table> b) {
        return a->get_h_val() > b->get_h_val();
    };
    std::priority_queue <std::shared_ptr<Table>, std::deque<std::shared_ptr<Table>>, decltype(comparator)> frontier(comparator);
    std::set<std::string> expanded;
    
    frontier.push(initial);
    
    while (!frontier.empty()) {

        auto node = frontier.top();
        frontier.pop();
        
        if (expanded.count(node->hash()) == 0) {
            
            if (*node == *end) {
                return node;
            }
            
            expanded.insert(node->hash());
            
            for (auto c : node->expand()) {
                if (expanded.count(c->hash()) == 0) {
                    c->compute_h_val();
                    frontier.push(c);
                }
            }
        }
    }
    
    return { nullptr };
}