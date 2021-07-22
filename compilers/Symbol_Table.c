#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "Symbol_Table.h"

static unsigned powui(unsigned base, unsigned exp)
{ //pow integer function, used to hash a string
    unsigned val = 1;

    for (int i = 0; i < exp; ++i) {
        val *= base;
    }

    return val;
}

static unsigned hash_str(char *name, unsigned size)
{ //hash string function
    const char prime = 31;
    unsigned hvalue = 0;
    unsigned strsize = strlen(name);

    for (unsigned i = 0; i < strsize; ++i) {
        hvalue += name[i] * powui(prime, i);
    }
    hvalue %= size;

    return hvalue;
}

struct Symbol_Table *create_table(unsigned size)
{
    struct Symbol_Table *table = malloc(sizeof(struct Symbol_Table));

    table->size = size;
    table->table = malloc(size * sizeof(struct Symbol_Node));
    for (unsigned i = 0; i < size; ++i) {
        table->table[i] = NULL;
    }

    return table;
}

void add_symbol(struct Symbol_Table *table, char *symbol, char **info, unsigned size)
{
    //find the string's position
    unsigned postable = hash_str(symbol, table->size);
    struct Symbol_Node **node = &table->table[postable];
    
    for (;*node; node = &((*node)->next_table_chain)); //traverse to the first empty chain node
    
    //add the element to the chain
    *node = malloc (sizeof(struct Symbol_Node));
    (*node)->name = symbol;
    (*node)->str_info_size = size;
    (*node)->str_info = malloc (sizeof(char*) * size);
    (*node)->next_table_chain = NULL;

    memcpy((*node)->str_info, info, sizeof(char*) * size); //the data is copied so it remains valid even if a static array is passed
}

struct Symbol_Node *get_symbol (struct Symbol_Table *table, char *symbol)
{
    //get string's position
    unsigned postable = hash_str(symbol, table->size);
    struct Symbol_Node **node = &table->table[postable];
    //traverse until the name is found or the chain hits the end
    for (; *node && strcmp(symbol, (*node)->name); node = &((*node)->next_table_chain));

    return *node;
}

void print_table(struct Symbol_Table *table)
{ //helper function to print the table
    for (int i = 0; i < table->size; ++i) {
        for (struct Symbol_Node *node = table->table[i]; node; node = node->next_table_chain) {
            printf("%s ", node->name);

            if (!strcmp(node->str_info[0], "function")) {

                printf("%s %s, %s arguments: ", node->str_info[0], node->str_info[1], node->str_info[2]);
                for (int i = 3; i < node->str_info_size; ++i) {
                    printf("%s ", node->str_info[i]);
                }

            } else if (!strcmp(node->str_info[0], "subroutine") && node->str_info_size > 1) {
                
                printf("%s, %s arguments: ", node->str_info[0], node->str_info[1]);
                for (int i = 2; i < node->str_info_size; ++i) {
                    printf("%s ", node->str_info[i]);
                }

            } else {

                for (int i = 0; i < node->str_info_size; ++i) {
                    printf("%s ", node->str_info[i]);
                }

            } 
            printf("\n");
        }
    }
}
