#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

struct Symbol_Node
{
    char *name;
    char **str_info; //maybe make dynamic array

    unsigned str_info_size;

    struct Symbol_Node *next_table_chain;
};

struct Symbol_Table
{
    unsigned size;

    struct Symbol_Node **table;
};

struct Symbol_Table *create_table  (unsigned size);
struct Symbol_Node  *get_symbol    (struct Symbol_Table *table, char *symbol);
void add_symbol                    (struct Symbol_Table *table, char *symbol, char **info, unsigned size);

void print_table (struct Symbol_Table *table);

#endif