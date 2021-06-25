#ifndef AST_H
#define AST_H

struct AST_Node
{
    struct AST_Node **children;
    unsigned c_count;
    char *type;
    char *strvalue;
    int   intvalue;
    float floatvalue;
};

struct AST_Node *make_node   (char *type, struct AST_Node   **children, unsigned children_count);
struct AST_Node *make_str    (char *type, char *strvalue, struct AST_Node **children, unsigned children_count);

void print_tree (struct AST_Node* x, char *flag, int depth, char isLast);



#endif