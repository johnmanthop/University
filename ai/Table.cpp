#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "Table.h"

#include <iostream>
Table::Table():
    size_r(0), 
    size_c(0), 
    steps_from_root(0),
    parent(nullptr)
{  }

Table::Table(unsigned s_r, unsigned s_c):
    size_r(s_r), 
    size_c(s_c), 
    steps_from_root(0),
    parent(nullptr)
{
    //Initialize the table
    for (unsigned i = 0; i < size_r; ++i) {
        table.push_back(std::vector<int> ());
        for (unsigned j = 0; j < size_c; ++j) {
            table[i].push_back(0);
        }
    }
}

Table::~Table() noexcept 
{//Use custom destructor to avoid stack overflow due to recursive deletio
    while (parent && parent.use_count() < 2) {
        parent = std::move(parent->parent);
    }
}

std::vector<int> Table::operator[](unsigned index) const
{
    return table[index];
}

std::vector<int> &Table::operator[](unsigned index)
{
    return table[index];
}

void Table::set_parent(std::shared_ptr<Table> p)
{
    parent = p;
}

unsigned Table::heuristic() const 
{
    unsigned value = 0; //0 means no sorting inconsistency, in other words, the problem is solved
    //for every one sorting inconsistency add one point to the value
    std::vector<int> linear(size_r * size_c - 1);
    int c = 0;
    for (auto & row : table) {
        for (auto & el : row) {
            linear[c++] = el;
        }
    }
    
    for (unsigned i = 0; i < linear.size() - 1; ++i) {
        if (linear[i] > linear[i+1]) ++value;
    }
    
    return value;
}

unsigned Table::get_h_val() const
{
    return heuristic_value;
}

unsigned Table::compute_h_val()
{
    heuristic_value = heuristic();
    return heuristic_value;
}

std::shared_ptr<Table> Table::slide(char dir)
{
    int direction_r = 0;
    int direction_c = 0;
    
    if (dir == 'u') {
        if (free_position.row == 0) {
            return std::shared_ptr<Table>(nullptr);
        }
        direction_r = -1;
    } else if (dir == 'd') {
        if (free_position.row == size_r-1) {
            return std::shared_ptr<Table>(nullptr);
        }
        direction_r = 1;
    } else if (dir == 'l') {
        if (free_position.col == 0) {
            return std::shared_ptr<Table>(nullptr);
        }  
        direction_c = -1;
    } else if (dir == 'r') {
        if (free_position.col == size_c-1) {
            return std::shared_ptr<Table>(nullptr);
        }  
        direction_c = 1;
    }
    
    ++steps_from_root;
    
    auto temp = std::make_shared<Table>(*this);

    std::swap((*temp)[free_position.row][free_position.col], (*temp)[free_position.row + direction_r][free_position.col + direction_c]);
    temp->free_position.row += direction_r;
    temp->free_position.col += direction_c;
    temp->set_parent(shared_from_this()); 
    
    return temp; 
}

std::vector<std::shared_ptr<Table>> Table::expand() 
{
    std::vector<std::shared_ptr<Table>> temp;
    temp.reserve(4);
    
    auto c1 = slide('u');
    auto c2 = slide('d');
    auto c3 = slide('l');
    auto c4 = slide('r');
    
    if (c1) temp.push_back(c1);
    if (c2) temp.push_back(c2);
    if (c3) temp.push_back(c3);
    if (c4) temp.push_back(c4);
    
    return temp;
}

std::string Table::hash() const
{
    std::string h;
    
    for (auto & row : table) {
        for (auto & el : row) {
            h += std::to_string(el) + "|";
        }
    }
    
    return h;
}

void Table::randomize()
{
    std::vector<int> list(size_r*size_c);
    for (unsigned i = 0; i < size_r*size_c; ++i) list[i] = i;
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::shuffle(list.begin(), list.end(), rng);
    
    for (unsigned i = 0; i < size_r; ++i) {
        for (unsigned j = 0; j < size_c; ++j) {
            table[i][j] = list[i * size_r + j];
            if (list[i * size_r + j] == 0) free_position = { i, j };
        }
    }
}

bool operator==(const Table &a, const Table &b)
{
    bool eq = true;
    
    for (unsigned i = 0; i < a.get_rows(); ++i) {
        for (unsigned j = 0; j < a.get_cols(); ++j) {
            if (a[i][j] != b[i][j]) eq = false;
        }
    }
    
    return eq;
}
