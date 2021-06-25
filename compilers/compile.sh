#!/bin/sh

yacc -d parser.y

flex lexer.l

gcc lex.yy.c y.tab.c AST.c Symbol_Table.c -g -o comp

