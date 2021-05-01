#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <memory>
#include <vector>

class Table : public std::enable_shared_from_this<Table>
{
private:
    struct Pair
    {
        unsigned row, col;
    };
    
private:
    Pair free_position;
    
    unsigned size_r, size_c;
    unsigned heuristic_value;
    unsigned steps_from_root;
    
    std::vector<std::vector<int>> table;
    std::shared_ptr<Table> parent;
    
private:
    void set_parent(std::shared_ptr<Table> p);
    unsigned heuristic() const;
    
public:
    Table();
    Table(unsigned size_r, unsigned size_c);
    virtual ~Table() noexcept;

    std::vector<int>  operator[](unsigned index) const;
    std::vector<int> &operator[](unsigned index);
    
    Pair get_free                    () const { return free_position; }
    unsigned get_rows                () const { return size_r; }
    unsigned get_cols                () const { return size_c; }
    std::shared_ptr<Table> get_parent() const { return parent; };
    
    std::vector<std::shared_ptr<Table>> expand();
    
    void set_initial_free(unsigned r, unsigned c) { free_position = { r, c }; }
    
    std::shared_ptr<Table> slide(char c);
    

    unsigned get_steps_from_root() const { return steps_from_root; }
    
    unsigned compute_h_val();
    std::string hash      () const;
    unsigned get_h_val    () const;
    void     set_h_val    (unsigned v)   { heuristic_value = v; }
    
    void randomize();
};

bool operator==(const Table &a, const Table &b);


#endif