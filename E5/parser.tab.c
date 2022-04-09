/* A Bison parser, made by GNU Bison 3.5.1.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "parser.y"

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  
  #include "instr_lst.h"
  #include "semantic.h"
  #include "asp.h"
  #include "util.h"
  #include "types.h"
  
  #define YYDEBUG 1
  
  extern void *arvore;
  
  int get_line_number (void);
  int yylex(void);
  void yyerror (char const *s);

#line 90 "parser.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_PR_INT = 258,
    TK_PR_FLOAT = 259,
    TK_PR_BOOL = 260,
    TK_PR_CHAR = 261,
    TK_PR_STRING = 262,
    TK_PR_IF = 263,
    TK_PR_THEN = 264,
    TK_PR_ELSE = 265,
    TK_PR_WHILE = 266,
    TK_PR_DO = 267,
    TK_PR_INPUT = 268,
    TK_PR_OUTPUT = 269,
    TK_PR_RETURN = 270,
    TK_PR_CONST = 271,
    TK_PR_STATIC = 272,
    TK_PR_FOREACH = 273,
    TK_PR_FOR = 274,
    TK_PR_SWITCH = 275,
    TK_PR_CASE = 276,
    TK_PR_BREAK = 277,
    TK_PR_CONTINUE = 278,
    TK_PR_CLASS = 279,
    TK_PR_PRIVATE = 280,
    TK_PR_PUBLIC = 281,
    TK_PR_PROTECTED = 282,
    TK_PR_END = 283,
    TK_PR_DEFAULT = 284,
    TOKEN_ERRO = 285,
    TK_OC_LE = 286,
    TK_OC_GE = 287,
    TK_OC_EQ = 288,
    TK_OC_NE = 289,
    TK_OC_AND = 290,
    TK_OC_OR = 291,
    TK_OC_SL = 292,
    TK_OC_SR = 293,
    TK_LIT_INT = 294,
    TK_LIT_FLOAT = 295,
    TK_LIT_FALSE = 296,
    TK_LIT_TRUE = 297,
    TK_LIT_CHAR = 298,
    TK_LIT_STRING = 299,
    TK_IDENTIFICADOR = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef struct YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   267

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  122
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  234

#define YYUNDEFTOK  2
#define YYMAXUTOK   300


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    67,     2,    68,     2,    65,    58,     2,
      50,    51,    63,    61,    47,    62,     2,    64,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    55,    46,
      59,    54,    60,    56,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    48,     2,    49,    66,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,    57,    53,     2,     2,     2,     2,
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
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   115,   115,   115,   120,   121,   121,   131,   131,   141,
     145,   146,   149,   153,   158,   159,   166,   167,   170,   174,
     178,   179,   182,   183,   190,   191,   191,   197,   198,   202,
     203,   204,   205,   206,   207,   208,   209,   213,   218,   222,
     226,   232,   236,   237,   246,   256,   261,   270,   275,   284,
     290,   296,   303,   304,   310,   311,   315,   324,   334,   343,
     357,   358,   359,   362,   365,   370,   375,   380,   384,   385,
     392,   395,   398,   402,   405,   409,   412,   416,   419,   423,
     426,   431,   436,   439,   443,   447,   452,   457,   460,   464,
     468,   471,   475,   479,   482,   485,   488,   491,   492,   493,
     494,   495,   496,   497,   498,   501,   502,   506,   511,   516,
     520,   521,   529,   534,   538,   542,   546,   550,   558,   559,
     560,   561,   562
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_PR_INT", "TK_PR_FLOAT", "TK_PR_BOOL",
  "TK_PR_CHAR", "TK_PR_STRING", "TK_PR_IF", "TK_PR_THEN", "TK_PR_ELSE",
  "TK_PR_WHILE", "TK_PR_DO", "TK_PR_INPUT", "TK_PR_OUTPUT", "TK_PR_RETURN",
  "TK_PR_CONST", "TK_PR_STATIC", "TK_PR_FOREACH", "TK_PR_FOR",
  "TK_PR_SWITCH", "TK_PR_CASE", "TK_PR_BREAK", "TK_PR_CONTINUE",
  "TK_PR_CLASS", "TK_PR_PRIVATE", "TK_PR_PUBLIC", "TK_PR_PROTECTED",
  "TK_PR_END", "TK_PR_DEFAULT", "TOKEN_ERRO", "TK_OC_LE", "TK_OC_GE",
  "TK_OC_EQ", "TK_OC_NE", "TK_OC_AND", "TK_OC_OR", "TK_OC_SL", "TK_OC_SR",
  "TK_LIT_INT", "TK_LIT_FLOAT", "TK_LIT_FALSE", "TK_LIT_TRUE",
  "TK_LIT_CHAR", "TK_LIT_STRING", "TK_IDENTIFICADOR", "';'", "','", "'['",
  "']'", "'('", "')'", "'{'", "'}'", "'='", "':'", "'?'", "'|'", "'&'",
  "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'^'", "'!'", "'#'",
  "$accept", "s", "$@1", "prog", "$@2", "$@3", "global_decl",
  "global_decl_list", "function_params", "function_params_list",
  "function_body", "statement_block", "$@4", "statement_list", "statement",
  "local_decl", "local_decl_list", "assignment", "in_out", "function_call",
  "function_call_list", "shift", "control_flow", "control_if",
  "control_for", "control_while", "control_jump", "expression",
  "expression10", "expression9", "expression8", "expression7",
  "expression6", "expression5", "expression4", "expression3",
  "expression2", "expression1", "expression0", "operand", "literal",
  "type", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,    59,    44,    91,    93,
      40,    41,   123,   125,    61,    58,    63,   124,    38,    60,
      62,    43,    45,    42,    47,    37,    94,    33,    35
};
# endif

#define YYPACT_NINF (-160)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -160,    52,  -160,  -160,   116,  -160,  -160,  -160,  -160,  -160,
     232,  -160,    10,    15,    36,    19,    36,    25,    30,    43,
      16,  -160,  -160,  -160,  -160,    49,  -160,    38,   232,  -160,
      48,    44,    53,    53,    60,    71,  -160,    84,    87,  -160,
    -160,    30,    89,   121,    88,   104,    73,   180,   145,   232,
     211,   110,  -160,  -160,    26,   113,  -160,   125,   114,   142,
     126,   127,   128,   131,   132,   133,  -160,  -160,  -160,   136,
     138,  -160,   121,  -160,   145,   145,  -160,  -160,  -160,  -160,
    -160,  -160,  -160,  -160,  -160,  -160,  -160,   -17,   145,   145,
     145,   145,   145,   145,   145,   145,  -160,  -160,    -8,   141,
     139,   144,    78,   -15,    68,   -22,   123,  -160,  -160,  -160,
     138,   232,   138,   154,   161,   165,   145,   130,   145,  -160,
     142,  -160,  -160,  -160,  -160,  -160,  -160,  -160,  -160,  -160,
    -160,     7,  -160,  -160,   158,   159,   145,   160,  -160,  -160,
    -160,  -160,  -160,  -160,  -160,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,  -160,   138,  -160,     3,   150,  -160,  -160,   177,
    -160,   190,   193,  -160,   191,   189,   138,   194,   230,   196,
    -160,   141,    -6,   139,   144,    78,   -15,   -15,    68,    68,
      68,    68,   -22,   -22,   123,   123,   123,  -160,  -160,   145,
     145,    -1,  -160,   145,  -160,   200,   201,  -160,   233,   194,
    -160,   145,   202,   195,   210,   213,   145,  -160,   138,   138,
     194,  -160,   217,   203,   154,  -160,  -160,  -160,  -160,  -160,
    -160,   204,   194,  -160
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     9,     1,     3,   118,   119,   120,   121,   122,
       0,     4,     0,     0,    14,     0,    14,     0,     0,     0,
       0,     5,    11,     7,    10,    14,    12,     0,     0,    16,
       0,     0,     0,     0,    15,     0,    17,    20,     0,     6,
       8,     0,    21,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    68,    69,     0,    25,    22,     0,     0,    28,
       0,     0,     0,     0,     0,     0,    60,    61,    62,     0,
       0,    13,     0,    18,     0,     0,    49,   112,   113,   114,
     115,   116,   117,    50,    51,   108,   109,   107,     0,     0,
       0,     0,     0,     0,     0,     0,   110,    67,    71,    73,
      75,    77,    79,    82,    87,    90,    94,    96,   104,   106,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    24,
       0,    29,    23,    27,    31,    30,    32,    33,    34,    36,
      35,    42,    40,    19,     0,     0,     0,     0,    99,   101,
      97,    98,   102,   100,   103,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    38,     0,    37,     0,     0,    56,    58,     0,
      52,     0,    55,    47,     0,     0,     0,     0,     0,     0,
     105,    72,     0,    74,    76,    78,    80,    81,    85,    86,
      83,    84,    88,    89,    91,    92,    93,    95,    39,     0,
       0,     0,    53,     0,    26,    46,    45,    41,    63,     0,
     111,     0,     0,     0,     0,     0,     0,    54,     0,     0,
       0,    66,    70,     0,     0,    57,    59,    48,    44,    43,
      64,     0,     0,    65
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -160,  -160,  -160,  -160,  -160,  -160,  -160,    21,   238,   -14,
     223,  -159,  -160,   -54,  -160,  -160,  -104,  -111,  -160,   -35,
      55,  -160,  -160,  -160,  -160,  -160,  -160,   -48,  -142,   115,
     112,   117,   118,   -16,   -11,     6,   -81,   -80,  -160,  -160,
      86,    -3
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     4,    32,    33,    11,    15,    21,    30,
      39,    57,   120,    58,    59,    60,   132,    61,    62,    96,
     171,    64,    65,    66,    67,    68,    69,   172,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
      84,    31
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      97,    12,   166,    63,   182,   123,   162,    13,   164,   138,
     139,   140,   141,   142,   143,   144,   152,   153,   208,     5,
       6,     7,     8,     9,    63,    35,   134,   135,   145,    73,
     145,   136,    28,   117,    17,    70,   214,   215,   175,    26,
     137,   158,   159,   160,   154,   155,   110,   112,   146,   211,
     221,   199,     3,   216,   176,    14,    70,   118,   133,   198,
      16,   230,    71,   114,   115,    22,   174,    29,   169,   222,
     173,    24,   207,   233,   116,    25,   117,   194,   195,   196,
     118,   197,    27,    18,    19,    63,    20,    34,   179,    37,
       5,     6,     7,     8,     9,    44,    18,    19,    45,    36,
      46,    47,    48,    49,    50,    38,    51,    41,   163,    52,
      53,   150,   151,   231,   228,   229,    42,    70,    76,     5,
       6,     7,     8,     9,     5,     6,     7,     8,     9,   156,
     157,    43,    54,    10,   186,   187,    72,    28,    74,    55,
      56,   188,   189,   190,   191,     5,     6,     7,     8,     9,
      44,   212,   213,    45,    75,    46,    47,    48,    49,    50,
     113,    51,   192,   193,    52,    53,   119,   122,   227,    85,
      86,   121,   124,   125,   126,    87,   147,   127,   128,   129,
      88,   170,   130,   131,    85,    86,    89,    54,    90,   161,
      87,    91,    92,    93,    55,    88,   148,    94,    95,   165,
     167,    89,   149,    90,   168,   200,    91,    92,    93,   177,
     178,   180,    94,    95,     5,     6,     7,     8,     9,    77,
      78,    79,    80,    81,    82,    83,   201,   111,    77,    78,
      79,    80,    81,    82,   205,     5,     6,     7,     8,     9,
     203,   202,   209,   220,   204,   210,    55,   218,   219,   225,
     224,   223,   226,   145,    23,   232,    40,   216,   217,   183,
     181,   206,     0,     0,     0,   184,     0,   185
};

static const yytype_int16 yycheck[] =
{
      48,     4,   113,    38,   146,    59,   110,    10,   112,    89,
      90,    91,    92,    93,    94,    95,    31,    32,   177,     3,
       4,     5,     6,     7,    59,    28,    74,    75,    36,    43,
      36,    48,    16,    50,    13,    38,    37,    38,    31,    18,
      88,    63,    64,    65,    59,    60,    49,    50,    56,    55,
     209,    48,     0,    54,    47,    45,    59,    54,    72,   163,
      45,   220,    41,    37,    38,    46,   120,    51,   116,   211,
     118,    46,   176,   232,    48,    45,    50,   158,   159,   160,
      54,   161,    39,    47,    48,   120,    50,    49,   136,    45,
       3,     4,     5,     6,     7,     8,    47,    48,    11,    51,
      13,    14,    15,    16,    17,    52,    19,    47,   111,    22,
      23,    33,    34,   224,   218,   219,    45,   120,    45,     3,
       4,     5,     6,     7,     3,     4,     5,     6,     7,    61,
      62,    47,    45,    17,   150,   151,    47,    16,    50,    52,
      53,   152,   153,   154,   155,     3,     4,     5,     6,     7,
       8,   199,   200,    11,    50,    13,    14,    15,    16,    17,
      50,    19,   156,   157,    22,    23,    53,    53,   216,    39,
      40,    46,    46,    46,    46,    45,    35,    46,    46,    46,
      50,    51,    46,    45,    39,    40,    56,    45,    58,    66,
      45,    61,    62,    63,    52,    50,    57,    67,    68,    45,
      39,    56,    58,    58,    39,    55,    61,    62,    63,    51,
      51,    51,    67,    68,     3,     4,     5,     6,     7,    39,
      40,    41,    42,    43,    44,    45,    49,    16,    39,    40,
      41,    42,    43,    44,    45,     3,     4,     5,     6,     7,
      47,    51,    12,    10,    53,    49,    52,    47,    47,    39,
      55,    49,    39,    36,    16,    51,    33,    54,   203,   147,
     145,   175,    -1,    -1,    -1,   148,    -1,   149
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    70,    71,     0,    72,     3,     4,     5,     6,     7,
      17,    75,   110,   110,    45,    76,    45,    76,    47,    48,
      50,    77,    46,    77,    46,    45,    76,    39,    16,    51,
      78,   110,    73,    74,    49,   110,    51,    45,    52,    79,
      79,    47,    45,    47,     8,    11,    13,    14,    15,    16,
      17,    19,    22,    23,    45,    52,    53,    80,    82,    83,
      84,    86,    87,    88,    90,    91,    92,    93,    94,    95,
     110,    76,    47,    78,    50,    50,    45,    39,    40,    41,
      42,    43,    44,    45,   109,    39,    40,    45,    50,    56,
      58,    61,    62,    63,    67,    68,    88,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     110,    16,   110,    50,    37,    38,    48,    50,    54,    53,
      81,    46,    53,    82,    46,    46,    46,    46,    46,    46,
      46,    45,    85,    78,    96,    96,    48,    96,   106,   106,
     106,   106,   106,   106,   106,    36,    56,    35,    57,    58,
      33,    34,    31,    32,    59,    60,    61,    62,    63,    64,
      65,    66,    85,   110,    85,    45,    86,    39,    39,    96,
      51,    89,    96,    96,    82,    31,    47,    51,    51,    96,
      51,    98,    97,    99,   100,   101,   102,   102,   103,   103,
     103,   103,   104,   104,   105,   105,   105,   106,    85,    48,
      55,    49,    51,    47,    53,    45,   109,    85,    80,    12,
      49,    55,    96,    96,    37,    38,    54,    89,    47,    47,
      10,    80,    97,    49,    55,    39,    39,    96,    85,    85,
      80,    86,    51,    80
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    69,    71,    70,    72,    73,    72,    74,    72,    72,
      75,    75,    76,    76,    76,    76,    77,    77,    78,    78,
      78,    78,    79,    79,    80,    81,    80,    82,    82,    83,
      83,    83,    83,    83,    83,    83,    83,    84,    84,    84,
      84,    85,    85,    85,    85,    85,    85,    86,    86,    87,
      87,    87,    88,    88,    89,    89,    90,    90,    90,    90,
      91,    91,    91,    92,    92,    93,    94,    95,    95,    95,
      96,    96,    97,    97,    98,    98,    99,    99,   100,   100,
     101,   101,   101,   102,   102,   102,   102,   102,   103,   103,
     103,   104,   104,   104,   104,   105,   105,   106,   106,   106,
     106,   106,   106,   106,   106,   107,   107,   108,   108,   108,
     108,   108,   109,   109,   109,   109,   109,   109,   110,   110,
     110,   110,   110
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     0,     6,     0,     7,     0,
       4,     3,     3,     6,     1,     4,     2,     3,     4,     5,
       2,     3,     2,     3,     2,     0,     4,     2,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     3,     3,     4,
       2,     3,     1,     5,     5,     3,     3,     3,     6,     2,
       2,     2,     3,     4,     3,     1,     3,     6,     3,     6,
       1,     1,     1,     5,     7,     9,     6,     2,     1,     1,
       5,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     1,     3,     1,     2,     2,     2,
       2,     2,     2,     2,     1,     3,     1,     1,     1,     1,
       1,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 115 "parser.y"
    { semantic_init(); }
#line 1541 "parser.tab.c"
    break;

  case 3:
#line 115 "parser.y"
                              { arvore = (yyvsp[0].node); }
#line 1547 "parser.tab.c"
    break;

  case 4:
#line 120 "parser.y"
                     { (yyval.node) = (yyvsp[-1].node); }
#line 1553 "parser.tab.c"
    break;

  case 5:
#line 121 "parser.y"
                                               { 
        ident_fun_declaration((yyvsp[-1].valor_lexico.string), (yyvsp[-2].dt_type), (yyvsp[0].node));
    }
#line 1561 "parser.tab.c"
    break;

  case 6:
#line 123 "parser.y"
                    { 
        node *fun = create_node_function((yyvsp[-3].valor_lexico.string), (yyvsp[0].node)); 
        if ((yyvsp[-5].node) == NULL) {
          (yyval.node) = fun;
        } else {
          (yyval.node) = add_child((yyvsp[-5].node), fun);
        }
    }
#line 1574 "parser.tab.c"
    break;

  case 7:
#line 131 "parser.y"
                                                            { 
        ident_fun_declaration((yyvsp[-1].valor_lexico.string), (yyvsp[-2].dt_type), (yyvsp[0].node));
    }
#line 1582 "parser.tab.c"
    break;

  case 8:
#line 133 "parser.y"
                    { 
        node *fun = create_node_function((yyvsp[-3].valor_lexico.string), (yyvsp[0].node)); 
        if ((yyvsp[-6].node) == NULL) {
          (yyval.node) = fun;
        } else {
          (yyval.node) = add_child((yyvsp[-6].node), fun);
        }
    }
#line 1595 "parser.tab.c"
    break;

  case 9:
#line 141 "parser.y"
    { (yyval.node) = NULL; }
#line 1601 "parser.tab.c"
    break;

  case 10:
#line 145 "parser.y"
                                           { ident_var_array_global_decl_list((yyvsp[-2].dt_type), 1, (yyvsp[-1].node)); }
#line 1607 "parser.tab.c"
    break;

  case 11:
#line 146 "parser.y"
                              { ident_var_array_global_decl_list((yyvsp[-2].dt_type), 0, (yyvsp[-1].node)); }
#line 1613 "parser.tab.c"
    break;

  case 12:
#line 149 "parser.y"
                                          {
        node *id_node = create_leaf_id((yyvsp[-2].valor_lexico.string)); 
        (yyval.node) = add_child(id_node, (yyvsp[0].node));
    }
#line 1622 "parser.tab.c"
    break;

  case 13:
#line 153 "parser.y"
                                                             {
        node *array_node = create_node_array_decl((yyvsp[-5].valor_lexico.string), (yyvsp[-3].valor_lexico.integer));
        (yyval.node) = add_child(array_node, (yyvsp[0].node));
        literal_use(array_node->nodes[1]); 
    }
#line 1632 "parser.tab.c"
    break;

  case 14:
#line 158 "parser.y"
                     { (yyval.node) = create_leaf_id((yyvsp[0].valor_lexico.string)); }
#line 1638 "parser.tab.c"
    break;

  case 15:
#line 159 "parser.y"
                                        { 
        (yyval.node) = create_node_array_decl((yyvsp[-3].valor_lexico.string), (yyvsp[-1].valor_lexico.integer)); 
        literal_use((yyval.node)->nodes[1]); 
    }
#line 1647 "parser.tab.c"
    break;

  case 16:
#line 166 "parser.y"
            { (yyval.node) = NULL; }
#line 1653 "parser.tab.c"
    break;

  case 17:
#line 167 "parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 1659 "parser.tab.c"
    break;

  case 18:
#line 170 "parser.y"
                                                   { 
        node *id_node = create_leaf_type((yyvsp[-2].valor_lexico.string), (yyvsp[-3].dt_type)); 
        (yyval.node) = add_child(id_node, (yyvsp[0].node));
    }
#line 1668 "parser.tab.c"
    break;

  case 19:
#line 174 "parser.y"
                                                               { 
        node *id_node = create_leaf_type((yyvsp[-2].valor_lexico.string), (yyvsp[-3].dt_type)); 
        (yyval.node) = add_child(id_node, (yyvsp[0].node));
    }
#line 1677 "parser.tab.c"
    break;

  case 20:
#line 178 "parser.y"
                          { (yyval.node) = create_leaf_type((yyvsp[0].valor_lexico.string), (yyvsp[-1].dt_type)); }
#line 1683 "parser.tab.c"
    break;

  case 21:
#line 179 "parser.y"
                                      { (yyval.node) = create_leaf_type((yyvsp[0].valor_lexico.string), (yyvsp[-1].dt_type)); }
#line 1689 "parser.tab.c"
    break;

  case 22:
#line 182 "parser.y"
            { (yyval.node) = NULL; }
#line 1695 "parser.tab.c"
    break;

  case 23:
#line 183 "parser.y"
                           { 
        (yyval.node) = (yyvsp[-1].node);
        exit_scope();
  }
#line 1704 "parser.tab.c"
    break;

  case 24:
#line 190 "parser.y"
            { (yyval.node) = NULL; }
#line 1710 "parser.tab.c"
    break;

  case 25:
#line 191 "parser.y"
        { enter_scope("local"); }
#line 1716 "parser.tab.c"
    break;

  case 26:
#line 191 "parser.y"
                                                     { 
        (yyval.node) = (yyvsp[-1].node);
        exit_scope();
  }
#line 1725 "parser.tab.c"
    break;

  case 27:
#line 197 "parser.y"
                            { (yyval.node) = asp_stmt_list((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1731 "parser.tab.c"
    break;

  case 37:
#line 213 "parser.y"
                                      { 
        ident_var_array_local_decl_list((yyvsp[-1].dt_type), 1, 0, (yyvsp[0].node));
        (yyval.node) = remove_uninit_decl_var((yyvsp[0].node)); 
        /* $$->code = generate_var_init($2, $$); */
    }
#line 1741 "parser.tab.c"
    break;

  case 38:
#line 218 "parser.y"
                                     { 
        ident_var_array_local_decl_list((yyvsp[-1].dt_type), 0, 1, (yyvsp[0].node));
        (yyval.node) = remove_uninit_decl_var((yyvsp[0].node)); 
    }
#line 1750 "parser.tab.c"
    break;

  case 39:
#line 222 "parser.y"
                                                  { 
        ident_var_array_local_decl_list((yyvsp[-1].dt_type), 1, 1, (yyvsp[0].node));
        (yyval.node) = remove_uninit_decl_var((yyvsp[0].node));
    }
#line 1759 "parser.tab.c"
    break;

  case 40:
#line 226 "parser.y"
                         { 
        ident_var_array_local_decl_list((yyvsp[-1].dt_type), 0, 0, (yyvsp[0].node));
        (yyval.node) = remove_uninit_decl_var((yyvsp[0].node)); 
    }
#line 1768 "parser.tab.c"
    break;

  case 41:
#line 232 "parser.y"
                                       { 
        node *id_node = create_leaf_decl_var((yyvsp[-2].valor_lexico.string)); 
        (yyval.node) = add_child(id_node, (yyvsp[0].node));
    }
#line 1777 "parser.tab.c"
    break;

  case 42:
#line 236 "parser.y"
                     { (yyval.node) = create_leaf_decl_var((yyvsp[0].valor_lexico.string));  }
#line 1783 "parser.tab.c"
    break;

  case 43:
#line 237 "parser.y"
                                                          { 
        free((yyvsp[-3].valor_lexico.string));
        node *id_node = create_leaf_id((yyvsp[-4].valor_lexico.string)); 
        if ((yyvsp[0].node) == NULL) {
            (yyval.node) = create_node("<=", DECL_VAR_INIT_T, 2, id_node, (yyvsp[-2].node)); 
        } else {
            (yyval.node) = create_node("<=", DECL_VAR_INIT_T, 3, id_node, (yyvsp[-2].node), (yyvsp[0].node)); 
        }
    }
#line 1797 "parser.tab.c"
    break;

  case 44:
#line 246 "parser.y"
                                                                   { 
        free((yyvsp[-3].valor_lexico.string));
        node *dest_node = create_leaf_id((yyvsp[-4].valor_lexico.string)); 
        node *source_node = create_leaf_id((yyvsp[-2].valor_lexico.string)); 
        if ((yyvsp[0].node) == NULL) {
            (yyval.node) = create_node("<=", DECL_VAR_INIT_T, 2, dest_node, source_node); 
        } else {
            (yyval.node) = create_node("<=", DECL_VAR_INIT_T, 3, dest_node, source_node, (yyvsp[0].node)); 
        }
    }
#line 1812 "parser.tab.c"
    break;

  case 45:
#line 256 "parser.y"
                                      { 
        free((yyvsp[-1].valor_lexico.string));
        node *id_node = create_leaf_id((yyvsp[-2].valor_lexico.string)); 
        (yyval.node) = create_node("<=", DECL_VAR_INIT_T, 2, id_node, (yyvsp[0].node)); 
    }
#line 1822 "parser.tab.c"
    break;

  case 46:
#line 261 "parser.y"
                                               { 
        free((yyvsp[-1].valor_lexico.string));
        node *dest_node = create_leaf_id((yyvsp[-2].valor_lexico.string)); 
        node *source_node = create_leaf_id((yyvsp[0].valor_lexico.string)); 
        (yyval.node) = create_node("<=", DECL_VAR_INIT_T, 2, dest_node, source_node);  
    }
#line 1833 "parser.tab.c"
    break;

  case 47:
#line 270 "parser.y"
                                    { 
        node *id_node = create_leaf_id((yyvsp[-2].valor_lexico.string)); 
        (yyval.node) = create_node("=", STMT_T, 2, id_node, (yyvsp[0].node)); 
        ident_var_set((yyvsp[-2].valor_lexico.string), (yyvsp[0].node));
    }
#line 1843 "parser.tab.c"
    break;

  case 48:
#line 275 "parser.y"
                                                       { 
        node *id_node = create_leaf_id((yyvsp[-5].valor_lexico.string)); 
        node *index_node = create_node("[]", ARRAY_T, 2, id_node, (yyvsp[-3].node));
        (yyval.node) = create_node("=", STMT_T, 2, index_node, (yyvsp[0].node)); 
        ident_vector_set((yyvsp[-5].valor_lexico.string), (yyvsp[-3].node), (yyvsp[0].node));
    }
#line 1854 "parser.tab.c"
    break;

  case 49:
#line 284 "parser.y"
                                 { 
        node *id_node = create_leaf_id((yyvsp[0].valor_lexico.string));
        (yyval.node) = create_node("input", STMT_T, 1, id_node); 
        ident_var_use((yyvsp[0].valor_lexico.string));
        verify_input_use(id_node);
    }
#line 1865 "parser.tab.c"
    break;

  case 50:
#line 290 "parser.y"
                                  { 
        node *id_node = create_leaf_id((yyvsp[0].valor_lexico.string));
        (yyval.node) = create_node("output", STMT_T, 1, id_node); 
        ident_var_use((yyvsp[0].valor_lexico.string));
        verify_output_use(id_node);
    }
#line 1876 "parser.tab.c"
    break;

  case 51:
#line 296 "parser.y"
                         { 
        (yyval.node) = create_node("output", STMT_T, 1, (yyvsp[0].node));
         verify_output_use((yyvsp[0].node)); 
    }
#line 1885 "parser.tab.c"
    break;

  case 52:
#line 303 "parser.y"
                             { (yyval.node) = create_leaf_fun_call((yyvsp[-2].valor_lexico.string), NULL); }
#line 1891 "parser.tab.c"
    break;

  case 53:
#line 304 "parser.y"
                                                { 
        (yyval.node) = create_leaf_fun_call((yyvsp[-3].valor_lexico.string), (yyvsp[-1].node)); 
        ident_fun_use((yyvsp[-3].valor_lexico.string), (yyvsp[-1].node));
    }
#line 1900 "parser.tab.c"
    break;

  case 54:
#line 310 "parser.y"
                                      { (yyval.node) = add_child((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1906 "parser.tab.c"
    break;

  case 55:
#line 311 "parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 1912 "parser.tab.c"
    break;

  case 56:
#line 315 "parser.y"
                                         {
        node *id_node = create_leaf_id((yyvsp[-2].valor_lexico.string));
        node *offset = create_leaf_int((yyvsp[0].valor_lexico.integer));
        (yyval.node) = create_node(">>", STMT_T, 2, id_node, offset); 
        ident_var_use((yyvsp[-2].valor_lexico.string));
        verify_shift((yyvsp[0].valor_lexico.integer));
        literal_use(offset);
        free((yyvsp[-1].valor_lexico.string));
    }
#line 1926 "parser.tab.c"
    break;

  case 57:
#line 324 "parser.y"
                                                            {
        node *id_node = create_leaf_id((yyvsp[-5].valor_lexico.string)); 
        node *index_node = create_node("[]", ARRAY_T, 2, id_node, (yyvsp[-3].node));
        node *offset = create_leaf_int((yyvsp[0].valor_lexico.integer));
        (yyval.node) = create_node(">>", STMT_T, 2, index_node, offset); 
        verify_shift((yyvsp[0].valor_lexico.integer));
        ident_vector_use((yyvsp[-5].valor_lexico.string), (yyvsp[-3].node));
        literal_use(offset);
        free((yyvsp[-1].valor_lexico.string));
  }
#line 1941 "parser.tab.c"
    break;

  case 58:
#line 334 "parser.y"
                                         {
        node *id_node = create_leaf_id((yyvsp[-2].valor_lexico.string));
        node *offset = create_leaf_int((yyvsp[0].valor_lexico.integer));
        (yyval.node) = create_node("<<", STMT_T, 2, id_node, offset); 
        ident_var_use((yyvsp[-2].valor_lexico.string));
        verify_shift((yyvsp[0].valor_lexico.integer));
        literal_use(offset);
        free((yyvsp[-1].valor_lexico.string));
    }
#line 1955 "parser.tab.c"
    break;

  case 59:
#line 343 "parser.y"
                                                            {
        node *id_node = create_leaf_id((yyvsp[-5].valor_lexico.string)); 
        node *index_node = create_node("[]", ARRAY_T, 2, id_node, (yyvsp[-3].node));
        node *offset = create_leaf_int((yyvsp[0].valor_lexico.integer));
        (yyval.node) = create_node("<<", STMT_T, 2, index_node, offset); 
        verify_shift((yyvsp[0].valor_lexico.integer));
        ident_vector_use((yyvsp[-5].valor_lexico.string), (yyvsp[-3].node));
        literal_use(offset); 
        free((yyvsp[-1].valor_lexico.string));
  }
#line 1970 "parser.tab.c"
    break;

  case 63:
#line 362 "parser.y"
                                                {
        (yyval.node) = create_node("if", STMT_T, 2, (yyvsp[-2].node), (yyvsp[0].node)); 
    }
#line 1978 "parser.tab.c"
    break;

  case 64:
#line 365 "parser.y"
                                                                           {
        (yyval.node) = create_node("if", STMT_T, 3, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); 
    }
#line 1986 "parser.tab.c"
    break;

  case 65:
#line 370 "parser.y"
                                                                               {
        (yyval.node) = create_node("for", STMT_T, 4, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); 
    }
#line 1994 "parser.tab.c"
    break;

  case 66:
#line 375 "parser.y"
                                                            {
        (yyval.node) = create_node("while", STMT_T, 2, (yyvsp[-3].node), (yyvsp[0].node)); 
    }
#line 2002 "parser.tab.c"
    break;

  case 67:
#line 380 "parser.y"
                            { 
        (yyval.node) = create_node("return", STMT_T, 1, (yyvsp[0].node)); 
        verify_return((yyvsp[0].node));
    }
#line 2011 "parser.tab.c"
    break;

  case 68:
#line 384 "parser.y"
                { (yyval.node) = create_node("break", STMT_T, 0); }
#line 2017 "parser.tab.c"
    break;

  case 69:
#line 385 "parser.y"
                   { (yyval.node) = create_node("continue", STMT_T, 0); }
#line 2023 "parser.tab.c"
    break;

  case 70:
#line 392 "parser.y"
                                                   { 
        (yyval.node) = create_node_ternary_ope("?:", (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); 
    }
#line 2031 "parser.tab.c"
    break;

  case 72:
#line 398 "parser.y"
                                      { 
        (yyval.node) = create_node_binary_ope("||", (yyvsp[-2].node), (yyvsp[0].node)); 
        free((yyvsp[-1].valor_lexico.string));
    }
#line 2040 "parser.tab.c"
    break;

  case 74:
#line 405 "parser.y"
                                      { 
        (yyval.node) = create_node_binary_ope("&&", (yyvsp[-2].node), (yyvsp[0].node)); 
        free((yyvsp[-1].valor_lexico.string)); 
    }
#line 2049 "parser.tab.c"
    break;

  case 76:
#line 412 "parser.y"
                                { 
        (yyval.node) = create_node_binary_ope("|", (yyvsp[-2].node), (yyvsp[0].node)); 
        (yyval.node)->code = generate_code("or", (yyvsp[-2].node)->code, (yyvsp[0].node)->code);
    }
#line 2058 "parser.tab.c"
    break;

  case 78:
#line 419 "parser.y"
                                { 
        (yyval.node) = create_node_binary_ope("&", (yyvsp[-2].node), (yyvsp[0].node)); 
        (yyval.node)->code = generate_code("and", (yyvsp[-2].node)->code, (yyvsp[0].node)->code);
    }
#line 2067 "parser.tab.c"
    break;

  case 80:
#line 426 "parser.y"
                                     { 
        (yyval.node) = create_node_binary_ope("==", (yyvsp[-2].node), (yyvsp[0].node)); 
        (yyval.node)->code = generate_code("cmp_EQ", (yyvsp[-2].node)->code, (yyvsp[0].node)->code);
        free((yyvsp[-1].valor_lexico.string));
    }
#line 2077 "parser.tab.c"
    break;

  case 81:
#line 431 "parser.y"
                                     { 
        (yyval.node) = create_node_binary_ope("!=", (yyvsp[-2].node), (yyvsp[0].node)); 
        (yyval.node)->code = generate_code("cmp_NE", (yyvsp[-2].node)->code, (yyvsp[0].node)->code);
        free((yyvsp[-1].valor_lexico.string)); 
    }
#line 2087 "parser.tab.c"
    break;

  case 83:
#line 439 "parser.y"
                                { 
        (yyval.node) = create_node_binary_ope("<", (yyvsp[-2].node), (yyvsp[0].node)); 
        (yyval.node)->code = generate_code("cmp_LT", (yyvsp[-2].node)->code, (yyvsp[0].node)->code);
    }
#line 2096 "parser.tab.c"
    break;

  case 84:
#line 443 "parser.y"
                                { 
        (yyval.node) = create_node_binary_ope(">", (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->code = generate_code("cmp_GT", (yyvsp[-2].node)->code, (yyvsp[0].node)->code); 
    }
#line 2105 "parser.tab.c"
    break;

  case 85:
#line 447 "parser.y"
                                     { 
        (yyval.node) = create_node_binary_ope("<=", (yyvsp[-2].node), (yyvsp[0].node)); 
        (yyval.node)->code = generate_code("cmp_LE", (yyvsp[-2].node)->code, (yyvsp[0].node)->code);
        free((yyvsp[-1].valor_lexico.string));
    }
#line 2115 "parser.tab.c"
    break;

  case 86:
#line 452 "parser.y"
                                     { 
        (yyval.node) = create_node_binary_ope(">=", (yyvsp[-2].node), (yyvsp[0].node)); 
        (yyval.node)->code = generate_code("cmp_GE", (yyvsp[-2].node)->code, (yyvsp[0].node)->code);
        free((yyvsp[-1].valor_lexico.string));
    }
#line 2125 "parser.tab.c"
    break;

  case 88:
#line 460 "parser.y"
                                { 
        (yyval.node) = create_node_binary_ope("+", (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->code = generate_code("add", (yyvsp[-2].node)->code, (yyvsp[0].node)->code);
    }
#line 2134 "parser.tab.c"
    break;

  case 89:
#line 464 "parser.y"
                                { 
        (yyval.node) = create_node_binary_ope("-", (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->code = generate_code("sub", (yyvsp[-2].node)->code, (yyvsp[0].node)->code);
    }
#line 2143 "parser.tab.c"
    break;

  case 91:
#line 471 "parser.y"
                                { 
        (yyval.node) = create_node_binary_ope("*", (yyvsp[-2].node), (yyvsp[0].node)); 
        (yyval.node)->code = generate_code("mult", (yyvsp[-2].node)->code, (yyvsp[0].node)->code);
    }
#line 2152 "parser.tab.c"
    break;

  case 92:
#line 475 "parser.y"
                                { 
        (yyval.node) = create_node_binary_ope("/", (yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node)->code = generate_code("div", (yyvsp[-2].node)->code, (yyvsp[0].node)->code);
    }
#line 2161 "parser.tab.c"
    break;

  case 93:
#line 479 "parser.y"
                                { 
        (yyval.node) = create_node_binary_ope("%", (yyvsp[-2].node), (yyvsp[0].node)); 
    }
#line 2169 "parser.tab.c"
    break;

  case 95:
#line 485 "parser.y"
                                { 
        (yyval.node) = create_node_binary_ope("^", (yyvsp[-2].node), (yyvsp[0].node)); 
    }
#line 2177 "parser.tab.c"
    break;

  case 97:
#line 491 "parser.y"
                    { (yyval.node) = create_node_unary_ope("+", (yyvsp[0].node)); }
#line 2183 "parser.tab.c"
    break;

  case 98:
#line 492 "parser.y"
                    { (yyval.node) = create_node_unary_ope("-", (yyvsp[0].node)); }
#line 2189 "parser.tab.c"
    break;

  case 99:
#line 493 "parser.y"
                    { (yyval.node) = create_node_unary_ope("?", (yyvsp[0].node)); }
#line 2195 "parser.tab.c"
    break;

  case 100:
#line 494 "parser.y"
                    { (yyval.node) = create_node_unary_ope("!", (yyvsp[0].node)); }
#line 2201 "parser.tab.c"
    break;

  case 101:
#line 495 "parser.y"
                    { (yyval.node) = create_node_unary_ope("&", (yyvsp[0].node)); }
#line 2207 "parser.tab.c"
    break;

  case 102:
#line 496 "parser.y"
                    { (yyval.node) = create_node_unary_ope("*", (yyvsp[0].node)); }
#line 2213 "parser.tab.c"
    break;

  case 103:
#line 497 "parser.y"
                    { (yyval.node) = create_node_unary_ope("#", (yyvsp[0].node)); }
#line 2219 "parser.tab.c"
    break;

  case 105:
#line 501 "parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 2225 "parser.tab.c"
    break;

  case 107:
#line 506 "parser.y"
                     { 
        (yyval.node) = create_leaf_id((yyvsp[0].valor_lexico.string)); 
        ident_var_use((yyvsp[0].valor_lexico.string));
        (yyval.node)->code = generate_var_load((yyvsp[0].valor_lexico.string));
    }
#line 2235 "parser.tab.c"
    break;

  case 108:
#line 511 "parser.y"
               { 
        (yyval.node) = create_leaf_int((yyvsp[0].valor_lexico.integer)); 
        literal_use((yyval.node)); 
        (yyval.node)->code = generate_literal_load((yyvsp[0].valor_lexico.integer));
    }
#line 2245 "parser.tab.c"
    break;

  case 109:
#line 516 "parser.y"
                 { 
        (yyval.node) = create_leaf_float((yyvsp[0].valor_lexico.real)); 
        literal_use((yyval.node)); 
    }
#line 2254 "parser.tab.c"
    break;

  case 111:
#line 521 "parser.y"
                                        { 
        (yyval.node) = create_node_id_array((yyvsp[-3].valor_lexico.string), (yyvsp[-1].node)); 
        ident_vector_use((yyvsp[-3].valor_lexico.string), (yyvsp[-1].node));
    }
#line 2263 "parser.tab.c"
    break;

  case 112:
#line 529 "parser.y"
               { 
        (yyval.node) = create_leaf_int((yyvsp[0].valor_lexico.integer)); 
        literal_use((yyval.node)); 
        (yyval.node)->code = generate_literal_load((yyvsp[0].valor_lexico.integer));
    }
#line 2273 "parser.tab.c"
    break;

  case 113:
#line 534 "parser.y"
                 { 
        (yyval.node) = create_leaf_float((yyvsp[0].valor_lexico.real)); 
        literal_use((yyval.node)); 
    }
#line 2282 "parser.tab.c"
    break;

  case 114:
#line 538 "parser.y"
                 { 
      (yyval.node) = create_leaf_bool((yyvsp[0].valor_lexico.boolean), "false"); 
      literal_use((yyval.node)); 
    }
#line 2291 "parser.tab.c"
    break;

  case 115:
#line 542 "parser.y"
                { 
        (yyval.node) = create_leaf_bool((yyvsp[0].valor_lexico.boolean), "true");
        literal_use((yyval.node)); 
    }
#line 2300 "parser.tab.c"
    break;

  case 116:
#line 546 "parser.y"
                { 
        (yyval.node) = create_leaf_char((yyvsp[0].valor_lexico.character)); 
        literal_use((yyval.node)); 
    }
#line 2309 "parser.tab.c"
    break;

  case 117:
#line 550 "parser.y"
                  { 
        (yyval.node) = create_leaf_string((yyvsp[0].valor_lexico.string)); 
        literal_use((yyval.node)); 
    }
#line 2318 "parser.tab.c"
    break;

  case 118:
#line 558 "parser.y"
              { (yyval.dt_type) = DT_INTEGER; }
#line 2324 "parser.tab.c"
    break;

  case 119:
#line 559 "parser.y"
                { (yyval.dt_type) = DT_FLOAT; }
#line 2330 "parser.tab.c"
    break;

  case 120:
#line 560 "parser.y"
               { (yyval.dt_type) = DT_BOOL; }
#line 2336 "parser.tab.c"
    break;

  case 121:
#line 561 "parser.y"
               { (yyval.dt_type) = DT_CHAR; }
#line 2342 "parser.tab.c"
    break;

  case 122:
#line 562 "parser.y"
                 { (yyval.dt_type) = DT_STRING; }
#line 2348 "parser.tab.c"
    break;


#line 2352 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 564 "parser.y"


// Função que é chamada pelo bison para imprimir algum 
// erro sintático da linguagem analisada
void yyerror(char const *s) {
  printf("ERROR:\n\tline: %d\n\tmessage: %s\n", get_line_number(), s);
}