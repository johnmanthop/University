/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h> 

    #include "AST.h"
    #include "Symbol_Table.h"

    int yydebug = 1;
    struct Symbol_Table *table;

#line 83 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 245 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_function = 3,                 /* T_function  */
  YYSYMBOL_T_subroutine = 4,               /* T_subroutine  */
  YYSYMBOL_T_end = 5,                      /* T_end  */
  YYSYMBOL_T_common = 6,                   /* T_common  */
  YYSYMBOL_T_integer = 7,                  /* T_integer  */
  YYSYMBOL_T_real = 8,                     /* T_real  */
  YYSYMBOL_T_complex = 9,                  /* T_complex  */
  YYSYMBOL_T_logical = 10,                 /* T_logical  */
  YYSYMBOL_T_character = 11,               /* T_character  */
  YYSYMBOL_T_string = 12,                  /* T_string  */
  YYSYMBOL_T_list = 13,                    /* T_list  */
  YYSYMBOL_T_data = 14,                    /* T_data  */
  YYSYMBOL_T_continue = 15,                /* T_continue  */
  YYSYMBOL_T_goto = 16,                    /* T_goto  */
  YYSYMBOL_T_call = 17,                    /* T_call  */
  YYSYMBOL_T_read = 18,                    /* T_read  */
  YYSYMBOL_T_write = 19,                   /* T_write  */
  YYSYMBOL_T_length = 20,                  /* T_length  */
  YYSYMBOL_T_new = 21,                     /* T_new  */
  YYSYMBOL_T_if = 22,                      /* T_if  */
  YYSYMBOL_T_then = 23,                    /* T_then  */
  YYSYMBOL_T_else = 24,                    /* T_else  */
  YYSYMBOL_T_endif = 25,                   /* T_endif  */
  YYSYMBOL_T_do = 26,                      /* T_do  */
  YYSYMBOL_T_enddo = 27,                   /* T_enddo  */
  YYSYMBOL_T_stop = 28,                    /* T_stop  */
  YYSYMBOL_T_return = 29,                  /* T_return  */
  YYSYMBOL_T_comma = 30,                   /* T_comma  */
  YYSYMBOL_T_listfunc = 31,                /* T_listfunc  */
  YYSYMBOL_T_id = 32,                      /* T_id  */
  YYSYMBOL_T_lbrack = 33,                  /* T_lbrack  */
  YYSYMBOL_T_rbrack = 34,                  /* T_rbrack  */
  YYSYMBOL_T_lparen = 35,                  /* T_lparen  */
  YYSYMBOL_T_rparen = 36,                  /* T_rparen  */
  YYSYMBOL_T_divop = 37,                   /* T_divop  */
  YYSYMBOL_T_addop = 38,                   /* T_addop  */
  YYSYMBOL_T_mulop = 39,                   /* T_mulop  */
  YYSYMBOL_T_powop = 40,                   /* T_powop  */
  YYSYMBOL_T_orop = 41,                    /* T_orop  */
  YYSYMBOL_T_andop = 42,                   /* T_andop  */
  YYSYMBOL_T_notop = 43,                   /* T_notop  */
  YYSYMBOL_T_relop = 44,                   /* T_relop  */
  YYSYMBOL_T_colon = 45,                   /* T_colon  */
  YYSYMBOL_T_assign = 46,                  /* T_assign  */
  YYSYMBOL_T_intlit = 47,                  /* T_intlit  */
  YYSYMBOL_T_reallit = 48,                 /* T_reallit  */
  YYSYMBOL_T_complexlit = 49,              /* T_complexlit  */
  YYSYMBOL_T_logicallit = 50,              /* T_logicallit  */
  YYSYMBOL_T_characterlit = 51,            /* T_characterlit  */
  YYSYMBOL_T_stringlit = 52,               /* T_stringlit  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_program = 54,                   /* program  */
  YYSYMBOL_body = 55,                      /* body  */
  YYSYMBOL_declarations = 56,              /* declarations  */
  YYSYMBOL_type = 57,                      /* type  */
  YYSYMBOL_vars = 58,                      /* vars  */
  YYSYMBOL_undef_variable = 59,            /* undef_variable  */
  YYSYMBOL_listspec = 60,                  /* listspec  */
  YYSYMBOL_dims = 61,                      /* dims  */
  YYSYMBOL_dim = 62,                       /* dim  */
  YYSYMBOL_cblock_list = 63,               /* cblock_list  */
  YYSYMBOL_cblock = 64,                    /* cblock  */
  YYSYMBOL_id_list = 65,                   /* id_list  */
  YYSYMBOL_vals = 66,                      /* vals  */
  YYSYMBOL_value_list = 67,                /* value_list  */
  YYSYMBOL_values = 68,                    /* values  */
  YYSYMBOL_value = 69,                     /* value  */
  YYSYMBOL_repeat = 70,                    /* repeat  */
  YYSYMBOL_sign = 71,                      /* sign  */
  YYSYMBOL_constant = 72,                  /* constant  */
  YYSYMBOL_simple_constant = 73,           /* simple_constant  */
  YYSYMBOL_complex_constant = 74,          /* complex_constant  */
  YYSYMBOL_statements = 75,                /* statements  */
  YYSYMBOL_labeled_statement = 76,         /* labeled_statement  */
  YYSYMBOL_label = 77,                     /* label  */
  YYSYMBOL_statement = 78,                 /* statement  */
  YYSYMBOL_simple_statement = 79,          /* simple_statement  */
  YYSYMBOL_assignment = 80,                /* assignment  */
  YYSYMBOL_variable = 81,                  /* variable  */
  YYSYMBOL_expressions = 82,               /* expressions  */
  YYSYMBOL_expression = 83,                /* expression  */
  YYSYMBOL_listexpression = 84,            /* listexpression  */
  YYSYMBOL_goto_statement = 85,            /* goto_statement  */
  YYSYMBOL_labels = 86,                    /* labels  */
  YYSYMBOL_if_statement = 87,              /* if_statement  */
  YYSYMBOL_subroutine_call = 88,           /* subroutine_call  */
  YYSYMBOL_io_statement = 89,              /* io_statement  */
  YYSYMBOL_read_list = 90,                 /* read_list  */
  YYSYMBOL_read_item = 91,                 /* read_item  */
  YYSYMBOL_iter_space = 92,                /* iter_space  */
  YYSYMBOL_step = 93,                      /* step  */
  YYSYMBOL_write_list = 94,                /* write_list  */
  YYSYMBOL_write_item = 95,                /* write_item  */
  YYSYMBOL_compound_statement = 96,        /* compound_statement  */
  YYSYMBOL_branch_statement = 97,          /* branch_statement  */
  YYSYMBOL_tail = 98,                      /* tail  */
  YYSYMBOL_loop_statement = 99,            /* loop_statement  */
  YYSYMBOL_subprograms = 100,              /* subprograms  */
  YYSYMBOL_subprogram = 101,               /* subprogram  */
  YYSYMBOL_header = 102,                   /* header  */
  YYSYMBOL_formal_parameters = 103         /* formal_parameters  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   413

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  121
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  240

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   307


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    90,    90,   103,   109,   134,   157,   162,   166,   170,
     174,   178,   182,   186,   191,   196,   202,   207,   213,   217,
     221,   226,   232,   236,   241,   246,   252,   258,   263,   268,
     273,   279,   285,   290,   296,   301,   306,   312,   316,   321,
     325,   329,   334,   340,   344,   348,   352,   356,   361,   376,
     381,   387,   392,   398,   403,   408,   414,   419,   424,   429,
     434,   439,   443,   447,   452,   458,   463,   468,   473,   478,
     484,   489,   494,   499,   504,   509,   514,   519,   524,   529,
     534,   539,   544,   549,   554,   559,   565,   570,   575,   580,
     586,   591,   597,   602,   608,   614,   619,   625,   630,   636,
     641,   647,   653,   658,   662,   667,   673,   678,   684,   689,
     695,   701,   706,   711,   717,   722,   726,   732,   759,   786,
     795,   800
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "T_function",
  "T_subroutine", "T_end", "T_common", "T_integer", "T_real", "T_complex",
  "T_logical", "T_character", "T_string", "T_list", "T_data", "T_continue",
  "T_goto", "T_call", "T_read", "T_write", "T_length", "T_new", "T_if",
  "T_then", "T_else", "T_endif", "T_do", "T_enddo", "T_stop", "T_return",
  "T_comma", "T_listfunc", "T_id", "T_lbrack", "T_rbrack", "T_lparen",
  "T_rparen", "T_divop", "T_addop", "T_mulop", "T_powop", "T_orop",
  "T_andop", "T_notop", "T_relop", "T_colon", "T_assign", "T_intlit",
  "T_reallit", "T_complexlit", "T_logicallit", "T_characterlit",
  "T_stringlit", "$accept", "program", "body", "declarations", "type",
  "vars", "undef_variable", "listspec", "dims", "dim", "cblock_list",
  "cblock", "id_list", "vals", "value_list", "values", "value", "repeat",
  "sign", "constant", "simple_constant", "complex_constant", "statements",
  "labeled_statement", "label", "statement", "simple_statement",
  "assignment", "variable", "expressions", "expression", "listexpression",
  "goto_statement", "labels", "if_statement", "subroutine_call",
  "io_statement", "read_list", "read_item", "iter_space", "step",
  "write_list", "write_item", "compound_statement", "branch_statement",
  "tail", "loop_statement", "subprograms", "subprogram", "header",
  "formal_parameters", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307
};
#endif

#define YYPACT_NINF (-199)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -199,    61,    14,    79,  -199,  -199,    34,  -199,    48,  -199,
      10,    19,   106,   172,    56,    71,  -199,  -199,    67,    69,
    -199,  -199,  -199,  -199,  -199,  -199,    96,   251,  -199,   295,
    -199,  -199,  -199,    66,  -199,  -199,  -199,  -199,  -199,  -199,
    -199,    17,    89,    34,  -199,    87,   103,   110,  -199,  -199,
     106,  -199,   118,  -199,  -199,  -199,  -199,  -199,  -199,   123,
     126,   135,   172,   206,   206,  -199,  -199,   367,  -199,   141,
    -199,   206,   119,   206,   206,  -199,   158,  -199,   162,  -199,
    -199,   206,   163,    96,  -199,  -199,   174,  -199,   152,  -199,
     180,   184,   190,   106,   206,   206,  -199,   206,   105,   367,
      78,   191,   169,   137,   206,   206,   206,   206,   206,   206,
     206,   172,   314,   206,   323,     4,    96,   188,   367,   196,
     232,   220,   204,   201,   243,    25,  -199,     1,  -199,   218,
    -199,  -199,  -199,    87,   252,   122,  -199,   332,   341,    78,
     206,  -199,  -199,   206,   222,   231,   169,   231,   231,   208,
     137,   224,  -199,   269,   292,  -199,  -199,  -199,  -199,    38,
     150,   240,  -199,  -199,   244,  -199,   230,  -199,   152,  -199,
    -199,    25,  -199,  -199,    52,   -19,  -199,  -199,   367,   350,
     -17,   246,  -199,   248,  -199,   206,   262,  -199,  -199,    70,
    -199,    96,   254,   258,   263,   218,  -199,  -199,   252,  -199,
     206,  -199,   206,   206,   161,   252,   305,  -199,    38,  -199,
     266,  -199,   150,  -199,   291,  -199,   271,   272,   359,  -199,
    -199,  -199,   290,   206,  -199,  -199,    26,   289,   301,  -199,
    -199,   287,   303,   252,   367,  -199,  -199,  -199,  -199,  -199
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       7,     0,     0,     0,     1,   115,     0,    53,     0,    61,
       0,     0,     0,     0,     0,     0,    63,    62,     0,    67,
       8,     9,    10,    11,    12,    13,    19,     3,    50,     0,
      52,    54,    56,     0,    57,    58,    59,    60,    55,   108,
     109,     2,     0,     5,    25,     0,     6,     0,    88,    94,
       0,    99,    95,    98,    43,    44,    45,    46,    47,     0,
       0,     0,     0,     0,     0,    80,    79,   106,    85,    96,
     105,     0,     0,     0,     0,    18,     4,    15,     0,    49,
      51,     0,     0,    19,   114,     7,     0,    24,     0,    30,
       0,     0,     0,     0,     0,     0,    87,     0,     0,    69,
     106,     0,    78,    77,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    19,    17,    64,   119,
       0,     0,     0,    43,     0,     0,    38,     0,    33,    40,
      36,    41,    42,     0,     0,     0,    97,     0,     0,     0,
       0,    86,    83,     0,     0,    75,    73,    74,    76,    70,
      71,    72,   104,     0,     0,     7,    66,    65,    14,     0,
       0,     0,   116,    28,    26,    37,     0,    35,     0,    31,
      39,     0,    29,    91,     0,    67,    81,    82,    68,     0,
      67,     0,     7,     0,    93,     0,     0,    22,    23,     0,
      21,    19,     0,     0,     0,    40,    32,    34,     0,    89,
       0,    84,     0,     0,     0,     0,   103,   113,     0,    16,
     121,   118,     0,    27,     0,    90,     0,     0,     0,     7,
     112,   110,     0,     0,   101,    20,    19,     0,     0,   100,
     107,     0,     0,     0,   102,   120,   117,    48,   111,    92
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -199,  -199,   -83,  -199,    22,   147,  -113,   256,  -199,   132,
    -199,   298,  -199,  -199,   215,  -199,   189,  -199,   171,  -119,
     -84,  -199,  -199,   348,    -9,   355,  -148,  -199,    -3,   319,
     -51,  -199,  -199,  -199,  -199,  -199,  -199,   352,   -86,  -121,
    -199,   351,   -96,  -199,  -199,  -199,  -199,  -199,  -199,  -199,
    -198
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,   191,    76,    77,    78,   189,   190,
      43,    44,   164,    46,    89,   127,   128,   129,   171,   130,
      65,   132,    27,    28,    29,    30,    31,    32,    66,    98,
      67,    68,    34,   174,    35,    36,    37,    52,    53,   155,
     224,    69,    70,    38,    39,   221,    40,    41,    84,    85,
     192
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      33,    48,   121,   158,   131,   184,   167,   136,    49,    51,
      99,   100,   102,   103,   227,   152,    74,     7,    74,     5,
     112,    82,   114,    99,    33,    26,    33,   200,   235,   202,
     118,   168,    54,    55,   140,    56,    57,    58,   169,    75,
     157,   131,    47,   137,   138,   187,   139,    51,   152,   136,
      18,    19,   197,   145,   146,   147,   148,   149,   150,   151,
     124,     4,   154,    83,    20,    21,    22,    23,    24,    25,
     188,    42,   186,    20,    21,    22,    23,    24,    25,   216,
      45,   217,   198,   184,   131,     6,     7,   131,   199,   178,
      51,    71,   179,     8,     9,    10,    11,    12,    13,   204,
     208,    14,    73,    72,    74,    15,   209,    16,    17,    75,
      18,    19,    81,   158,   142,   104,   105,   106,   107,   108,
     109,    86,   110,   143,    88,   173,    20,    21,    22,    23,
      24,    25,    51,    90,   206,   140,   232,    18,    19,   141,
      91,    50,    54,    55,   183,    56,    57,    58,    93,   154,
      33,   154,   218,    18,   175,    59,    60,    50,    94,   123,
      55,    95,    56,    57,    58,   113,    18,    19,    61,    96,
      97,   111,   234,    63,   104,   105,   106,   107,    64,    54,
      55,   110,    56,    57,    58,   219,   220,   124,   116,   215,
     125,   126,    59,    60,   117,   119,   222,    20,    21,    22,
      23,    24,    25,    18,    19,    61,   104,    62,   106,   107,
      63,   122,   133,    54,    55,    64,    56,    57,    58,   134,
     135,   144,   183,   159,   239,   162,    59,    60,    33,    54,
      55,   160,    56,    57,    58,   161,   163,    18,    19,    61,
     165,    97,    59,    60,    63,   104,   105,   106,   107,    64,
     109,   166,   110,    18,   180,    61,   170,    62,     7,     7,
      63,   104,   105,   106,   107,    64,     9,    10,    11,    12,
      13,   107,   193,    14,   194,   195,     7,    15,   205,    16,
      17,   203,    18,    19,     9,    10,    11,    12,    13,   207,
     211,   181,   182,   212,     7,   213,   226,    16,    17,   228,
      18,    19,     9,    10,    11,    12,    13,   229,   230,   181,
       9,    10,    11,    12,    13,    16,    17,    14,    18,    19,
     233,    15,   185,    16,    17,   236,    18,    19,   238,   104,
     105,   106,   107,   108,   109,   223,   110,   237,   210,   120,
     225,    87,   104,   105,   106,   107,   108,   109,   172,   110,
     153,   104,   105,   106,   107,   108,   109,   196,   110,   156,
     104,   105,   106,   107,   108,   109,   214,   110,   176,   104,
     105,   106,   107,   108,   109,    79,   110,   177,   104,   105,
     106,   107,   108,   109,    80,   110,   201,   104,   105,   106,
     107,   108,   109,   115,   110,   231,   104,   105,   106,   107,
     108,   109,    92,   110,   104,   105,   106,   107,   108,   109,
       0,   110,     0,   101
};

static const yytype_int16 yycheck[] =
{
       3,    10,    85,   116,    88,   153,   125,    93,    11,    12,
      61,    62,    63,    64,   212,   111,    35,     7,    35,     5,
      71,     4,    73,    74,    27,     3,    29,    46,   226,    46,
      81,    30,     7,     8,    30,    10,    11,    12,    37,    13,
      36,   125,    32,    94,    95,     7,    97,    50,   144,   135,
      31,    32,   171,   104,   105,   106,   107,   108,   109,   110,
      35,     0,   113,    41,    47,    48,    49,    50,    51,    52,
      32,    37,   155,    47,    48,    49,    50,    51,    52,   200,
      32,   202,    30,   231,   168,     6,     7,   171,    36,   140,
      93,    35,   143,    14,    15,    16,    17,    18,    19,   182,
      30,    22,    35,    32,    35,    26,    36,    28,    29,    13,
      31,    32,    46,   226,    36,    37,    38,    39,    40,    41,
      42,    32,    44,    45,    37,   134,    47,    48,    49,    50,
      51,    52,   135,    30,   185,    30,   219,    31,    32,    34,
      30,    35,     7,     8,   153,    10,    11,    12,    30,   200,
     153,   202,   203,    31,    32,    20,    21,    35,    35,     7,
       8,    35,    10,    11,    12,    46,    31,    32,    33,    34,
      35,    30,   223,    38,    37,    38,    39,    40,    43,     7,
       8,    44,    10,    11,    12,    24,    25,    35,    30,   198,
      38,    39,    20,    21,    32,    32,   205,    47,    48,    49,
      50,    51,    52,    31,    32,    33,    37,    35,    39,    40,
      38,    37,    32,     7,     8,    43,    10,    11,    12,    35,
      30,    30,   231,    35,   233,     5,    20,    21,   231,     7,
       8,    35,    10,    11,    12,     3,    32,    31,    32,    33,
      39,    35,    20,    21,    38,    37,    38,    39,    40,    43,
      42,     8,    44,    31,    32,    33,    38,    35,     7,     7,
      38,    37,    38,    39,    40,    43,    15,    16,    17,    18,
      19,    40,    32,    22,    30,    45,     7,    26,    30,    28,
      29,    35,    31,    32,    15,    16,    17,    18,    19,    27,
      36,    22,    23,    35,     7,    32,    30,    28,    29,     8,
      31,    32,    15,    16,    17,    18,    19,    36,    36,    22,
      15,    16,    17,    18,    19,    28,    29,    22,    31,    32,
      30,    26,    30,    28,    29,    36,    31,    32,    25,    37,
      38,    39,    40,    41,    42,    30,    44,    36,   191,    83,
     208,    43,    37,    38,    39,    40,    41,    42,   133,    44,
      36,    37,    38,    39,    40,    41,    42,   168,    44,    36,
      37,    38,    39,    40,    41,    42,   195,    44,    36,    37,
      38,    39,    40,    41,    42,    27,    44,    36,    37,    38,
      39,    40,    41,    42,    29,    44,    36,    37,    38,    39,
      40,    41,    42,    74,    44,    36,    37,    38,    39,    40,
      41,    42,    50,    44,    37,    38,    39,    40,    41,    42,
      -1,    44,    -1,    62
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    54,    55,    56,     0,     5,     6,     7,    14,    15,
      16,    17,    18,    19,    22,    26,    28,    29,    31,    32,
      47,    48,    49,    50,    51,    52,    57,    75,    76,    77,
      78,    79,    80,    81,    85,    87,    88,    89,    96,    97,
      99,   100,    37,    63,    64,    32,    66,    32,    77,    81,
      35,    81,    90,    91,     7,     8,    10,    11,    12,    20,
      21,    33,    35,    38,    43,    73,    81,    83,    84,    94,
      95,    35,    32,    35,    35,    13,    58,    59,    60,    76,
      78,    46,     4,    57,   101,   102,    32,    64,    37,    67,
      30,    30,    90,    30,    35,    35,    34,    35,    82,    83,
      83,    94,    83,    83,    37,    38,    39,    40,    41,    42,
      44,    30,    83,    46,    83,    82,    30,    32,    83,    32,
      60,    55,    37,     7,    35,    38,    39,    68,    69,    70,
      72,    73,    74,    32,    35,    30,    91,    83,    83,    83,
      30,    34,    36,    45,    30,    83,    83,    83,    83,    83,
      83,    83,    95,    36,    83,    92,    36,    36,    59,    35,
      35,     3,     5,    32,    65,    39,     8,    72,    30,    37,
      38,    71,    67,    77,    86,    32,    36,    36,    83,    83,
      32,    22,    23,    77,    79,    30,    55,     7,    32,    61,
      62,    57,   103,    32,    30,    45,    69,    72,    30,    36,
      46,    36,    46,    35,    55,    30,    83,    27,    30,    36,
      58,    36,    35,    32,    71,    77,    92,    92,    83,    24,
      25,    98,    77,    30,    93,    62,    30,   103,     8,    36,
      36,    36,    55,    30,    83,   103,    36,    36,    25,    77
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    56,    56,    56,    56,    57,    57,
      57,    57,    57,    57,    58,    58,    59,    59,    60,    60,
      61,    61,    62,    62,    63,    63,    64,    65,    65,    66,
      66,    67,    68,    68,    69,    69,    69,    70,    70,    71,
      71,    72,    72,    73,    73,    73,    73,    73,    74,    75,
      75,    76,    76,    77,    78,    78,    79,    79,    79,    79,
      79,    79,    79,    79,    80,    81,    81,    81,    82,    82,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    84,    84,    85,    85,
      86,    86,    87,    87,    88,    89,    89,    90,    90,    91,
      91,    92,    93,    93,    94,    94,    95,    95,    96,    96,
      97,    98,    98,    99,   100,   100,   101,   102,   102,   102,
     103,   103
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     3,     3,     3,     0,     1,     1,
       1,     1,     1,     1,     3,     1,     5,     2,     1,     0,
       3,     1,     1,     1,     2,     1,     4,     3,     1,     4,
       2,     3,     3,     1,     3,     2,     1,     2,     1,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     6,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     4,     4,     1,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     1,
       1,     4,     4,     3,     5,     1,     3,     2,     2,     6,
       3,     1,     9,     5,     2,     2,     2,     3,     1,     1,
       7,     4,     2,     0,     3,     1,     1,     7,     1,     1,
       7,     3,     1,     6,     2,     0,     3,     7,     5,     2,
       4,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: body T_end subprograms  */
#line 91 "parser.y"
                {
                    //Each rule has their productions as children
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("program", ar, 2);

                    //when parsing is done print the tree
                    const long long s = 10000000; //tree can have up to this many nodes
                    char *flag = malloc(s);
                    for (long long i = 0; i < s; ++i) flag[i] = 1;
                    print_tree((yyval.node), flag, 0, 0);
                }
#line 1541 "y.tab.c"
    break;

  case 3: /* body: declarations statements  */
#line 104 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-1].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("body", ar, 2);
                }
#line 1550 "y.tab.c"
    break;

  case 4: /* declarations: declarations type vars  */
#line 110 "parser.y"
                {
                    struct AST_Node *ar[3] = { (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("decl_typevars", ar, 3);
                    
                    //traverse the tree and get data about variables to put into the symbol table
                    struct AST_Node *node = (yyvsp[0].node); //starting node
                    for (;;) {
                        struct AST_Node *undef_var;

                        if (node->c_count == 2) { //find the undef_var
                            //node's second child is the variable
                            undef_var = node->children[1];
                        } else if (node->c_count == 1) {
                            undef_var = node->children[0];
                        }

                        char *name = undef_var->strvalue; //get undef_var's data
                        char *ar[2] = { "variable", (yyvsp[-1].node)->type };
                        add_symbol (table, name, ar, 2); //add data to symbol table

                        if (node->c_count == 1) break; //if there are no more undef_vars then break
                        else node = node->children[0]; //else set new starting node and keep going
                    }
                }
#line 1579 "y.tab.c"
    break;

  case 5: /* declarations: declarations T_common cblock_list  */
#line 135 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("decl_common", ar, 2);
                    //same as before
                    struct AST_Node *node = (yyvsp[0].node);
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
                }
#line 1606 "y.tab.c"
    break;

  case 6: /* declarations: declarations T_data vals  */
#line 158 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("decl_data", ar, 2);
                }
#line 1615 "y.tab.c"
    break;

  case 7: /* declarations: %empty  */
#line 162 "parser.y"
                {
                    (yyval.node) = make_node ("null", NULL, 0);
                }
#line 1623 "y.tab.c"
    break;

  case 8: /* type: T_intlit  */
#line 167 "parser.y"
                {
                    (yyval.node) = make_node ("int_type", NULL, 0);
                }
#line 1631 "y.tab.c"
    break;

  case 9: /* type: T_reallit  */
#line 171 "parser.y"
                {
                    (yyval.node) = make_node ("real_type", NULL, 0);
                }
#line 1639 "y.tab.c"
    break;

  case 10: /* type: T_complexlit  */
#line 175 "parser.y"
                {
                    (yyval.node) = make_node ("complex_type", NULL, 0);
                }
#line 1647 "y.tab.c"
    break;

  case 11: /* type: T_logicallit  */
#line 179 "parser.y"
                {
                    (yyval.node) = make_node ("logical_type", NULL, 0);
                }
#line 1655 "y.tab.c"
    break;

  case 12: /* type: T_characterlit  */
#line 183 "parser.y"
                {
                    (yyval.node) = make_node ("char_type", NULL, 0);
                }
#line 1663 "y.tab.c"
    break;

  case 13: /* type: T_stringlit  */
#line 187 "parser.y"
                {
                    (yyval.node) = make_node ("string_type", NULL, 0);
                }
#line 1671 "y.tab.c"
    break;

  case 14: /* vars: vars T_comma undef_variable  */
#line 192 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("vars", ar, 2);
                }
#line 1680 "y.tab.c"
    break;

  case 15: /* vars: undef_variable  */
#line 197 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("vars", ar, 1);
                }
#line 1689 "y.tab.c"
    break;

  case 16: /* undef_variable: listspec T_id T_lparen dims T_rparen  */
#line 203 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-4].node), (yyvsp[-1].node) };
                    (yyval.node) = make_str ("array_var", (yyvsp[-3].strvalue), ar, 2);
                }
#line 1698 "y.tab.c"
    break;

  case 17: /* undef_variable: listspec T_id  */
#line 208 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[-1].node) };
                    (yyval.node) = make_str ("scalar_var", (yyvsp[0].strvalue), ar, 1);
                }
#line 1707 "y.tab.c"
    break;

  case 18: /* listspec: T_list  */
#line 214 "parser.y"
                {
                    (yyval.node) = make_str ("list_spec", "list", NULL, 0);
                }
#line 1715 "y.tab.c"
    break;

  case 19: /* listspec: %empty  */
#line 217 "parser.y"
                {
                    (yyval.node) = make_str ("list_spec", "nolist", NULL, 0);
                }
#line 1723 "y.tab.c"
    break;

  case 20: /* dims: dims T_comma dim  */
#line 222 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("dims", ar, 2);
                }
#line 1732 "y.tab.c"
    break;

  case 21: /* dims: dim  */
#line 227 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("dim", ar, 1);
                }
#line 1741 "y.tab.c"
    break;

  case 22: /* dim: T_integer  */
#line 233 "parser.y"
                {
                    (yyval.node) = make_str ("dim_int", (yyvsp[0].strvalue), NULL, 0);
                }
#line 1749 "y.tab.c"
    break;

  case 23: /* dim: T_id  */
#line 237 "parser.y"
                {
                    (yyval.node) = make_str ("dim_var", (yyvsp[0].strvalue), NULL, 0);
                }
#line 1757 "y.tab.c"
    break;

  case 24: /* cblock_list: cblock_list cblock  */
#line 242 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-1].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("common", ar, 2);
                }
#line 1766 "y.tab.c"
    break;

  case 25: /* cblock_list: cblock  */
#line 247 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("common", ar, 1);
                }
#line 1775 "y.tab.c"
    break;

  case 26: /* cblock: T_divop T_id T_divop id_list  */
#line 253 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[0].node) };
                    (yyval.node) = make_str ("common_block", (yyvsp[-2].strvalue), ar, 2);
                }
#line 1784 "y.tab.c"
    break;

  case 27: /* id_list: id_list T_comma T_id  */
#line 259 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[-2].node) };
                    (yyval.node) = make_str ("common_var", (yyvsp[0].strvalue), ar, 1);
                }
#line 1793 "y.tab.c"
    break;

  case 28: /* id_list: T_id  */
#line 264 "parser.y"
                {
                    (yyval.node) = make_str ("common_var", (yyvsp[0].strvalue), NULL, 0);
                }
#line 1801 "y.tab.c"
    break;

  case 29: /* vals: vals T_comma T_id value_list  */
#line 269 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-3].node), (yyvsp[0].node) };
                    (yyval.node) = make_str ("value_decl", (yyvsp[-1].strvalue), ar, 2);
                }
#line 1810 "y.tab.c"
    break;

  case 30: /* vals: T_id value_list  */
#line 274 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_str ("value_decl", (yyvsp[-1].strvalue), ar, 1);
                }
#line 1819 "y.tab.c"
    break;

  case 31: /* value_list: T_divop values T_divop  */
#line 280 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[-1].node) };
                    (yyval.node) = make_node ("value_list", ar, 1);
                }
#line 1828 "y.tab.c"
    break;

  case 32: /* values: values T_comma value  */
#line 286 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("value", ar, 2);
                }
#line 1837 "y.tab.c"
    break;

  case 33: /* values: value  */
#line 291 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("value", ar, 1);
                }
#line 1846 "y.tab.c"
    break;

  case 34: /* value: repeat sign constant  */
#line 297 "parser.y"
                {
                    struct AST_Node *ar[3] = { (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("repeated_value", ar, 3);
                }
#line 1855 "y.tab.c"
    break;

  case 35: /* value: T_addop constant  */
#line 302 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("signed_value", ar, 1);
                }
#line 1864 "y.tab.c"
    break;

  case 36: /* value: constant  */
#line 307 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("unsigned_value", ar, 1);
                }
#line 1873 "y.tab.c"
    break;

  case 37: /* repeat: T_integer T_mulop  */
#line 313 "parser.y"
                {
                    (yyval.node) = make_str ("repeater1", (yyvsp[-1].strvalue), NULL, 0);
                }
#line 1881 "y.tab.c"
    break;

  case 38: /* repeat: T_mulop  */
#line 317 "parser.y"
                {
                    (yyval.node) = make_node ("repeater2", NULL, 0);
                }
#line 1889 "y.tab.c"
    break;

  case 39: /* sign: T_addop  */
#line 322 "parser.y"
                {
                    (yyval.node) = make_str ("sign", (yyvsp[0].strvalue), NULL, 0);
                }
#line 1897 "y.tab.c"
    break;

  case 40: /* sign: %empty  */
#line 325 "parser.y"
                {
                    (yyval.node) = make_node ("null", NULL, 0);
                }
#line 1905 "y.tab.c"
    break;

  case 41: /* constant: simple_constant  */
#line 330 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("simple_constant", ar, 1);
                }
#line 1914 "y.tab.c"
    break;

  case 42: /* constant: complex_constant  */
#line 335 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("complex_constant", ar, 1);
                }
#line 1923 "y.tab.c"
    break;

  case 43: /* simple_constant: T_integer  */
#line 341 "parser.y"
                {
                    (yyval.node) = make_str ("int_const", (yyvsp[0].strvalue), NULL, 0);
                }
#line 1931 "y.tab.c"
    break;

  case 44: /* simple_constant: T_real  */
#line 345 "parser.y"
                {
                    (yyval.node) = make_str ("real_const", (yyvsp[0].strvalue), NULL, 0);
                }
#line 1939 "y.tab.c"
    break;

  case 45: /* simple_constant: T_logical  */
#line 349 "parser.y"
                {
                    (yyval.node) = make_str ("logical_const", (yyvsp[0].strvalue), NULL, 0);
                }
#line 1947 "y.tab.c"
    break;

  case 46: /* simple_constant: T_character  */
#line 353 "parser.y"
                {
                    (yyval.node) = make_str ("char_const", (yyvsp[0].strvalue), NULL, 0);
                }
#line 1955 "y.tab.c"
    break;

  case 47: /* simple_constant: T_string  */
#line 357 "parser.y"
                {
                    (yyval.node) = make_str ("string_const", (yyvsp[0].strvalue), NULL, 0);
                }
#line 1963 "y.tab.c"
    break;

  case 48: /* complex_constant: T_lparen T_real T_colon sign T_real T_rparen  */
#line 362 "parser.y"
                {
                    //in case of complex number concatenate the 2 real parts into "part1 part2" and add them as a string node
                    //needs to be freed
                    struct AST_Node *ar[1] = { (yyvsp[-2].node) };
                    char *buffer = malloc(strlen(((yyvsp[-4].strvalue)) + strlen((yyvsp[-1].strvalue)) + 2) * sizeof(char));
                    strcat(buffer, (yyvsp[-4].strvalue));
                    strcat(buffer, " ");
                    strcat(buffer, (yyvsp[-1].strvalue));
                    (yyval.node) = make_str ("complex_const", buffer, ar, 1);
                }
#line 1978 "y.tab.c"
    break;

  case 49: /* statements: statements labeled_statement  */
#line 377 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-1].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("statements", ar, 2);
                }
#line 1987 "y.tab.c"
    break;

  case 50: /* statements: labeled_statement  */
#line 382 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("statements", ar, 1);
                }
#line 1996 "y.tab.c"
    break;

  case 51: /* labeled_statement: label statement  */
#line 388 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-1].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("labeled_statement", ar, 2);
                }
#line 2005 "y.tab.c"
    break;

  case 52: /* labeled_statement: statement  */
#line 393 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("unlabeled_statement", ar, 1);
                }
#line 2014 "y.tab.c"
    break;

  case 53: /* label: T_integer  */
#line 399 "parser.y"
                {
                    (yyval.node) = make_str ("label_int", (yyvsp[0].strvalue), NULL, 0);
                }
#line 2022 "y.tab.c"
    break;

  case 54: /* statement: simple_statement  */
#line 404 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("simple_statement", ar, 1);
                }
#line 2031 "y.tab.c"
    break;

  case 55: /* statement: compound_statement  */
#line 409 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("comp_statement", ar, 1);
                }
#line 2040 "y.tab.c"
    break;

  case 56: /* simple_statement: assignment  */
#line 415 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("assignment", ar, 1);
                }
#line 2049 "y.tab.c"
    break;

  case 57: /* simple_statement: goto_statement  */
#line 420 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("goto", ar, 1);
                }
#line 2058 "y.tab.c"
    break;

  case 58: /* simple_statement: if_statement  */
#line 425 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("if", ar, 1);
                }
#line 2067 "y.tab.c"
    break;

  case 59: /* simple_statement: subroutine_call  */
#line 430 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("subroutine", ar, 1);
                }
#line 2076 "y.tab.c"
    break;

  case 60: /* simple_statement: io_statement  */
#line 435 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("io", ar, 1);
                }
#line 2085 "y.tab.c"
    break;

  case 61: /* simple_statement: T_continue  */
#line 440 "parser.y"
                {
                    (yyval.node) = make_node ("contiue", NULL, 0);
                }
#line 2093 "y.tab.c"
    break;

  case 62: /* simple_statement: T_return  */
#line 444 "parser.y"
                {
                    (yyval.node) = make_node ("return", NULL, 0);
                }
#line 2101 "y.tab.c"
    break;

  case 63: /* simple_statement: T_stop  */
#line 448 "parser.y"
                {
                    (yyval.node) = make_node ("stop", NULL, 0);
                }
#line 2109 "y.tab.c"
    break;

  case 64: /* assignment: variable T_assign expression  */
#line 453 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("assignment", ar, 2);
                }
#line 2118 "y.tab.c"
    break;

  case 65: /* variable: T_id T_lparen expressions T_rparen  */
#line 459 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[-1].node) };
                    (yyval.node) = make_node ("array_assignment", ar, 1);
                }
#line 2127 "y.tab.c"
    break;

  case 66: /* variable: T_listfunc T_lparen expression T_rparen  */
#line 464 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[-1].node) };
                    (yyval.node) = make_str ("list_assignment", (yyvsp[-3].strvalue), ar, 1);
                }
#line 2136 "y.tab.c"
    break;

  case 67: /* variable: T_id  */
#line 469 "parser.y"
                {
                    (yyval.node) = make_str ("var_assignment", (yyvsp[0].strvalue), NULL, 0);
                }
#line 2144 "y.tab.c"
    break;

  case 68: /* expressions: expressions T_comma expression  */
#line 474 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("expressions", ar, 2);
                }
#line 2153 "y.tab.c"
    break;

  case 69: /* expressions: expression  */
#line 479 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("expression", ar, 1);
                }
#line 2162 "y.tab.c"
    break;

  case 70: /* expression: expression T_orop expression  */
#line 485 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("or", ar, 2);
                }
#line 2171 "y.tab.c"
    break;

  case 71: /* expression: expression T_andop expression  */
#line 490 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("and", ar, 2);
                }
#line 2180 "y.tab.c"
    break;

  case 72: /* expression: expression T_relop expression  */
#line 495 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_str ("rel", (yyvsp[-1].strvalue), ar, 2);
                }
#line 2189 "y.tab.c"
    break;

  case 73: /* expression: expression T_addop expression  */
#line 500 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_str ("add", (yyvsp[-1].strvalue), ar, 2);
                }
#line 2198 "y.tab.c"
    break;

  case 74: /* expression: expression T_mulop expression  */
#line 505 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("mul", ar, 2);
                }
#line 2207 "y.tab.c"
    break;

  case 75: /* expression: expression T_divop expression  */
#line 510 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("div", ar, 2);
                }
#line 2216 "y.tab.c"
    break;

  case 76: /* expression: expression T_powop expression  */
#line 515 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("pow", ar, 2);
                }
#line 2225 "y.tab.c"
    break;

  case 77: /* expression: T_notop expression  */
#line 520 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("not_single", ar, 1);
                }
#line 2234 "y.tab.c"
    break;

  case 78: /* expression: T_addop expression  */
#line 525 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_str ("add_single", (yyvsp[-1].strvalue), ar, 1);
                }
#line 2243 "y.tab.c"
    break;

  case 79: /* expression: variable  */
#line 530 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("variable", ar, 1);
                }
#line 2252 "y.tab.c"
    break;

  case 80: /* expression: simple_constant  */
#line 535 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("simple_constant", ar, 1);
                }
#line 2261 "y.tab.c"
    break;

  case 81: /* expression: T_length T_lparen expression T_rparen  */
#line 540 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[-1].node) };
                    (yyval.node) = make_node ("length", ar, 1);
                }
#line 2270 "y.tab.c"
    break;

  case 82: /* expression: T_new T_lparen expression T_rparen  */
#line 545 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[-1].node) };
                    (yyval.node) = make_node ("new", ar, 1);
                }
#line 2279 "y.tab.c"
    break;

  case 83: /* expression: T_lparen expression T_rparen  */
#line 550 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[-1].node) };
                    (yyval.node) = make_node ("single_expression", ar, 1);
                }
#line 2288 "y.tab.c"
    break;

  case 84: /* expression: T_lparen expression T_colon expression T_rparen  */
#line 555 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-3].node), (yyvsp[-1].node) };
                    (yyval.node) = make_node ("coloned_expression", ar, 2);
                }
#line 2297 "y.tab.c"
    break;

  case 85: /* expression: listexpression  */
#line 560 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("list_expression", ar, 1);
                }
#line 2306 "y.tab.c"
    break;

  case 86: /* listexpression: T_lbrack expressions T_rbrack  */
#line 566 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[-1].node) };
                    (yyval.node) = make_node ("list_position", ar, 1);
                }
#line 2315 "y.tab.c"
    break;

  case 87: /* listexpression: T_lbrack T_rbrack  */
#line 571 "parser.y"
                {
                    (yyval.node) = make_node ("empty_list_position", NULL, 0);
                }
#line 2323 "y.tab.c"
    break;

  case 88: /* goto_statement: T_goto label  */
#line 576 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("simple_goto", ar, 1);
                }
#line 2332 "y.tab.c"
    break;

  case 89: /* goto_statement: T_goto T_id T_comma T_lparen labels T_rparen  */
#line 581 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[-1].node) };
                    (yyval.node) = make_node ("complex_goto", ar, 1);
                }
#line 2341 "y.tab.c"
    break;

  case 90: /* labels: labels T_comma label  */
#line 587 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("label", ar, 2);
                }
#line 2350 "y.tab.c"
    break;

  case 91: /* labels: label  */
#line 592 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("label", ar, 1);
                }
#line 2359 "y.tab.c"
    break;

  case 92: /* if_statement: T_if T_lparen expression T_rparen label T_comma label T_comma label  */
#line 598 "parser.y"
                {
                    struct AST_Node *ar[4] = { (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("arithmetic_if", ar, 4);
                }
#line 2368 "y.tab.c"
    break;

  case 93: /* if_statement: T_if T_lparen expression T_rparen simple_statement  */
#line 603 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("logical_if", ar, 2);
                }
#line 2377 "y.tab.c"
    break;

  case 94: /* subroutine_call: T_call variable  */
#line 609 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("call", ar, 1);
                }
#line 2386 "y.tab.c"
    break;

  case 95: /* io_statement: T_read read_list  */
#line 615 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("read", ar, 1);
                }
#line 2395 "y.tab.c"
    break;

  case 96: /* io_statement: T_write write_list  */
#line 620 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("write", ar, 1);
                }
#line 2404 "y.tab.c"
    break;

  case 97: /* read_list: read_list T_comma read_item  */
#line 626 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("read_list", ar, 2);
                }
#line 2413 "y.tab.c"
    break;

  case 98: /* read_list: read_item  */
#line 631 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("read_list", ar, 1);
                }
#line 2422 "y.tab.c"
    break;

  case 99: /* read_item: variable  */
#line 637 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("read_variable", ar, 1);
                }
#line 2431 "y.tab.c"
    break;

  case 100: /* read_item: T_lparen read_list T_comma T_id T_assign iter_space T_rparen  */
#line 642 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-5].node), (yyvsp[-1].node) };
                    (yyval.node) = make_node ("read_loop", ar, 2);
                }
#line 2440 "y.tab.c"
    break;

  case 101: /* iter_space: expression T_comma expression step  */
#line 648 "parser.y"
                {
                    struct AST_Node *ar[3] = { (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("loop_expression", ar, 3);
                }
#line 2449 "y.tab.c"
    break;

  case 102: /* step: T_comma expression  */
#line 654 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("step_expression", ar, 1);
                }
#line 2458 "y.tab.c"
    break;

  case 103: /* step: %empty  */
#line 658 "parser.y"
                {
                    (yyval.node) = make_node ("empty_step", NULL, 0);
                }
#line 2466 "y.tab.c"
    break;

  case 104: /* write_list: write_list T_comma write_item  */
#line 663 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("write_list", ar, 2);
                }
#line 2475 "y.tab.c"
    break;

  case 105: /* write_list: write_item  */
#line 668 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("write_list", ar, 1);
                }
#line 2484 "y.tab.c"
    break;

  case 106: /* write_item: expression  */
#line 674 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("write_variable", ar, 1);
                }
#line 2493 "y.tab.c"
    break;

  case 107: /* write_item: T_lparen write_list T_comma T_id T_assign iter_space T_rparen  */
#line 679 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-5].node), (yyvsp[-1].node) };
                    (yyval.node) = make_node ("write_loop", ar, 2);
                }
#line 2502 "y.tab.c"
    break;

  case 108: /* compound_statement: branch_statement  */
#line 685 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("branch_statement", ar, 1);
                }
#line 2511 "y.tab.c"
    break;

  case 109: /* compound_statement: loop_statement  */
#line 690 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[0].node) };
                    (yyval.node) = make_node ("loop_statement", ar, 1);
                }
#line 2520 "y.tab.c"
    break;

  case 110: /* branch_statement: T_if T_lparen expression T_rparen T_then body tail  */
#line 696 "parser.y"
                {
                    struct AST_Node *ar[3] = { (yyvsp[-4].node), (yyvsp[-1].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("branch_if", ar, 3);
                }
#line 2529 "y.tab.c"
    break;

  case 111: /* tail: T_else body T_endif  */
#line 702 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[-1].node) };
                    (yyval.node) = make_node ("else", ar, 1);
                }
#line 2538 "y.tab.c"
    break;

  case 112: /* tail: T_endif  */
#line 707 "parser.y"
                {
                    (yyval.node) = make_node ("null", NULL, 0);
                }
#line 2546 "y.tab.c"
    break;

  case 113: /* loop_statement: T_do T_id T_assign iter_space body T_enddo  */
#line 712 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[-1].node) };
                    (yyval.node) = make_str ("loop", (yyvsp[-4].strvalue), ar, 2);
                }
#line 2555 "y.tab.c"
    break;

  case 114: /* subprograms: subprograms subprogram  */
#line 718 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-1].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("subprograms", ar, 2);
                }
#line 2564 "y.tab.c"
    break;

  case 115: /* subprograms: %empty  */
#line 722 "parser.y"
                {
                    (yyval.node) = make_node ("null", NULL, 0);
                }
#line 2572 "y.tab.c"
    break;

  case 116: /* subprogram: header body T_end  */
#line 727 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-2].node), (yyvsp[-1].node) };
                    (yyval.node) = make_node ("subprogram", ar, 2);
                }
#line 2581 "y.tab.c"
    break;

  case 117: /* header: type listspec T_function T_id T_lparen formal_parameters T_rparen  */
#line 733 "parser.y"
                {
                    struct AST_Node *ar[3] = { (yyvsp[-6].node), (yyvsp[-5].node), (yyvsp[-1].node) };
                    (yyval.node) = make_str ("header1", (yyvsp[-3].strvalue), ar, 3);

                    char *name = (yyvsp[-3].strvalue);
                    char **data  = malloc (10000 * sizeof(char*)); //any subprogram can have up to 10000 parameters (probably enough)
                    data[0] = "function";
                    data[1] = (yyvsp[-6].node)->type; //add function name and type to the data passed to the symbol table
                    int counter = 3; //counts the amount of parameters
                    struct AST_Node *node = (yyvsp[-1].node);
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
                }
#line 2612 "y.tab.c"
    break;

  case 118: /* header: T_subroutine T_id T_lparen formal_parameters T_rparen  */
#line 760 "parser.y"
                {
                    struct AST_Node *ar[1] = { (yyvsp[-1].node) };
                    (yyval.node) = make_str ("header2", (yyvsp[-3].strvalue), ar, 1);

                    //same with subroutine
                    char *name = (yyvsp[-3].strvalue);
                    char **data  = malloc (10000 * sizeof(char*)); //any subprogram can have up to 10000 parameters (probably enough)
                    data[0] = "subroutine";
                    int counter = 2;
                    struct AST_Node *node = (yyvsp[-1].node);
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
                }
#line 2643 "y.tab.c"
    break;

  case 119: /* header: T_subroutine T_id  */
#line 787 "parser.y"
                {
                    (yyval.node) = make_str ("header3", (yyvsp[0].strvalue), NULL, 0);

                    char *name = (yyvsp[0].strvalue);
                    char *ar[1] = { "subroutine" };
                    add_symbol(table, name, ar, 1);
                }
#line 2655 "y.tab.c"
    break;

  case 120: /* formal_parameters: type vars T_comma formal_parameters  */
#line 796 "parser.y"
                {
                    struct AST_Node *ar[3] = { (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("formal_parameters", ar, 3);
                }
#line 2664 "y.tab.c"
    break;

  case 121: /* formal_parameters: type vars  */
#line 801 "parser.y"
                {
                    struct AST_Node *ar[2] = { (yyvsp[-1].node), (yyvsp[0].node) };
                    (yyval.node) = make_node ("formal_parameters", ar, 2);
                }
#line 2673 "y.tab.c"
    break;


#line 2677 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 806 "parser.y"


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
