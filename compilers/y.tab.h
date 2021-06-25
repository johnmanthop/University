/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_function = 258,              /* T_function  */
    T_subroutine = 259,            /* T_subroutine  */
    T_end = 260,                   /* T_end  */
    T_common = 261,                /* T_common  */
    T_integer = 262,               /* T_integer  */
    T_real = 263,                  /* T_real  */
    T_complex = 264,               /* T_complex  */
    T_logical = 265,               /* T_logical  */
    T_character = 266,             /* T_character  */
    T_string = 267,                /* T_string  */
    T_list = 268,                  /* T_list  */
    T_data = 269,                  /* T_data  */
    T_continue = 270,              /* T_continue  */
    T_goto = 271,                  /* T_goto  */
    T_call = 272,                  /* T_call  */
    T_read = 273,                  /* T_read  */
    T_write = 274,                 /* T_write  */
    T_length = 275,                /* T_length  */
    T_new = 276,                   /* T_new  */
    T_if = 277,                    /* T_if  */
    T_then = 278,                  /* T_then  */
    T_else = 279,                  /* T_else  */
    T_endif = 280,                 /* T_endif  */
    T_do = 281,                    /* T_do  */
    T_enddo = 282,                 /* T_enddo  */
    T_stop = 283,                  /* T_stop  */
    T_return = 284,                /* T_return  */
    T_comma = 285,                 /* T_comma  */
    T_listfunc = 286,              /* T_listfunc  */
    T_id = 287,                    /* T_id  */
    T_lbrack = 288,                /* T_lbrack  */
    T_rbrack = 289,                /* T_rbrack  */
    T_lparen = 290,                /* T_lparen  */
    T_rparen = 291,                /* T_rparen  */
    T_divop = 292,                 /* T_divop  */
    T_addop = 293,                 /* T_addop  */
    T_mulop = 294,                 /* T_mulop  */
    T_powop = 295,                 /* T_powop  */
    T_orop = 296,                  /* T_orop  */
    T_andop = 297,                 /* T_andop  */
    T_notop = 298,                 /* T_notop  */
    T_relop = 299,                 /* T_relop  */
    T_colon = 300,                 /* T_colon  */
    T_assign = 301,                /* T_assign  */
    T_intlit = 302,                /* T_intlit  */
    T_reallit = 303,               /* T_reallit  */
    T_complexlit = 304,            /* T_complexlit  */
    T_logicallit = 305,            /* T_logicallit  */
    T_characterlit = 306,          /* T_characterlit  */
    T_stringlit = 307              /* T_stringlit  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define T_function 258
#define T_subroutine 259
#define T_end 260
#define T_common 261
#define T_integer 262
#define T_real 263
#define T_complex 264
#define T_logical 265
#define T_character 266
#define T_string 267
#define T_list 268
#define T_data 269
#define T_continue 270
#define T_goto 271
#define T_call 272
#define T_read 273
#define T_write 274
#define T_length 275
#define T_new 276
#define T_if 277
#define T_then 278
#define T_else 279
#define T_endif 280
#define T_do 281
#define T_enddo 282
#define T_stop 283
#define T_return 284
#define T_comma 285
#define T_listfunc 286
#define T_id 287
#define T_lbrack 288
#define T_rbrack 289
#define T_lparen 290
#define T_rparen 291
#define T_divop 292
#define T_addop 293
#define T_mulop 294
#define T_powop 295
#define T_orop 296
#define T_andop 297
#define T_notop 298
#define T_relop 299
#define T_colon 300
#define T_assign 301
#define T_intlit 302
#define T_reallit 303
#define T_complexlit 304
#define T_logicallit 305
#define T_characterlit 306
#define T_stringlit 307

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 13 "parser.y"

    struct AST_Node *node;
    int numvalue;
    char *strvalue;

#line 176 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
