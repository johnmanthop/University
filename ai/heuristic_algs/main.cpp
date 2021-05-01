#include <iostream>
#include <chrono>
#include <memory>
#include <functional>

#include "DFS.h"
#include "BFS.h"
#include "BESTFS.h"
#include "AS.h"
#include "Table.h"

void print(std::shared_ptr<Table> a)
{
	for (unsigned i = 0; i < a->get_rows(); ++i) {
		for (unsigned j = 0; j < a->get_cols(); ++j) {
			std::cout << (*a)[i][j] << ' ';
		}
		std::cout << '\n';
	}
    std::cout << '\n';
}

void print_chain(std::shared_ptr<Table> a)
{
    do {
        print(a);
        a = a->get_parent();
    } while (a);
}

unsigned chain_len(std::shared_ptr<Table> a)
{
    unsigned c = 0;
    for (; a->get_parent(); a = a->get_parent()) c++;
    
    return c;
}

void benchmark(std::shared_ptr<Table> start, 
               std::shared_ptr<Table> end, 
               std::function<std::shared_ptr<Table>(std::shared_ptr<Table> s, std::shared_ptr<Table> e)> alg,
               std::string alg_name,
               bool bprint_chain)
{
    auto begint = std::chrono::steady_clock::now();
    auto solution = alg(start, end);
    auto endt = std::chrono::steady_clock::now();
    std::cout << "---------------------" << alg_name << "---------------------\n";
    if (solution) {
        std::cout << "Solution found\n"; 
        if (bprint_chain) print_chain(solution);
        std::cout << "Length: " << chain_len(solution) << '\n';
    } else {
        std::cout << "No solution found\n";
    }
    
    std::cout << alg_name
              << " time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(endt - begint).count() 
              << " milliseconds\n\n"; 
}

int main()
{
    auto end   = std::make_shared<Table>(3, 3);
    auto table = std::make_shared<Table>(3, 3);
    
    (*end)[0][0] = 1;
    (*end)[0][1] = 2;
    (*end)[0][2] = 3;
        
    (*end)[1][0] = 4;
    (*end)[1][1] = 5;
    (*end)[1][2] = 6;
        
    (*end)[2][0] = 7;
    (*end)[2][1] = 8;
    (*end)[2][2] = 0;
    
    (*table)[0][0] = 3;
    (*table)[0][1] = 6;
    (*table)[0][2] = 0;
      
    (*table)[1][0] = 1;
    (*table)[1][1] = 4;
    (*table)[1][2] = 2;
      
    (*table)[2][0] = 7;
    (*table)[2][1] = 5;
    (*table)[2][2] = 8;
    table->set_initial_free(0, 2);
    
    benchmark(table, end, BFS, "BFS", false);
    benchmark(table, end, DFS, "DFS", false);
    benchmark(table, end, BESTFS, "BESTFS", false);
    benchmark(table, end, AS, "A*", false);

    return 0;
}