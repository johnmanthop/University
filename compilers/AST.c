#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AST.h"

//there can be 2 kinds of node, the simple node that has only one string data (it's node type)
//and the string node which can also have a string value associated

struct AST_Node *make_node (char *type, struct AST_Node **children, unsigned children_count)
{
    struct AST_Node *node = malloc(sizeof(struct AST_Node));

    node->type     = type;
    node->strvalue = "";
    node->c_count  = children_count;
    node->children = (children_count > 0)?(malloc (sizeof(struct AST_Node*) * children_count)):NULL;

    memcpy(node->children, children, sizeof(struct AST_Node*) * children_count);

    return node;
}

struct AST_Node *make_str (char *type, char *strvalue, struct AST_Node **children, unsigned children_count)
{
    struct AST_Node *node = malloc(sizeof(struct AST_Node));

    node->type     = type;
    node->strvalue = strvalue;
    node->c_count  = children_count;
    node->children = (children_count > 0)?(malloc (sizeof(struct AST_Node*) * children_count)):NULL;

    memcpy(node->children, children, sizeof(struct AST_Node*) * children_count);

    return node;
}

void print_tree (struct AST_Node* x, char *flag, int depth, char isLast)
{ //from geeks_for_geeks, helper function to print the syntax tree
    if (x == NULL) return;
     
    for (int i = 1; i < depth; ++i) {
        if (flag[i] == 1) {
            printf("|    ");
        } else {
            printf("    ");
        }
    }
     
    if (depth == 0) { 
        printf("%s\n", x->type); 
    } else if (isLast) {
        printf("+--- %s\n", x->type);

        flag[depth] = 0;
    } else {
        printf("+--- %s\n", x->type);
    }
 
    int it = 0;
    for (int i = 0; i != x->c_count; ++i, ++it) {
        print_tree(x->children[i], flag, depth + 1, (it == x->c_count - 1));
    }
    flag[depth] = 1;
}