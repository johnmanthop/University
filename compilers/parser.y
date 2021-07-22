%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h> 

    #include "AST.h"
    #include "Symbol_Table.h"

    int yydebug = 1;
    struct Symbol_Table *table;
%}

%union {
    struct AST_Node *node;
    int numvalue;
    char *strvalue;
}

%start program

%type<node> program body declarations type vars undef_variable
%type<node> listspec dims dim cblock_list cblock id_list vals value_list values value repeat sign
%type<node> constant simple_constant complex_constant statements labeled_statement label statement
%type<node> simple_statement assignment variable expressions expression listexpression goto_statement labels
%type<node> if_statement io_statement subroutine_call read_list read_item iter_space step write_list write_item 
%type<node> compound_statement branch_statement loop_statement tail subprograms subprogram formal_parameters header

%token T_function
%token T_subroutine
%token T_end
%token T_common
%token T_integer
%token T_real
%token T_complex
%token T_logical
%token T_character
%token T_string
%token T_list
%token T_data
%token T_continue
%token T_goto
%token T_call
%token T_read
%token T_write
%token T_length
%token T_new
%token T_if 
%token T_then 
%token T_else
%token T_endif
%token T_do
%token T_enddo
%token T_stop
%token T_return
%token T_comma
%token T_listfunc
%token T_id
%token T_lbrack 
%token T_rbrack
%token T_lparen
%token T_rparen
%token T_divop
%token T_addop
%token T_mulop
%token T_powop
%token T_orop
%token T_andop
%token T_notop
%token T_relop
%token T_colon
%token T_assign
%token T_intlit
%token T_reallit
%token T_complexlit
%token T_logicallit
%token T_characterlit
%token T_stringlit

%left T_orop
%left T_andop 
%left T_notop

%left T_relop
%left T_addop
%left T_mulop T_divop
%right T_powop

%%
//Most rules are trivially explained, comments are provided when needed
program         :body T_end subprograms
                {
                    //Each rule has their productions as children
                    struct AST_Node *ar[2] = { $1, $3 };
                    $$ = make_node ("program", ar, 2);

                    //when parsing is done print the tree
                    const long long s = 10000000; //tree can have up to this many nodes
                    char *flag = malloc(s);
                    for (long long i = 0; i < s; ++i) flag[i] = 1;
                    print_tree($$, flag, 0, 0);
                };

body            :declarations statements
                {
                    struct AST_Node *ar[2] = { $1, $2 };
                    $$ = make_node ("body", ar, 2);
                };

declarations    :declarations type vars
                {
                    struct AST_Node *ar[3] = { $1, $2, $3 };
                    $$ = make_node ("decl_typevars", ar, 3);
                    
                    //traverse the tree and get data about variables to put into the symbol table
                    struct AST_Node *node = $3; //starting node
                    for (;;) {
                        struct AST_Node *undef_var;

                        if (node->c_count == 2) { //find the undef_var
                            //node's second child is the variable
                            undef_var = node->children[1];
                        } else if (node->c_count == 1) {
                            undef_var = node->children[0];
                        }

                        char *name = undef_var->strvalue; //get undef_var's data
                        char *ar[2] = { "variable", $2->type };
                        add_symbol (table, name, ar, 2); //add data to symbol table

                        if (node->c_count == 1) break; //if there are no more undef_vars then break
                        else node = node->children[0]; //else set new starting node and keep going
                    }
                } |
                declarations T_common cblock_list
                {
                    struct AST_Node *ar[2] = { $1, $3 };
                    $$ = make_node ("decl_common", ar, 2);
                    //same as before
                    struct AST_Node *node = $3;
                    for (;;) {
                        struct AST_Node *cblock;

                        if (node->c_count == 2) {
                            cblock = node->children[1];
                        } else if (node->c_count == 1) {
                            cblock = node->children[0];
                        }

                        char *name = cblock->strvalue;
                        char *ar[2] = { "common_block", cblock->strvalue };
                        add_symbol (table, name, ar, 2);

                        if (node->c_count == 1) break;
                        else node = node->children[0];
                    }
                } |
                declarations T_data vals
                {
                    struct AST_Node *ar[2] = { $1, $3 };
                    $$ = make_node ("decl_data", ar, 2);
                } |
                {
                    $$ = make_node ("null", NULL, 0);
                };

type		    : T_intlit 
                {
                    $$ = make_node ("int_type", NULL, 0);
                } |
                T_reallit
                {
                    $$ = make_node ("real_type", NULL, 0);
                } | 
                T_complexlit
                {
                    $$ = make_node ("complex_type", NULL, 0);
                } | 
                T_logicallit
                {
                    $$ = make_node ("logical_type", NULL, 0);
                } | 
                T_characterlit
                {
                    $$ = make_node ("char_type", NULL, 0);
                } | 
                T_stringlit
                {
                    $$ = make_node ("string_type", NULL, 0);
                };

vars            :vars T_comma undef_variable
                {
                    struct AST_Node *ar[2] = { $1, $3 };
                    $$ = make_node ("vars", ar, 2);
                } |
                undef_variable
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("vars", ar, 1);
                };

undef_variable  : listspec T_id T_lparen dims T_rparen
                {
                    struct AST_Node *ar[2] = { $1, $4 };
                    $$ = make_str ("array_var", $<strvalue>2, ar, 2);
                } |
                listspec T_id
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_str ("scalar_var", $<strvalue>2, ar, 1);
                };

listspec        : T_list
                {
                    $$ = make_str ("list_spec", "list", NULL, 0);
                } |
                {
                    $$ = make_str ("list_spec", "nolist", NULL, 0);
                };

dims            :dims T_comma dim 
                {
                    struct AST_Node *ar[2] = { $1, $3 };
                    $$ = make_node ("dims", ar, 2);
                } | 
                dim
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("dim", ar, 1);
                };

dim             :T_integer 
                {
                    $$ = make_str ("dim_int", $<strvalue>1, NULL, 0);
                } | 
                T_id
                {
                    $$ = make_str ("dim_var", $<strvalue>1, NULL, 0);
                };

cblock_list     : cblock_list cblock
                {
                    struct AST_Node *ar[2] = { $1, $2 };
                    $$ = make_node ("common", ar, 2);
                } | 
                cblock
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("common", ar, 1);
                };

cblock          : T_divop T_id T_divop id_list
                {
                    struct AST_Node *ar[2] = { $4 };
                    $$ = make_str ("common_block", $<strvalue>2, ar, 2);
                };

id_list         : id_list T_comma T_id
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_str ("common_var", $<strvalue>3, ar, 1);
                } | 
                T_id
                {
                    $$ = make_str ("common_var", $<strvalue>1, NULL, 0);
                };

vals            :vals T_comma T_id value_list
                {
                    struct AST_Node *ar[2] = { $1, $4 };
                    $$ = make_str ("value_decl", $<strvalue>3, ar, 2);
                } |
                T_id value_list
                {
                    struct AST_Node *ar[1] = { $2 };
                    $$ = make_str ("value_decl", $<strvalue>1, ar, 1);
                };

value_list      : T_divop values T_divop
                {
                    struct AST_Node *ar[1] = { $2 };
                    $$ = make_node ("value_list", ar, 1);
                };

values          : values T_comma value
                {
                    struct AST_Node *ar[2] = { $1, $3 };
                    $$ = make_node ("value", ar, 2);
                } |
                value
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("value", ar, 1);
                };

value           : repeat sign constant
                {
                    struct AST_Node *ar[3] = { $1, $2, $3 };
                    $$ = make_node ("repeated_value", ar, 3);
                } |
                T_addop constant
                {
                    struct AST_Node *ar[1] = { $2 };
                    $$ = make_node ("signed_value", ar, 1);
                } |
                constant
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("unsigned_value", ar, 1);
                };

repeat          : T_integer T_mulop
                {
                    $$ = make_str ("repeater1", $<strvalue>1, NULL, 0);
                } | 
                T_mulop
                {
                    $$ = make_node ("repeater2", NULL, 0);
                };

sign            : T_addop 
                {
                    $$ = make_str ("sign", $<strvalue>1, NULL, 0);
                } |
                {
                    $$ = make_node ("null", NULL, 0);
                };

constant        : simple_constant
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("simple_constant", ar, 1);
                } | 
                complex_constant
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("complex_constant", ar, 1);
                };

simple_constant : T_integer
                {
                    $$ = make_str ("int_const", $<strvalue>1, NULL, 0);
                } | 
                T_real
                {
                    $$ = make_str ("real_const", $<strvalue>1, NULL, 0);
                } | 
                T_logical
                {
                    $$ = make_str ("logical_const", $<strvalue>1, NULL, 0);
                } | 
                T_character
                {
                    $$ = make_str ("char_const", $<strvalue>1, NULL, 0);
                } | 
                T_string
                {
                    $$ = make_str ("string_const", $<strvalue>1, NULL, 0);
                };

complex_constant : T_lparen T_real T_colon sign T_real T_rparen
                {
                    //in case of complex number concatenate the 2 real parts into "part1 part2" and add them as a string node
                    //needs to be freed
                    struct AST_Node *ar[1] = { $4 };
                    char *buffer = malloc(strlen(($<strvalue>2) + strlen($<strvalue>5) + 2) * sizeof(char));
                    strcat(buffer, $<strvalue>2);
                    strcat(buffer, " ");
                    strcat(buffer, $<strvalue>5);
                    $$ = make_str ("complex_const", buffer, ar, 1);
                };




statements      : statements labeled_statement
                {
                    struct AST_Node *ar[2] = { $1, $2 };
                    $$ = make_node ("statements", ar, 2);
                } | 
                labeled_statement
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("statements", ar, 1);
                };

labeled_statement : label statement
                {
                    struct AST_Node *ar[2] = { $1, $2 };
                    $$ = make_node ("labeled_statement", ar, 2);
                } | 
                statement
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("unlabeled_statement", ar, 1);
                };

label           : T_integer
                {
                    $$ = make_str ("label_int", $<strvalue>1, NULL, 0);
                };

statement       : simple_statement
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("simple_statement", ar, 1);
                } | 
                compound_statement
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("comp_statement", ar, 1);
                };

simple_statement : assignment
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("assignment", ar, 1);
                } |
                goto_statement
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("goto", ar, 1);
                } |
                if_statement
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("if", ar, 1);
                } |
                subroutine_call
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("subroutine", ar, 1);
                } |
                io_statement
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("io", ar, 1);
                } |
                T_continue
                {
                    $$ = make_node ("contiue", NULL, 0);
                } |
                T_return
                {
                    $$ = make_node ("return", NULL, 0);
                } |
                T_stop
                {
                    $$ = make_node ("stop", NULL, 0);
                };

assignment      : variable T_assign expression
                {
                    struct AST_Node *ar[2] = { $1, $3 };
                    $$ = make_node ("assignment", ar, 2);
                };

variable        : T_id T_lparen expressions T_rparen
                {
                    struct AST_Node *ar[1] = { $3 };
                    $$ = make_node ("array_assignment", ar, 1);
                } |
                T_listfunc T_lparen expression T_rparen
                {
                    struct AST_Node *ar[1] = { $3 };
                    $$ = make_str ("list_assignment", $<strvalue>1, ar, 1);
                } |
                T_id
                {
                    $$ = make_str ("var_assignment", $<strvalue>1, NULL, 0);
                };

expressions     : expressions T_comma expression
                {
                    struct AST_Node *ar[2] = { $1, $3 };
                    $$ = make_node ("expressions", ar, 2);
                } | 
                expression
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("expression", ar, 1);
                };

expression      :expression T_orop expression 
                {
                    struct AST_Node *ar[2] = { $1, $3 };
                    $$ = make_node ("or", ar, 2);
                } |
                expression T_andop expression
                {
                    struct AST_Node *ar[2] = { $1, $3 };
                    $$ = make_node ("and", ar, 2);
                } |
                expression T_relop expression
                {
                    struct AST_Node *ar[2] = { $1, $3 };
                    $$ = make_str ("rel", $<strvalue>2, ar, 2);
                } |
                expression T_addop expression
                {
                    struct AST_Node *ar[2] = { $1, $3 };
                    $$ = make_str ("add", $<strvalue>2, ar, 2);
                } |
                expression T_mulop expression
                {
                    struct AST_Node *ar[2] = { $1, $3 };
                    $$ = make_node ("mul", ar, 2);
                } |
                expression T_divop expression
                {
                    struct AST_Node *ar[2] = { $1, $3 };
                    $$ = make_node ("div", ar, 2);
                } |
                expression T_powop expression
                {
                    struct AST_Node *ar[2] = { $1, $3 };
                    $$ = make_node ("pow", ar, 2);
                } |
                T_notop expression
                {
                    struct AST_Node *ar[1] = { $2 };
                    $$ = make_node ("not_single", ar, 1);
                } |
                T_addop expression
                {
                    struct AST_Node *ar[1] = { $2 };
                    $$ = make_str ("add_single", $<strvalue>1, ar, 1);
                } |
                variable
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("variable", ar, 1);
                } |
                simple_constant
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("simple_constant", ar, 1);
                } |
                T_length T_lparen expression T_rparen
                {
                    struct AST_Node *ar[1] = { $3 };
                    $$ = make_node ("length", ar, 1);
                } |
                T_new T_lparen expression T_rparen
                {
                    struct AST_Node *ar[1] = { $3 };
                    $$ = make_node ("new", ar, 1);
                } |
                T_lparen expression T_rparen
                {
                    struct AST_Node *ar[1] = { $2 };
                    $$ = make_node ("single_expression", ar, 1);
                } |
                T_lparen expression T_colon expression T_rparen
                {
                    struct AST_Node *ar[2] = { $2, $4 };
                    $$ = make_node ("coloned_expression", ar, 2);
                } |
                listexpression
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("list_expression", ar, 1);
                };

listexpression  : T_lbrack expressions T_rbrack
                {
                    struct AST_Node *ar[1] = { $2 };
                    $$ = make_node ("list_position", ar, 1);
                } |
                T_lbrack T_rbrack
                {
                    $$ = make_node ("empty_list_position", NULL, 0);
                };

goto_statement  :T_goto label
                {
                    struct AST_Node *ar[1] = { $2 };
                    $$ = make_node ("simple_goto", ar, 1);
                } |
                T_goto T_id T_comma T_lparen labels T_rparen
                {
                    struct AST_Node *ar[1] = { $5 };
                    $$ = make_node ("complex_goto", ar, 1);
                };

labels          : labels T_comma label
                {
                    struct AST_Node *ar[2] = { $1, $3 };
                    $$ = make_node ("label", ar, 2);
                } | 
                label
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("label", ar, 1);
                };

if_statement    : T_if T_lparen expression T_rparen label T_comma label T_comma label
                {
                    struct AST_Node *ar[4] = { $3, $5, $7, $9 };
                    $$ = make_node ("arithmetic_if", ar, 4);
                } |
                T_if T_lparen expression T_rparen simple_statement
                {
                    struct AST_Node *ar[2] = { $3, $5 };
                    $$ = make_node ("logical_if", ar, 2);
                };

subroutine_call : T_call variable
                {
                    struct AST_Node *ar[1] = { $2 };
                    $$ = make_node ("call", ar, 1);
                };

io_statement    : T_read read_list
                {
                    struct AST_Node *ar[1] = { $2 };
                    $$ = make_node ("read", ar, 1);
                } | 
                T_write write_list
                {
                    struct AST_Node *ar[1] = { $2 };
                    $$ = make_node ("write", ar, 1);
                };

read_list       : read_list T_comma read_item
                {
                    struct AST_Node *ar[2] = { $1, $3 };
                    $$ = make_node ("read_list", ar, 2);
                } | 
                read_item
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("read_list", ar, 1);
                };

read_item       : variable
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("read_variable", ar, 1);
                } |
                T_lparen read_list T_comma T_id T_assign iter_space T_rparen
                {
                    struct AST_Node *ar[2] = { $2, $6 };
                    $$ = make_node ("read_loop", ar, 2);
                };

iter_space      : expression T_comma expression step
                {
                    struct AST_Node *ar[3] = { $1, $3, $4 };
                    $$ = make_node ("loop_expression", ar, 3);
                };

step            : T_comma expression
                {
                    struct AST_Node *ar[1] = { $2 };
                    $$ = make_node ("step_expression", ar, 1);
                } |
                {
                    $$ = make_node ("empty_step", NULL, 0);
                };

write_list      : write_list T_comma write_item
                {
                    struct AST_Node *ar[2] = { $1, $3 };
                    $$ = make_node ("write_list", ar, 2);
                } | 
                write_item
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("write_list", ar, 1);
                };

write_item      : expression
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("write_variable", ar, 1);
                } | 
                T_lparen write_list T_comma T_id T_assign iter_space T_rparen
                {
                    struct AST_Node *ar[2] = { $2, $6 };
                    $$ = make_node ("write_loop", ar, 2);
                };

compound_statement : branch_statement
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("branch_statement", ar, 1);
                } | 
                loop_statement
                {
                    struct AST_Node *ar[1] = { $1 };
                    $$ = make_node ("loop_statement", ar, 1);
                };

branch_statement : T_if T_lparen expression T_rparen T_then body tail
                {
                    struct AST_Node *ar[3] = { $3, $6, $7 };
                    $$ = make_node ("branch_if", ar, 3);
                };

tail            : T_else body T_endif
                {
                    struct AST_Node *ar[1] = { $2 };
                    $$ = make_node ("else", ar, 1);
                } |
                T_endif
                {
                    $$ = make_node ("null", NULL, 0);
                };

loop_statement  : T_do T_id T_assign iter_space body T_enddo
                {
                    struct AST_Node *ar[2] = { $4, $5 };
                    $$ = make_str ("loop", $<strvalue>2, ar, 2);
                };

subprograms     : subprograms subprogram
                {
                    struct AST_Node *ar[2] = { $1, $2 };
                    $$ = make_node ("subprograms", ar, 2);
                } |
                {
                    $$ = make_node ("null", NULL, 0);
                };

subprogram      : header body T_end
                {
                    struct AST_Node *ar[2] = { $1, $2 };
                    $$ = make_node ("subprogram", ar, 2);
                };

header          : type listspec T_function T_id T_lparen formal_parameters T_rparen
                {
                    struct AST_Node *ar[3] = { $1, $2, $6 };
                    $$ = make_str ("header1", $<strvalue>4, ar, 3);

                    char *name = $<strvalue>4;
                    char **data  = malloc (10000 * sizeof(char*)); //any subprogram can have up to 10000 parameters (probably enough)
                    data[0] = "function";
                    data[1] = $1->type; //add function name and type to the data passed to the symbol table
                    int counter = 3; //counts the amount of parameters
                    struct AST_Node *node = $6;
                    for (;;) {
                        data[counter++] = node->children[0]->type; //add parameter's type

                        if      (node->c_count == 2) break; //if the traverse has ended then break
                        else if (node->c_count == 3) {
                            node = node->children[2];
                        }
                    }
                    char *num = malloc (counter * sizeof(char));
                    sprintf(num, "%d", counter - 3);
                    data[2] = num; //set the number of args, converted to string (remember to free)
                    data = realloc (data, (counter + 3) * sizeof(char*));
                    
                    add_symbol(table, name, data, counter);
                    free(data);
                } |
                T_subroutine T_id T_lparen formal_parameters T_rparen
                {
                    struct AST_Node *ar[1] = { $4 };
                    $$ = make_str ("header2", $<strvalue>2, ar, 1);

                    //same with subroutine
                    char *name = $<strvalue>2;
                    char **data  = malloc (10000 * sizeof(char*)); //any subprogram can have up to 10000 parameters (probably enough)
                    data[0] = "subroutine";
                    int counter = 2;
                    struct AST_Node *node = $4;
                    for (;;) {
                        data[counter++] = node->children[0]->type;

                        if      (node->c_count == 2) break;
                        else if (node->c_count == 3) {
                            node = node->children[2];
                        }
                    }
                    char *num = malloc(counter * sizeof(char));
                    sprintf(num, "%d", counter - 2);
                    data[1] = num; //set the number converted to string
                    data = realloc (data, (counter + 2) * sizeof(char*));
                    
                    add_symbol(table, name, data, counter);
                    free(data);
                } |
                T_subroutine T_id
                {
                    $$ = make_str ("header3", $<strvalue>2, NULL, 0);

                    char *name = $<strvalue>2;
                    char *ar[1] = { "subroutine" };
                    add_symbol(table, name, ar, 1);
                };
//add stuff about parameters to symbol table
formal_parameters : type vars T_comma formal_parameters
                {
                    struct AST_Node *ar[3] = { $1, $2, $4 };
                    $$ = make_node ("formal_parameters", ar, 3);
                } | 
                type vars
                {
                    struct AST_Node *ar[2] = { $1, $2 };
                    $$ = make_node ("formal_parameters", ar, 2);
                };

%%

int yyerror(char *msg)
{
	printf("Error: %s\n", msg);
	return 0;
}

int main()
{
    table = create_table(10);
    printf("--------------------------------------------------------\nSyntax Tree:\n");
    yyparse();

    printf("--------------------------------------------------------\nSymbol Table:\n");
    print_table(table);

	return 0;
}
