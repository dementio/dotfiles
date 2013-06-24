/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "./lev_comp.y"

/*	SCCS Id: @(#)lev_yacc.c	3.4	2000/01/17	*/
/*	Copyright (c) 1989 by Jean-Christophe Collet */
/* NetHack may be freely redistributed.  See license for details. */

/*
 * This file contains the Level Compiler code
 * It may handle special mazes & special room-levels
 */

/* In case we're using bison in AIX.  This definition must be
 * placed before any other C-language construct in the file
 * excluding comments and preprocessor directives (thanks IBM
 * for this wonderful feature...).
 *
 * Note: some cpps barf on this 'undefined control' (#pragma).
 * Addition of the leading space seems to prevent barfage for now,
 * and AIX will still see the directive.
 */
#ifdef _AIX
 #pragma alloca		/* keep leading space! */
#endif

#include "hack.h"
#include "sp_lev.h"

#define ERR		(-1)
/* many types of things are put in chars for transference to NetHack.
 * since some systems will use signed chars, limit everybody to the
 * same number for portability.
 */
#define MAX_OF_TYPE	128

#define MAX_NESTED_IFS	20
#define MAX_SWITCH_CASES 20
#define MAX_SWITCH_BREAKS 20

#define New(type)		\
	(type *) memset((genericptr_t)alloc(sizeof(type)), 0, sizeof(type))
#define NewTab(type, size)	(type **) alloc(sizeof(type *) * size)
#define Free(ptr)		free((genericptr_t)ptr)

extern void FDECL(yyerror, (const char *));
extern void FDECL(yywarning, (const char *));
extern int NDECL(yylex);
int NDECL(yyparse);
 extern void FDECL(include_push, (const char *));
extern int NDECL(include_pop);

extern int FDECL(get_floor_type, (CHAR_P));
extern int FDECL(get_room_type, (char *));
extern int FDECL(get_trap_type, (char *));
extern int FDECL(get_monster_id, (char *,CHAR_P));
extern int FDECL(get_object_id, (char *,CHAR_P));
extern boolean FDECL(check_monster_char, (CHAR_P));
extern boolean FDECL(check_object_char, (CHAR_P));
extern char FDECL(what_map_char, (CHAR_P));
extern void FDECL(scan_map, (char *, sp_lev *));
extern void FDECL(add_opcode, (sp_lev *, int, genericptr_t));
extern genericptr_t FDECL(get_last_opcode_data1, (sp_lev *, int));
extern genericptr_t FDECL(get_last_opcode_data2, (sp_lev *, int,int));
extern boolean FDECL(check_subrooms, (sp_lev *));
extern boolean FDECL(write_level_file, (char *,sp_lev *));
extern struct opvar *FDECL(set_opvar_int, (struct opvar *, long));
extern struct opvar *FDECL(set_opvar_str, (struct opvar *, char *));
extern void VDECL(add_opvars, (sp_lev *, const char *, ...));

extern struct lc_funcdefs *FDECL(funcdef_new,(long,char *));
extern void FDECL(funcdef_free_all,(struct lc_funcdefs *));
extern struct lc_funcdefs *FDECL(funcdef_defined,(struct lc_funcdefs *,char *, int));

extern void FDECL(splev_add_from, (sp_lev *, sp_lev *));


struct coord {
	long x;
	long y;
};

sp_lev *splev = NULL;

static char olist[MAX_REGISTERS], mlist[MAX_REGISTERS];
static struct coord plist[MAX_REGISTERS];
static struct opvar *if_list[MAX_NESTED_IFS];

static short n_olist = 0, n_mlist = 0, n_plist = 0, n_if_list = 0;
static short on_olist = 0, on_mlist = 0, on_plist = 0;


unsigned int max_x_map, max_y_map;
int obj_containment = 0;

int in_switch_statement = 0;
static struct opvar *switch_check_jump = NULL;
static struct opvar *switch_default_case = NULL;
static struct opvar *switch_case_list[MAX_SWITCH_CASES];
static long switch_case_value[MAX_SWITCH_CASES];
int n_switch_case_list = 0;
static struct opvar *switch_break_list[MAX_SWITCH_BREAKS];
int n_switch_break_list = 0;



static struct lc_funcdefs *function_definitions = NULL;
int in_function_definition = 0;
sp_lev *function_splev_backup = NULL;

extern int fatal_error;
extern int line_number;
extern const char *fname;



/* Line 268 of yacc.c  */
#line 185 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CHAR = 258,
     INTEGER = 259,
     BOOLEAN = 260,
     PERCENT = 261,
     SPERCENT = 262,
     MAZE_GRID_ID = 263,
     SOLID_FILL_ID = 264,
     MINES_ID = 265,
     MESSAGE_ID = 266,
     LEVEL_ID = 267,
     LEV_INIT_ID = 268,
     GEOMETRY_ID = 269,
     NOMAP_ID = 270,
     OBJECT_ID = 271,
     COBJECT_ID = 272,
     MONSTER_ID = 273,
     TRAP_ID = 274,
     DOOR_ID = 275,
     DRAWBRIDGE_ID = 276,
     MAZEWALK_ID = 277,
     WALLIFY_ID = 278,
     REGION_ID = 279,
     FILLING = 280,
     RANDOM_OBJECTS_ID = 281,
     RANDOM_MONSTERS_ID = 282,
     RANDOM_PLACES_ID = 283,
     ALTAR_ID = 284,
     LADDER_ID = 285,
     STAIR_ID = 286,
     NON_DIGGABLE_ID = 287,
     NON_PASSWALL_ID = 288,
     ROOM_ID = 289,
     PORTAL_ID = 290,
     TELEPRT_ID = 291,
     BRANCH_ID = 292,
     LEV = 293,
     CHANCE_ID = 294,
     RANDLINE_ID = 295,
     CORRIDOR_ID = 296,
     GOLD_ID = 297,
     ENGRAVING_ID = 298,
     FOUNTAIN_ID = 299,
     POOL_ID = 300,
     SINK_ID = 301,
     NONE = 302,
     RAND_CORRIDOR_ID = 303,
     DOOR_STATE = 304,
     LIGHT_STATE = 305,
     CURSE_TYPE = 306,
     ENGRAVING_TYPE = 307,
     DIRECTION = 308,
     RANDOM_TYPE = 309,
     O_REGISTER = 310,
     M_REGISTER = 311,
     P_REGISTER = 312,
     A_REGISTER = 313,
     ALIGNMENT = 314,
     LEFT_OR_RIGHT = 315,
     CENTER = 316,
     TOP_OR_BOT = 317,
     ALTAR_TYPE = 318,
     UP_OR_DOWN = 319,
     SUBROOM_ID = 320,
     NAME_ID = 321,
     FLAGS_ID = 322,
     FLAG_TYPE = 323,
     MON_ATTITUDE = 324,
     MON_ALERTNESS = 325,
     MON_APPEARANCE = 326,
     ROOMDOOR_ID = 327,
     IF_ID = 328,
     ELSE_ID = 329,
     SPILL_ID = 330,
     TERRAIN_ID = 331,
     HORIZ_OR_VERT = 332,
     REPLACE_TERRAIN_ID = 333,
     EXIT_ID = 334,
     QUANTITY_ID = 335,
     BURIED_ID = 336,
     LOOP_ID = 337,
     SWITCH_ID = 338,
     CASE_ID = 339,
     BREAK_ID = 340,
     DEFAULT_ID = 341,
     ERODED_ID = 342,
     TRAPPED_ID = 343,
     RECHARGED_ID = 344,
     INVIS_ID = 345,
     GREASED_ID = 346,
     FEMALE_ID = 347,
     CANCELLED_ID = 348,
     REVIVED_ID = 349,
     AVENGE_ID = 350,
     FLEEING_ID = 351,
     BLINDED_ID = 352,
     PARALYZED_ID = 353,
     STUNNED_ID = 354,
     CONFUSED_ID = 355,
     SEENTRAPS_ID = 356,
     ALL_ID = 357,
     MON_GENERATION_ID = 358,
     GRAVE_ID = 359,
     FUNCTION_ID = 360,
     INCLUDE_ID = 361,
     SOUNDS_ID = 362,
     MSG_OUTPUT_TYPE = 363,
     STRING = 364,
     MAP_ID = 365,
     NQSTRING = 366
   };
#endif
/* Tokens.  */
#define CHAR 258
#define INTEGER 259
#define BOOLEAN 260
#define PERCENT 261
#define SPERCENT 262
#define MAZE_GRID_ID 263
#define SOLID_FILL_ID 264
#define MINES_ID 265
#define MESSAGE_ID 266
#define LEVEL_ID 267
#define LEV_INIT_ID 268
#define GEOMETRY_ID 269
#define NOMAP_ID 270
#define OBJECT_ID 271
#define COBJECT_ID 272
#define MONSTER_ID 273
#define TRAP_ID 274
#define DOOR_ID 275
#define DRAWBRIDGE_ID 276
#define MAZEWALK_ID 277
#define WALLIFY_ID 278
#define REGION_ID 279
#define FILLING 280
#define RANDOM_OBJECTS_ID 281
#define RANDOM_MONSTERS_ID 282
#define RANDOM_PLACES_ID 283
#define ALTAR_ID 284
#define LADDER_ID 285
#define STAIR_ID 286
#define NON_DIGGABLE_ID 287
#define NON_PASSWALL_ID 288
#define ROOM_ID 289
#define PORTAL_ID 290
#define TELEPRT_ID 291
#define BRANCH_ID 292
#define LEV 293
#define CHANCE_ID 294
#define RANDLINE_ID 295
#define CORRIDOR_ID 296
#define GOLD_ID 297
#define ENGRAVING_ID 298
#define FOUNTAIN_ID 299
#define POOL_ID 300
#define SINK_ID 301
#define NONE 302
#define RAND_CORRIDOR_ID 303
#define DOOR_STATE 304
#define LIGHT_STATE 305
#define CURSE_TYPE 306
#define ENGRAVING_TYPE 307
#define DIRECTION 308
#define RANDOM_TYPE 309
#define O_REGISTER 310
#define M_REGISTER 311
#define P_REGISTER 312
#define A_REGISTER 313
#define ALIGNMENT 314
#define LEFT_OR_RIGHT 315
#define CENTER 316
#define TOP_OR_BOT 317
#define ALTAR_TYPE 318
#define UP_OR_DOWN 319
#define SUBROOM_ID 320
#define NAME_ID 321
#define FLAGS_ID 322
#define FLAG_TYPE 323
#define MON_ATTITUDE 324
#define MON_ALERTNESS 325
#define MON_APPEARANCE 326
#define ROOMDOOR_ID 327
#define IF_ID 328
#define ELSE_ID 329
#define SPILL_ID 330
#define TERRAIN_ID 331
#define HORIZ_OR_VERT 332
#define REPLACE_TERRAIN_ID 333
#define EXIT_ID 334
#define QUANTITY_ID 335
#define BURIED_ID 336
#define LOOP_ID 337
#define SWITCH_ID 338
#define CASE_ID 339
#define BREAK_ID 340
#define DEFAULT_ID 341
#define ERODED_ID 342
#define TRAPPED_ID 343
#define RECHARGED_ID 344
#define INVIS_ID 345
#define GREASED_ID 346
#define FEMALE_ID 347
#define CANCELLED_ID 348
#define REVIVED_ID 349
#define AVENGE_ID 350
#define FLEEING_ID 351
#define BLINDED_ID 352
#define PARALYZED_ID 353
#define STUNNED_ID 354
#define CONFUSED_ID 355
#define SEENTRAPS_ID 356
#define ALL_ID 357
#define MON_GENERATION_ID 358
#define GRAVE_ID 359
#define FUNCTION_ID 360
#define INCLUDE_ID 361
#define SOUNDS_ID 362
#define MSG_OUTPUT_TYPE 363
#define STRING 364
#define MAP_ID 365
#define NQSTRING 366




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 115 "./lev_comp.y"

	long	i;
	char*	map;
	struct {
		long room;
		long wall;
		long door;
	} corpos;
    struct {
	long area;
	long x1;
	long y1;
	long x2;
	long y2;
    } lregn;
    struct {
	long x;
	long y;
    } crd;
    struct {
	long height;
	long width;
    } sze;



/* Line 293 of yacc.c  */
#line 470 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 482 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   683

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  121
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  145
/* YYNRULES -- Number of rules.  */
#define YYNRULES  296
/* YYNRULES -- Number of states.  */
#define YYNSTATES  693

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   366

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     111,   112,     2,     2,   109,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   110,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   113,     2,   114,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   115,   120,   116,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   117,   118,   119
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    12,    14,    16,    19,
      21,    24,    29,    33,    34,    41,    47,    64,    65,    68,
      70,    72,    73,    77,    81,    83,    84,    87,    89,    91,
      93,    95,    97,    99,   101,   103,   105,   107,   109,   111,
     113,   115,   117,   119,   121,   123,   125,   127,   129,   131,
     133,   135,   137,   139,   141,   143,   145,   147,   149,   151,
     153,   155,   157,   159,   161,   163,   165,   167,   169,   171,
     173,   175,   176,   185,   189,   191,   192,   194,   196,   197,
     206,   207,   210,   211,   217,   218,   223,   224,   227,   229,
     231,   232,   241,   242,   247,   251,   252,   261,   265,   266,
     273,   277,   278,   287,   289,   295,   301,   309,   314,   315,
     328,   329,   344,   345,   348,   354,   356,   362,   364,   370,
     372,   378,   380,   384,   388,   398,   404,   406,   408,   410,
     412,   414,   418,   420,   422,   424,   428,   434,   440,   442,
     444,   446,   448,   452,   456,   460,   462,   466,   468,   472,
     474,   475,   480,   486,   488,   492,   498,   504,   506,   510,
     516,   522,   527,   528,   537,   544,   545,   548,   551,   554,
     557,   560,   564,   567,   570,   573,   576,   579,   584,   589,
     594,   597,   600,   605,   607,   609,   613,   614,   617,   619,
     621,   626,   627,   636,   641,   642,   651,   656,   663,   664,
     667,   670,   673,   676,   681,   686,   689,   692,   697,   700,
     703,   708,   711,   714,   721,   729,   735,   744,   746,   750,
     756,   762,   770,   778,   785,   791,   792,   795,   799,   803,
     807,   819,   828,   841,   852,   863,   864,   867,   879,   883,
     887,   896,   904,   910,   916,   920,   926,   934,   936,   938,
     940,   942,   944,   946,   948,   950,   952,   954,   956,   958,
     960,   962,   963,   966,   971,   973,   975,   977,   979,   981,
     982,   985,   987,   989,   991,   993,   995,   997,   999,  1004,
    1009,  1014,  1019,  1021,  1023,  1025,  1027,  1029,  1031,  1032,
    1034,  1036,  1038,  1044,  1048,  1050,  1061
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     122,     0,    -1,   123,    -1,   123,   126,    -1,    -1,   124,
     123,    -1,   136,    -1,   125,    -1,   106,   117,    -1,   127,
      -1,   127,   126,    -1,   128,   132,   129,   134,    -1,    12,
     110,   258,    -1,    -1,    13,   110,     9,   109,     3,   247,
      -1,    13,   110,     8,   109,     3,    -1,    13,   110,    10,
     109,     3,   109,     3,   109,     5,   109,     5,   109,   248,
     109,   131,   130,    -1,    -1,   109,     3,    -1,     5,    -1,
      54,    -1,    -1,    67,   110,   133,    -1,    68,   109,   133,
      -1,    68,    -1,    -1,   135,   134,    -1,   156,    -1,   234,
      -1,   235,    -1,   193,    -1,   190,    -1,   221,    -1,   162,
      -1,   231,    -1,   176,    -1,   213,    -1,   237,    -1,   223,
      -1,   236,    -1,   142,    -1,   150,    -1,   152,    -1,   139,
      -1,   136,    -1,   138,    -1,   185,    -1,   216,    -1,   181,
      -1,   214,    -1,   196,    -1,   206,    -1,   232,    -1,   225,
      -1,   219,    -1,   161,    -1,   233,    -1,   167,    -1,   165,
      -1,   175,    -1,   174,    -1,   224,    -1,   227,    -1,   226,
      -1,   230,    -1,   228,    -1,   217,    -1,   218,    -1,   220,
      -1,   212,    -1,   215,    -1,    -1,   105,   119,   111,   112,
     137,   115,   134,   116,    -1,   119,   111,   112,    -1,    79,
      -1,    -1,     6,    -1,     6,    -1,    -1,    83,   113,     4,
     114,   143,   115,   144,   116,    -1,    -1,   145,   144,    -1,
      -1,    84,     4,   110,   146,   148,    -1,    -1,    86,   110,
     147,   148,    -1,    -1,   149,   148,    -1,    85,    -1,   135,
      -1,    -1,    82,   113,     4,   114,   151,   115,   134,   116,
      -1,    -1,    73,   141,   153,   154,    -1,   115,   134,   116,
      -1,    -1,   115,   134,   116,   155,    74,   115,   134,   116,
      -1,    11,   110,   117,    -1,    -1,    73,   113,   141,   114,
     158,   159,    -1,   115,   202,   116,    -1,    -1,   115,   202,
     116,   160,    74,   115,   202,   116,    -1,    48,    -1,    41,
     110,   163,   109,   163,    -1,    41,   110,   163,   109,     4,
      -1,   111,     4,   109,    53,   109,   180,   112,    -1,   243,
     140,   109,   248,    -1,    -1,    65,   110,   164,   109,   171,
     109,   173,   169,   166,   115,   134,   116,    -1,    -1,    34,
     110,   164,   109,   170,   109,   172,   109,   173,   169,   168,
     115,   134,   116,    -1,    -1,   109,     5,    -1,   111,     4,
     109,     4,   112,    -1,    54,    -1,   111,     4,   109,     4,
     112,    -1,    54,    -1,   111,   183,   109,   184,   112,    -1,
      54,    -1,   111,     4,   109,     4,   112,    -1,    54,    -1,
      66,   110,   258,    -1,    39,   110,     4,    -1,    72,   110,
     177,   109,   246,   109,   178,   109,   180,    -1,    20,   110,
     246,   109,   245,    -1,     5,    -1,    54,    -1,   179,    -1,
      54,    -1,    53,    -1,    53,   120,   179,    -1,     4,    -1,
      54,    -1,    15,    -1,   182,   169,   118,    -1,    14,   110,
     245,   169,   118,    -1,    14,   110,   183,   109,   184,    -1,
      60,    -1,    61,    -1,    62,    -1,    61,    -1,    26,   110,
     186,    -1,    28,   110,   188,    -1,    27,   110,   187,    -1,
     257,    -1,   257,   109,   186,    -1,   256,    -1,   256,   109,
     187,    -1,   255,    -1,    -1,   255,   189,   109,   188,    -1,
     107,   110,     4,   109,   191,    -1,   192,    -1,   192,   109,
     191,    -1,   111,   108,   109,   117,   112,    -1,   103,   110,
       7,   109,   194,    -1,   195,    -1,   195,   109,   194,    -1,
     111,     4,   109,   256,   112,    -1,   111,     4,   109,   258,
     112,    -1,    18,   260,   110,   198,    -1,    -1,    18,   260,
     110,   198,   197,   115,   202,   116,    -1,   238,   109,   240,
     109,   245,   199,    -1,    -1,   199,   200,    -1,   109,   258,
      -1,   109,    69,    -1,   109,    70,    -1,   109,   249,    -1,
     109,    71,   258,    -1,   109,    92,    -1,   109,    90,    -1,
     109,    93,    -1,   109,    94,    -1,   109,    95,    -1,   109,
      96,   110,     4,    -1,   109,    97,   110,     4,    -1,   109,
      98,   110,     4,    -1,   109,    99,    -1,   109,   100,    -1,
     109,   101,   110,   201,    -1,   117,    -1,   102,    -1,   117,
     120,   201,    -1,    -1,   203,   202,    -1,   204,    -1,   157,
      -1,    16,   260,   110,   208,    -1,    -1,    17,   260,   110,
     208,   205,   115,   202,   116,    -1,    16,   260,   110,   209,
      -1,    -1,    17,   260,   110,   209,   207,   115,   202,   116,
      -1,   239,   109,   241,   210,    -1,   239,   109,   241,   109,
     245,   210,    -1,    -1,   210,   211,    -1,   109,    51,    -1,
     109,   117,    -1,   109,     4,    -1,   109,    66,   110,   117,
      -1,   109,    80,   110,     4,    -1,   109,    81,    -1,   109,
      50,    -1,   109,    87,   110,     4,    -1,   109,    49,    -1,
     109,    88,    -1,   109,    89,   110,     4,    -1,   109,    90,
      -1,   109,    91,    -1,    19,   260,   110,   242,   109,   245,
      -1,    21,   110,   245,   109,    53,   109,   246,    -1,    22,
     110,   245,   109,    53,    -1,    22,   110,   245,   109,    53,
     109,     5,   130,    -1,    23,    -1,    23,   110,   264,    -1,
      30,   110,   245,   109,    64,    -1,    31,   110,   245,   109,
      64,    -1,    31,   110,   264,   109,   264,   109,    64,    -1,
      35,   110,   264,   109,   264,   109,   258,    -1,    36,   110,
     264,   109,   264,   222,    -1,    37,   110,   264,   109,   264,
      -1,    -1,   109,    64,    -1,    44,   110,   245,    -1,    46,
     110,   245,    -1,    45,   110,   245,    -1,    78,   110,   265,
     109,     3,   109,     3,   109,   248,   109,     7,    -1,    76,
     260,   110,   245,   109,     3,   109,   248,    -1,    76,   260,
     110,   245,   109,    77,   109,     4,   109,     3,   109,   248,
      -1,    76,   260,   110,   265,   109,    25,   109,     3,   109,
     248,    -1,    40,   110,   263,   109,     3,   109,   248,   109,
       4,   229,    -1,    -1,   109,     4,    -1,    75,   110,   245,
     109,     3,   109,    53,   109,     4,   109,   248,    -1,    32,
     110,   265,    -1,    33,   110,   265,    -1,    24,   110,   265,
     109,   248,   109,   243,   244,    -1,    29,   110,   245,   109,
     249,   109,   250,    -1,   104,   110,   245,   109,   258,    -1,
     104,   110,   245,   109,    54,    -1,   104,   110,   245,    -1,
      42,   110,   259,   109,   245,    -1,    43,   110,   245,   109,
     261,   109,   258,    -1,   256,    -1,    54,    -1,   253,    -1,
     257,    -1,    54,    -1,   252,    -1,   258,    -1,    54,    -1,
     258,    -1,    54,    -1,   258,    -1,    54,    -1,   258,    -1,
      54,    -1,    -1,   109,    25,    -1,   109,    25,   109,     5,
      -1,   262,    -1,   251,    -1,    54,    -1,    49,    -1,    54,
      -1,    -1,   109,   248,    -1,    50,    -1,    54,    -1,    59,
      -1,   254,    -1,    54,    -1,    63,    -1,    54,    -1,    57,
     113,     4,   114,    -1,    55,   113,     4,   114,    -1,    56,
     113,     4,   114,    -1,    58,   113,     4,   114,    -1,   262,
      -1,     3,    -1,     3,    -1,   117,    -1,     4,    -1,    54,
      -1,    -1,   141,    -1,    52,    -1,    54,    -1,   111,     4,
     109,     4,   112,    -1,   245,   109,   245,    -1,   265,    -1,
      38,   111,     4,   109,     4,   109,     4,   109,     4,   112,
      -1,   111,     4,   109,     4,   109,     4,   109,     4,   112,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   189,   189,   190,   193,   194,   197,   198,   202,   209,
     210,   213,   231,   252,   255,   264,   273,   299,   302,   309,
     310,   314,   317,   323,   327,   333,   334,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,   369,
     370,   371,   372,   373,   374,   375,   376,   377,   378,   379,
     380,   384,   383,   410,   436,   443,   446,   453,   462,   461,
     522,   523,   527,   526,   539,   538,   553,   554,   557,   568,
     574,   573,   607,   606,   631,   640,   639,   666,   677,   676,
     701,   710,   709,   738,   744,   751,   760,   768,   779,   778,
     790,   789,   802,   805,   811,   821,   827,   836,   842,   847,
     853,   858,   864,   871,   877,   886,   893,   894,   897,   898,
     901,   905,   911,   912,   915,   921,   927,   935,   941,   942,
     945,   946,   949,   962,   979,   993,  1000,  1009,  1016,  1025,
    1035,  1034,  1046,  1055,  1059,  1065,  1071,  1083,  1087,  1093,
    1100,  1110,  1123,  1122,  1140,  1156,  1162,  1170,  1175,  1180,
    1185,  1190,  1195,  1200,  1205,  1210,  1215,  1220,  1225,  1230,
    1235,  1240,  1245,  1252,  1259,  1263,  1277,  1279,  1282,  1283,
    1286,  1298,  1297,  1316,  1328,  1327,  1346,  1361,  1377,  1383,
    1391,  1396,  1408,  1413,  1418,  1423,  1428,  1433,  1438,  1449,
    1454,  1459,  1464,  1471,  1484,  1509,  1514,  1522,  1526,  1533,
    1539,  1545,  1555,  1564,  1579,  1589,  1592,  1598,  1604,  1610,
    1616,  1636,  1656,  1685,  1706,  1717,  1720,  1726,  1743,  1750,
    1757,  1780,  1787,  1792,  1797,  1804,  1810,  1817,  1818,  1822,
    1825,  1826,  1830,  1833,  1834,  1840,  1841,  1847,  1855,  1858,
    1868,  1872,  1875,  1879,  1885,  1886,  1887,  1893,  1894,  1898,
    1901,  1907,  1908,  1911,  1912,  1913,  1919,  1920,  1923,  1935,
    1947,  1959,  1968,  1974,  1985,  1997,  2000,  2001,  2005,  2009,
    2026,  2027,  2030,  2039,  2049,  2053,  2073
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR", "INTEGER", "BOOLEAN", "PERCENT",
  "SPERCENT", "MAZE_GRID_ID", "SOLID_FILL_ID", "MINES_ID", "MESSAGE_ID",
  "LEVEL_ID", "LEV_INIT_ID", "GEOMETRY_ID", "NOMAP_ID", "OBJECT_ID",
  "COBJECT_ID", "MONSTER_ID", "TRAP_ID", "DOOR_ID", "DRAWBRIDGE_ID",
  "MAZEWALK_ID", "WALLIFY_ID", "REGION_ID", "FILLING", "RANDOM_OBJECTS_ID",
  "RANDOM_MONSTERS_ID", "RANDOM_PLACES_ID", "ALTAR_ID", "LADDER_ID",
  "STAIR_ID", "NON_DIGGABLE_ID", "NON_PASSWALL_ID", "ROOM_ID", "PORTAL_ID",
  "TELEPRT_ID", "BRANCH_ID", "LEV", "CHANCE_ID", "RANDLINE_ID",
  "CORRIDOR_ID", "GOLD_ID", "ENGRAVING_ID", "FOUNTAIN_ID", "POOL_ID",
  "SINK_ID", "NONE", "RAND_CORRIDOR_ID", "DOOR_STATE", "LIGHT_STATE",
  "CURSE_TYPE", "ENGRAVING_TYPE", "DIRECTION", "RANDOM_TYPE", "O_REGISTER",
  "M_REGISTER", "P_REGISTER", "A_REGISTER", "ALIGNMENT", "LEFT_OR_RIGHT",
  "CENTER", "TOP_OR_BOT", "ALTAR_TYPE", "UP_OR_DOWN", "SUBROOM_ID",
  "NAME_ID", "FLAGS_ID", "FLAG_TYPE", "MON_ATTITUDE", "MON_ALERTNESS",
  "MON_APPEARANCE", "ROOMDOOR_ID", "IF_ID", "ELSE_ID", "SPILL_ID",
  "TERRAIN_ID", "HORIZ_OR_VERT", "REPLACE_TERRAIN_ID", "EXIT_ID",
  "QUANTITY_ID", "BURIED_ID", "LOOP_ID", "SWITCH_ID", "CASE_ID",
  "BREAK_ID", "DEFAULT_ID", "ERODED_ID", "TRAPPED_ID", "RECHARGED_ID",
  "INVIS_ID", "GREASED_ID", "FEMALE_ID", "CANCELLED_ID", "REVIVED_ID",
  "AVENGE_ID", "FLEEING_ID", "BLINDED_ID", "PARALYZED_ID", "STUNNED_ID",
  "CONFUSED_ID", "SEENTRAPS_ID", "ALL_ID", "MON_GENERATION_ID", "GRAVE_ID",
  "FUNCTION_ID", "INCLUDE_ID", "SOUNDS_ID", "MSG_OUTPUT_TYPE", "','",
  "':'", "'('", "')'", "'['", "']'", "'{'", "'}'", "STRING", "MAP_ID",
  "NQSTRING", "'|'", "$accept", "file", "header_stmts", "header_stmt",
  "include_def", "levels", "level", "level_def", "lev_init",
  "opt_fillchar", "walled", "flags", "flag_list", "levstatements",
  "levstatement", "function_define", "$@1", "function_call",
  "exitstatement", "opt_percent", "comparestmt", "switchstatement", "$@2",
  "switchcases", "switchcase", "$@3", "$@4", "breakstatements",
  "breakstatement", "loopstatement", "$@5", "ifstatement", "$@6",
  "if_ending", "$@7", "message", "cobj_ifstatement", "$@8",
  "cobj_if_ending", "$@9", "random_corridors", "corridor", "corr_spec",
  "room_begin", "subroom_def", "$@10", "room_def", "$@11", "roomfill",
  "room_pos", "subroom_pos", "room_align", "room_size", "room_name",
  "room_chance", "door_detail", "secret", "door_wall", "dir_list",
  "door_pos", "map_definition", "map_geometry", "h_justif", "v_justif",
  "init_reg", "object_list", "monster_list", "place_list", "$@12",
  "sounds_detail", "sounds_list", "lvl_sound_part", "mon_generation",
  "mon_gen_list", "mon_gen_part", "monster_detail", "@13", "monster_desc",
  "monster_infos", "monster_info", "seen_trap_mask", "cobj_statements",
  "cobj_statement", "cobj_detail", "@14", "object_detail", "@15",
  "cobj_desc", "object_desc", "object_infos", "object_info", "trap_detail",
  "drawbridge_detail", "mazewalk_detail", "wallify_detail",
  "ladder_detail", "stair_detail", "stair_region", "portal_region",
  "teleprt_region", "branch_region", "teleprt_detail", "fountain_detail",
  "sink_detail", "pool_detail", "replace_terrain_detail", "terrain_detail",
  "randline_detail", "opt_int", "spill_detail", "diggable_detail",
  "passwall_detail", "region_detail", "altar_detail", "grave_detail",
  "gold_detail", "engraving_detail", "monster_c", "object_c", "m_name",
  "o_name", "trap_name", "room_type", "prefilled", "coordinate",
  "door_state", "opt_lit_state", "light_state", "alignment", "altar_type",
  "p_register", "o_register", "m_register", "a_register", "place",
  "monster", "object", "string", "amount", "chance", "engraving_type",
  "coord", "lineends", "lev_region", "region", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,    44,
      58,    40,    41,    91,    93,   123,   125,   364,   365,   366,
     124
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   121,   122,   122,   123,   123,   124,   124,   125,   126,
     126,   127,   128,   129,   129,   129,   129,   130,   130,   131,
     131,   132,   132,   133,   133,   134,   134,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   137,   136,   138,   139,   140,   140,   141,   143,   142,
     144,   144,   146,   145,   147,   145,   148,   148,   149,   149,
     151,   150,   153,   152,   154,   155,   154,   156,   158,   157,
     159,   160,   159,   161,   162,   162,   163,   164,   166,   165,
     168,   167,   169,   169,   170,   170,   171,   171,   172,   172,
     173,   173,   174,   175,   176,   176,   177,   177,   178,   178,
     179,   179,   180,   180,   181,   181,   181,   182,   183,   183,
     184,   184,   185,   185,   185,   186,   186,   187,   187,   188,
     189,   188,   190,   191,   191,   192,   193,   194,   194,   195,
     195,   196,   197,   196,   198,   199,   199,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   201,   201,   201,   202,   202,   203,   203,
     204,   205,   204,   206,   207,   206,   208,   209,   210,   210,
     211,   211,   211,   211,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   212,   213,   214,   214,   215,   215,   216,
     217,   218,   219,   220,   221,   222,   222,   223,   224,   225,
     226,   227,   227,   227,   228,   229,   229,   230,   231,   232,
     233,   234,   235,   235,   235,   236,   237,   238,   238,   238,
     239,   239,   239,   240,   240,   241,   241,   242,   242,   243,
     243,   244,   244,   244,   245,   245,   245,   246,   246,   247,
     247,   248,   248,   249,   249,   249,   250,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   259,   260,   260,
     261,   261,   262,   263,   264,   264,   265
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     2,     1,
       2,     4,     3,     0,     6,     5,    16,     0,     2,     1,
       1,     0,     3,     3,     1,     0,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     8,     3,     1,     0,     1,     1,     0,     8,
       0,     2,     0,     5,     0,     4,     0,     2,     1,     1,
       0,     8,     0,     4,     3,     0,     8,     3,     0,     6,
       3,     0,     8,     1,     5,     5,     7,     4,     0,    12,
       0,    14,     0,     2,     5,     1,     5,     1,     5,     1,
       5,     1,     3,     3,     9,     5,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     5,     5,     1,     1,
       1,     1,     3,     3,     3,     1,     3,     1,     3,     1,
       0,     4,     5,     1,     3,     5,     5,     1,     3,     5,
       5,     4,     0,     8,     6,     0,     2,     2,     2,     2,
       2,     3,     2,     2,     2,     2,     2,     4,     4,     4,
       2,     2,     4,     1,     1,     3,     0,     2,     1,     1,
       4,     0,     8,     4,     0,     8,     4,     6,     0,     2,
       2,     2,     2,     4,     4,     2,     2,     4,     2,     2,
       4,     2,     2,     6,     7,     5,     8,     1,     3,     5,
       5,     7,     7,     6,     5,     0,     2,     3,     3,     3,
      11,     8,    12,    10,    10,     0,     2,    11,     3,     3,
       8,     7,     5,     5,     3,     5,     7,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     2,     4,     1,     1,     1,     1,     1,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     4,     4,
       4,     4,     1,     1,     1,     1,     1,     1,     0,     1,
       1,     1,     5,     3,     1,    10,     9
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     0,     0,     2,     4,     7,     6,     0,     8,
       1,     0,     3,     9,    21,     5,     0,     0,    10,     0,
      13,    71,   285,    12,     0,     0,    25,     0,    24,    22,
       0,     0,     0,   134,   288,   288,   288,   288,     0,     0,
       0,   217,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   103,     0,     0,     0,     0,     0,   288,
       0,    74,     0,     0,     0,     0,     0,     0,    11,    25,
      44,    45,    43,    40,    41,    42,    27,    55,    33,    58,
      57,    60,    59,    35,    48,   112,    46,    31,    30,    50,
      51,    69,    36,    49,    70,    47,    66,    67,    54,    68,
      32,    38,    61,    53,    63,    62,    65,    64,    34,    52,
      56,    28,    29,    39,    37,    25,     0,     0,     0,     0,
       0,     0,    77,   289,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    92,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    26,     0,     0,     0,
      23,     0,     0,     0,    97,   266,     0,   138,   139,     0,
       0,   112,   265,   264,     0,     0,     0,     0,   267,   268,
       0,     0,     0,     0,     0,   218,   294,     0,   284,   142,
     145,   283,   144,   147,   143,   149,   282,     0,     0,     0,
       0,     0,   238,   239,   260,     0,    75,   259,     0,     0,
       0,   123,     0,     0,     0,     0,   286,   287,     0,     0,
     227,   229,   228,     0,   122,   126,   127,     0,     0,     0,
       0,     0,     0,     0,     0,   244,     0,    73,   113,   135,
      72,    15,   269,     0,     0,     0,     0,     0,   251,     0,
     193,     0,   252,   250,   194,   248,     0,   161,     0,   249,
     247,   258,     0,   257,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    76,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    25,    93,     0,     0,     0,     0,    90,    78,
       0,     0,     0,     0,    14,     0,     0,     0,   141,   140,
     137,   136,     0,     0,     0,     0,     0,     0,     0,   125,
       0,   215,     0,     0,   271,   272,     0,   146,   148,     0,
     275,     0,   273,     0,   274,   219,     0,   220,     0,   115,
       0,     0,     0,     0,   225,   224,   293,     0,     0,   105,
     104,   245,   290,   291,     0,   117,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   156,   157,   243,
     242,     0,   152,   153,   270,     0,   278,     0,     0,   256,
       0,   255,   186,     0,   186,   254,     0,   253,   213,     0,
       0,     0,     0,     0,   151,     0,     0,     0,     0,     0,
       0,   107,     0,     0,   223,     0,     0,     0,     0,     0,
       0,    94,     0,     0,     0,     0,     0,    25,    80,     0,
       0,     0,     0,     0,   292,   279,     0,   288,   288,     0,
     189,     0,   186,   188,   280,     0,     0,   214,    17,     0,
       0,   261,     0,   277,   276,   241,   221,     0,   119,     0,
       0,   222,   226,     0,     0,   246,     0,   121,     0,   112,
     130,   129,     0,   128,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    80,     0,   158,     0,   154,     0,
     198,     0,     0,     0,   195,   187,   163,   165,     0,   216,
       0,     0,     0,   240,   281,     0,     0,     0,     0,   132,
     133,     0,     0,     0,   108,     0,     0,     0,     0,   231,
       0,     0,     0,    91,     0,    84,    79,    81,     0,     0,
       0,     0,   197,     0,     0,     0,   164,    18,     0,     0,
     262,   114,     0,   112,   235,   106,   116,     0,     0,   131,
     124,    25,     0,     0,     0,     0,    82,    86,   159,   160,
     155,     0,     0,   199,   190,     0,   191,    98,     0,   166,
       0,     0,     0,     0,   110,     0,   234,     0,    25,     0,
       0,     0,   233,     0,    86,    88,    89,    85,    86,     0,
     202,   208,   206,   200,     0,     0,   205,     0,   209,     0,
     211,   212,   201,     0,     0,     0,   168,   169,     0,   173,
     172,   174,   175,   176,     0,     0,     0,   180,   181,     0,
     170,   167,     0,   296,   263,   118,     0,   236,   120,     0,
      96,   237,     0,   230,    83,    87,     0,     0,     0,     0,
       0,   198,   186,   186,    99,   171,     0,     0,     0,     0,
     295,    25,   109,   232,     0,   203,   204,   207,   210,   196,
       0,     0,   177,   178,   179,   184,   183,   182,     0,    19,
      20,    17,   192,   100,     0,   111,    16,     0,   185,     0,
     186,     0,   102
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    12,    13,    14,    26,   509,
     681,    20,    29,    78,    79,    80,    27,    81,    82,   300,
     133,    83,   385,   493,   494,   594,   567,   597,   598,    84,
     384,    85,   248,   313,   484,    86,   450,   615,   654,   687,
      87,    88,   235,   225,    89,   558,    90,   636,   178,   361,
     377,   470,   479,    91,    92,    93,   247,   482,   483,   521,
      94,    95,   190,   330,    96,   209,   212,   214,   292,    97,
     392,   393,    98,   387,   388,    99,   336,   277,   546,   579,
     677,   451,   452,   453,   614,   100,   334,   574,   270,   542,
     573,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   424,   111,   112,   113,   114,   115,   116,   586,   117,
     118,   119,   120,   121,   122,   123,   124,   278,   271,   406,
     400,   282,   226,   513,   191,   200,   324,   346,   353,   465,
     192,   272,   279,   354,   215,   213,   273,   227,   238,   134,
     374,   193,   233,   205,   206
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -511
static const yytype_int16 yypact[] =
{
     -15,   -67,   -55,    72,    67,   -15,  -511,  -511,    19,  -511,
    -511,    41,  -511,    67,    92,  -511,    54,    22,  -511,    62,
     161,  -511,  -511,  -511,   107,    69,   502,    78,    73,  -511,
     134,    84,    85,  -511,   170,   170,   170,   170,    86,    87,
      88,    89,    90,    93,    95,    96,    99,   100,   101,   103,
     104,   105,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,  -511,   119,   120,   121,   170,   122,   170,
     125,  -511,    65,   124,   126,   128,   129,   130,  -511,   502,
    -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,
    -511,  -511,  -511,  -511,  -511,   131,  -511,  -511,  -511,  -511,
    -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,
    -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,
    -511,  -511,  -511,  -511,  -511,   502,   107,   133,   135,   136,
     132,    16,  -511,  -511,   137,   140,   141,   142,    33,    -9,
      -9,     0,   143,   198,   199,   144,    -9,    -9,     1,   143,
     143,   -22,     0,     0,     0,   200,    -9,   145,    39,    -9,
      -9,    -9,    -9,   -22,    22,    64,  -511,    -9,   147,   143,
     208,   229,   236,    -9,   242,   146,  -511,   248,   148,   149,
    -511,   258,   259,   260,  -511,  -511,   151,  -511,  -511,   263,
     159,   131,  -511,  -511,    61,    61,    38,   -21,  -511,  -511,
     160,   162,   163,   164,   266,  -511,  -511,   167,  -511,  -511,
     168,  -511,  -511,   169,  -511,   171,  -511,   172,   173,   269,
     175,   176,  -511,  -511,  -511,   177,   273,  -511,   178,   179,
     180,  -511,   181,   182,   288,   184,  -511,  -511,   186,   187,
    -511,  -511,  -511,   189,  -511,  -511,  -511,   190,   185,   192,
      -1,   193,   191,   194,   197,   201,   202,  -511,  -511,  -511,
    -511,  -511,   203,   204,   299,   205,    63,   206,  -511,   209,
    -511,   210,  -511,  -511,  -511,  -511,   214,   213,   212,  -511,
    -511,  -511,   220,  -511,    -9,   254,   264,   314,   221,    83,
     198,   199,   222,    27,   270,   224,   282,     0,   -10,  -511,
     261,     0,     0,     0,    -9,   320,   262,    18,    -9,    94,
      11,    33,   502,  -511,   369,   265,   267,   370,  -511,  -511,
     268,   -14,   271,    83,  -511,   372,   274,   373,  -511,  -511,
    -511,  -511,   374,    -4,   275,   376,   276,    -3,    -9,  -511,
     272,   280,   283,   379,  -511,  -511,   286,  -511,  -511,   144,
    -511,   285,  -511,   292,  -511,  -511,   380,  -511,   293,  -511,
     381,   298,    83,   300,   302,  -511,  -511,   303,   355,  -511,
    -511,  -511,  -511,  -511,   304,  -511,   410,   308,   309,   305,
     310,    23,   395,   313,   312,   315,   419,  -511,   322,  -511,
    -511,   324,  -511,   325,  -511,   326,  -511,   317,   319,  -511,
     327,  -511,    44,   323,    44,  -511,   330,  -511,  -511,    33,
     436,   438,   334,   -22,  -511,   440,    26,    29,   382,   336,
      20,  -511,    22,   383,  -511,    83,   339,    22,   340,    21,
     102,   377,   397,   343,   344,   345,   452,   502,    68,   347,
     268,   348,   271,   453,  -511,  -511,    -9,   170,   170,   346,
    -511,   349,    44,  -511,  -511,   350,    -9,  -511,   351,   352,
     458,   354,   353,  -511,  -511,  -511,  -511,   460,  -511,    97,
     359,  -511,  -511,   360,    45,  -511,   466,  -511,   467,   131,
     356,  -511,   363,  -511,   399,   365,    83,   471,   474,   371,
     366,   475,   375,   368,    68,     9,  -511,   364,  -511,   378,
    -511,   384,   385,   170,  -511,  -511,  -511,  -511,   483,  -511,
     484,   387,   464,  -511,  -511,   386,   388,    21,   486,  -511,
    -511,   389,   390,   391,  -511,   439,    45,   392,   487,  -511,
     394,   396,    83,  -511,   398,  -511,  -511,  -511,   400,   402,
     403,   488,   418,    61,    61,   426,   442,  -511,   443,   495,
     444,  -511,    63,   131,   445,  -511,  -511,   500,   434,  -511,
    -511,   502,   446,   503,    83,   447,  -511,   321,  -511,  -511,
    -511,   448,    17,  -511,  -511,   449,  -511,  -511,    91,  -511,
     505,   450,   506,   451,  -511,   555,  -511,   454,   502,   455,
      83,   456,  -511,   553,   321,  -511,  -511,  -511,   321,    83,
    -511,  -511,  -511,  -511,   459,   462,  -511,   463,  -511,   469,
    -511,  -511,  -511,    -4,   461,   472,  -511,  -511,    22,  -511,
    -511,  -511,  -511,  -511,   476,   478,   479,  -511,  -511,   480,
    -511,  -511,   470,  -511,  -511,  -511,   477,  -511,  -511,   481,
    -511,  -511,    83,  -511,  -511,  -511,   482,   485,   560,   566,
     589,  -511,    44,    44,  -511,  -511,   590,   591,   594,   -39,
    -511,   502,  -511,  -511,    66,  -511,  -511,  -511,  -511,   418,
     492,   494,  -511,  -511,  -511,  -511,   491,  -511,   496,  -511,
    -511,   351,  -511,   525,   -39,  -511,  -511,   526,  -511,   489,
      44,   497,  -511
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -511,  -511,   598,  -511,  -511,   601,  -511,  -511,  -511,   -66,
    -511,  -511,   490,   -78,  -510,   123,  -511,  -511,  -511,  -511,
     -65,  -511,  -511,   138,  -511,  -511,  -511,  -458,  -511,  -511,
    -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,
    -511,  -511,   311,   457,  -511,  -511,  -511,  -511,  -185,  -511,
    -511,  -511,   106,  -511,  -511,  -511,  -511,  -511,   127,    98,
    -511,  -511,   150,    70,  -511,   335,   337,   277,  -511,  -511,
     188,  -511,  -511,   195,  -511,  -511,  -511,  -511,  -511,  -511,
     -57,  -393,  -511,  -511,  -511,  -511,  -511,   139,   422,   -20,
    -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,
    -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,
    -511,  -511,  -511,  -511,  -511,  -511,  -511,  -511,  -379,  -511,
      24,  -511,   216,  -511,  -131,  -288,  -511,  -316,    55,  -511,
    -511,  -511,  -511,  -511,  -511,  -186,  -119,   -17,  -511,   -32,
    -511,  -132,  -511,  -134,  -115
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -163
static const yytype_int16 yytable[] =
{
      23,   176,   166,   135,   136,   137,   267,   394,   201,   202,
     280,   455,   211,   216,   221,   217,   218,   220,   228,   229,
     230,   600,   369,   378,   210,   232,   433,   207,   239,   240,
     241,   242,   224,   281,   222,   223,   249,   168,   203,   203,
     389,   211,   255,   236,   359,   185,   421,   179,   186,   519,
     399,   405,     8,   185,   251,   185,   186,   596,   186,   505,
     447,   448,     9,   675,   208,   375,   601,   602,   603,   245,
     185,   679,    10,   186,   468,   477,   187,   188,   676,    11,
     463,   350,   198,   604,   596,   351,   352,   199,   596,   464,
       1,     2,   275,   237,   276,    22,    22,   605,   606,   520,
     434,   360,   189,    22,   607,   608,   609,   610,   611,   473,
     219,   204,   219,    22,    22,   268,   269,   449,   246,   315,
     680,   457,   376,     7,   328,   329,    22,   189,     7,   234,
      16,   469,   478,   344,   612,   316,   644,   345,   460,    22,
     645,   444,   127,   128,   129,   350,   372,   244,   373,   351,
     352,    17,   491,   339,   492,   480,   481,   187,   188,    19,
     616,   617,   618,   358,   575,   575,    21,   363,   364,   365,
     529,   210,    24,   366,    25,    28,   132,   371,   170,    30,
     283,   619,   126,   620,   621,   622,   623,   624,   625,   626,
     627,   628,   629,   125,   130,   131,   138,   139,   140,   141,
     142,   208,   211,   143,   231,   144,   145,   408,    22,   146,
     147,   148,   252,   149,   150,   151,   565,   216,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   167,   253,   379,   169,   172,   171,   173,   174,
     177,   175,   181,   254,   182,   183,   256,   194,   592,   184,
     195,   196,   197,   258,   204,   189,   234,   250,   257,   670,
     671,   261,   262,   263,   264,   260,   259,   265,   266,   284,
     288,   285,   286,   295,   641,   287,   289,   290,   291,   299,
    -150,   293,   294,   646,   296,   297,   298,   301,   302,   303,
     304,   305,   306,   307,   524,   308,   309,   691,   310,   311,
     312,   314,   317,   326,   390,   318,   320,   340,   319,   538,
     321,   322,   323,   325,   327,   500,   401,   341,   342,   333,
     407,   337,   332,   367,   331,   507,   663,   335,  -162,   338,
     343,   349,    31,   356,   355,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,   357,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,   490,
      55,    56,    57,    58,    59,    60,    61,    62,   584,    63,
     362,   368,   380,   383,   381,   395,   382,   397,   398,   386,
     403,   409,   391,   412,   417,   419,    64,    65,   396,   410,
     402,   404,   411,    66,    67,   413,    68,    69,   415,    70,
      71,   416,   418,    72,    73,   471,   595,   420,   426,   422,
     475,   423,   425,   427,   428,   501,   502,   429,   430,   432,
     435,   431,   436,   439,    74,    75,     1,   437,    76,   444,
     438,   440,   441,   445,   442,   443,   446,   454,   545,   456,
      77,   458,   459,   460,   462,   467,   466,   472,   474,   476,
     485,   -95,   486,   487,   488,   489,   495,   497,   499,   503,
     508,   510,   511,   512,   515,   504,   506,   514,   517,   518,
     522,   523,   526,   527,   528,   530,   525,   531,   539,   534,
     532,   540,   533,   589,   536,   535,   547,   541,   548,   550,
     554,   562,   480,   571,   543,   544,   549,   552,   551,   581,
     557,   555,   556,   563,   587,   564,   591,   561,   566,   632,
     639,   634,   568,    31,   569,   570,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,   572,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
     577,    55,    56,    57,    58,    59,    60,    61,    62,   588,
      63,   578,   580,   582,   585,   590,   593,   599,   613,   637,
     643,   631,   633,   635,   666,   642,   638,    64,    65,   647,
     667,   640,   648,   649,    66,    67,   652,    68,    69,   650,
      70,    71,   660,   678,    72,    73,   656,   653,   657,   658,
     659,   664,   661,   668,   672,   673,   401,   662,   674,  -101,
     689,   655,   665,    15,   690,    74,    75,     1,   682,    76,
     683,   684,   685,   692,    18,   686,   180,   274,   370,   516,
     243,    77,   583,   553,   560,   347,   414,   688,   348,   461,
     498,   669,   537,   630,     0,   496,     0,   651,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   559,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   576
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-511))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      17,    79,    67,    35,    36,    37,   191,   323,   139,   140,
     196,   404,     3,   145,   148,   146,   147,   148,   152,   153,
     154,     4,     4,   311,   143,   156,     3,   142,   159,   160,
     161,   162,    54,    54,   149,   150,   167,    69,    38,    38,
      54,     3,   173,     4,    54,    54,   362,   125,    57,     4,
      54,    54,   119,    54,   169,    54,    57,   567,    57,   452,
      16,    17,   117,   102,     3,    54,    49,    50,    51,     5,
      54,     5,     0,    57,    54,    54,    60,    61,   117,    12,
      54,    54,    49,    66,   594,    58,    59,    54,   598,    63,
     105,   106,    54,    54,    56,   117,   117,    80,    81,    54,
      77,   111,   111,   117,    87,    88,    89,    90,    91,   425,
     111,   111,   111,   117,   117,    54,    55,    73,    54,   250,
      54,   409,   111,     0,    61,    62,   117,   111,     5,   111,
     111,   111,   111,    50,   117,   250,   594,    54,   109,   117,
     598,   112,     8,     9,    10,    54,    52,   164,    54,    58,
      59,   110,    84,   284,    86,    53,    54,    60,    61,    67,
      69,    70,    71,   297,   543,   544,   112,   301,   302,   303,
     486,   290,   110,   304,    13,    68,     6,   308,   113,   110,
     197,    90,   109,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   115,   110,   110,   110,   110,   110,   110,
     110,     3,     3,   110,     4,   110,   110,   338,   117,   110,
     110,   110,     4,   110,   110,   110,   532,   349,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,     4,   312,   110,   110,   113,   110,   110,
     109,   111,   109,     7,   109,   109,     4,   110,   564,   117,
     110,   110,   110,     5,   111,   111,   111,   110,   112,   652,
     653,     3,     3,     3,   113,   116,   118,     4,   109,   109,
       4,   109,   109,     4,   590,   111,   109,   109,   109,     6,
     109,   109,   109,   599,   109,   109,   109,   109,   109,   109,
     109,   109,     4,   109,   479,   109,   109,   690,   109,   109,
     115,   109,   109,     4,   321,   114,   109,    53,   114,   495,
     109,   109,   109,   109,   109,   446,   333,    53,     4,   109,
     337,   109,   113,     3,   118,   456,   642,   113,   115,   109,
     109,   109,    11,   109,    64,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    64,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,   437,
      39,    40,    41,    42,    43,    44,    45,    46,   553,    48,
     109,   109,     3,     3,   109,     3,   109,     4,     4,   111,
       4,   109,   111,     4,     4,     4,    65,    66,   114,   109,
     115,   115,   109,    72,    73,   109,    75,    76,   113,    78,
      79,   109,   109,    82,    83,   422,    85,   109,    53,   109,
     427,   109,   109,   109,     4,   447,   448,   109,   109,   109,
      25,   116,   109,     4,   103,   104,   105,   115,   107,   112,
     115,   109,   108,   114,   109,   109,   109,   114,   503,   109,
     119,     5,     4,   109,     4,   109,    64,    64,   109,   109,
      53,    74,   109,   109,   109,     3,   109,   109,     5,   113,
     109,   109,     4,   109,     4,   116,   116,   114,   109,   109,
       4,     4,   109,    74,   109,     4,   120,     3,   495,     4,
     109,   117,   116,   561,   116,   110,     3,   109,     4,    25,
       4,     4,    53,     5,   110,   110,   109,   109,   112,     4,
     109,   112,   112,   109,     4,   109,     3,   115,   110,     4,
     588,     5,   112,    11,   112,   112,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,   109,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
     114,    39,    40,    41,    42,    43,    44,    45,    46,   115,
      48,   109,   109,   109,   109,   109,   109,   109,   109,     4,
       7,   578,   112,   112,     4,   109,   112,    65,    66,   110,
       4,   116,   110,   110,    72,    73,   115,    75,    76,   110,
      78,    79,   112,   661,    82,    83,   110,   115,   110,   110,
     110,   109,   115,     4,     4,     4,   613,   116,     4,    74,
      74,   618,   117,     5,   115,   103,   104,   105,   116,   107,
     116,   120,   116,   116,    13,   681,   126,   195,   307,   469,
     163,   119,   552,   517,   526,   290,   349,   684,   291,   413,
     442,   651,   494,   578,    -1,   440,    -1,   613,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   525,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   544
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   105,   106,   122,   123,   124,   125,   136,   119,   117,
       0,    12,   126,   127,   128,   123,   111,   110,   126,    67,
     132,   112,   117,   258,   110,    13,   129,   137,    68,   133,
     110,    11,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    39,    40,    41,    42,    43,
      44,    45,    46,    48,    65,    66,    72,    73,    75,    76,
      78,    79,    82,    83,   103,   104,   107,   119,   134,   135,
     136,   138,   139,   142,   150,   152,   156,   161,   162,   165,
     167,   174,   175,   176,   181,   182,   185,   190,   193,   196,
     206,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   223,   224,   225,   226,   227,   228,   230,   231,   232,
     233,   234,   235,   236,   237,   115,   109,     8,     9,    10,
     110,   110,     6,   141,   260,   260,   260,   260,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   141,   110,   260,   110,
     113,   113,   110,   110,   110,   111,   134,   109,   169,   134,
     133,   109,   109,   109,   117,    54,    57,    60,    61,   111,
     183,   245,   251,   262,   110,   110,   110,   110,    49,    54,
     246,   245,   245,    38,   111,   264,   265,   265,     3,   186,
     257,     3,   187,   256,   188,   255,   262,   245,   245,   111,
     245,   264,   265,   265,    54,   164,   243,   258,   264,   264,
     264,     4,   245,   263,   111,   163,     4,    54,   259,   245,
     245,   245,   245,   164,   258,     5,    54,   177,   153,   245,
     110,   265,     4,     4,     7,   245,     4,   112,     5,   118,
     116,     3,     3,     3,   113,     4,   109,   169,    54,    55,
     209,   239,   252,   257,   209,    54,    56,   198,   238,   253,
     256,    54,   242,   258,   109,   109,   109,   111,     4,   109,
     109,   109,   189,   109,   109,     4,   109,   109,   109,     6,
     140,   109,   109,   109,   109,   109,     4,   109,   109,   109,
     109,   109,   115,   154,   109,   245,   265,   109,   114,   114,
     109,   109,   109,   109,   247,   109,     4,   109,    61,    62,
     184,   118,   113,   109,   207,   113,   197,   109,   109,   245,
      53,    53,     4,   109,    50,    54,   248,   186,   187,   109,
      54,    58,    59,   249,   254,    64,   109,    64,   264,    54,
     111,   170,   109,   264,   264,   264,   245,     3,   109,     4,
     163,   245,    52,    54,   261,    54,   111,   171,   246,   134,
       3,   109,   109,     3,   151,   143,   111,   194,   195,    54,
     258,   111,   191,   192,   248,     3,   114,     4,     4,    54,
     241,   258,   115,     4,   115,    54,   240,   258,   245,   109,
     109,   109,     4,   109,   188,   113,   109,     4,   109,     4,
     109,   248,   109,   109,   222,   109,    53,   109,     4,   109,
     109,   116,   109,     3,    77,    25,   109,   115,   115,     4,
     109,   108,   109,   109,   112,   114,   109,    16,    17,    73,
     157,   202,   203,   204,   114,   202,   109,   246,     5,     4,
     109,   243,     4,    54,    63,   250,    64,   109,    54,   111,
     172,   258,    64,   248,   109,   258,   109,    54,   111,   173,
      53,    54,   178,   179,   155,    53,   109,   109,   109,     3,
     134,    84,    86,   144,   145,   109,   194,   109,   191,     5,
     245,   260,   260,   113,   116,   202,   116,   245,   109,   130,
     109,     4,   109,   244,   114,     4,   183,   109,   109,     4,
      54,   180,     4,     4,   169,   120,   109,    74,   109,   248,
       4,     3,   109,   116,     4,   110,   116,   144,   256,   258,
     117,   109,   210,   110,   110,   141,   199,     3,     4,   109,
      25,   112,   109,   173,     4,   112,   112,   109,   166,   179,
     180,   115,     4,   109,   109,   248,   110,   147,   112,   112,
     112,     5,   109,   211,   208,   239,   208,   114,   109,   200,
     109,     4,   109,   184,   169,   109,   229,     4,   115,   134,
     109,     3,   248,   109,   146,    85,   135,   148,   149,   109,
       4,    49,    50,    51,    66,    80,    81,    87,    88,    89,
      90,    91,   117,   109,   205,   158,    69,    70,    71,    90,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     249,   258,     4,   112,     5,   112,   168,     4,   112,   134,
     116,   248,   109,     7,   148,   148,   248,   110,   110,   110,
     110,   241,   115,   115,   159,   258,   110,   110,   110,   110,
     112,   115,   116,   248,   109,   117,     4,     4,     4,   210,
     202,   202,     4,     4,     4,   102,   117,   201,   134,     5,
      54,   131,   116,   116,   120,   116,   130,   160,   201,    74,
     115,   202,   116
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
      int yyn = yypact[*yyssp];
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
      yychar = YYLEX;
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 8:

/* Line 1806 of yacc.c  */
#line 203 "./lev_comp.y"
    {
		      include_push( (yyvsp[(2) - (2)].map) );
		      Free((yyvsp[(2) - (2)].map));
		  }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 214 "./lev_comp.y"
    {
			if (fatal_error > 0) {
				(void) fprintf(stderr,
				"%s : %d errors detected. No output created!\n",
					fname, fatal_error);
			} else {
				if (!write_level_file((yyvsp[(1) - (4)].map), splev)) {
				    yyerror("Can't write output file!!");
				    exit(EXIT_FAILURE);
				}
			}
			Free((yyvsp[(1) - (4)].map));
			Free(splev);
			splev = NULL;
		  }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 232 "./lev_comp.y"
    {
		      struct lc_funcdefs *f;
			if (index((yyvsp[(3) - (3)].map), '.'))
			    yyerror("Invalid dot ('.') in level name.");
			if ((int) strlen((yyvsp[(3) - (3)].map)) > 8)
			    yyerror("Level names limited to 8 characters.");
			n_plist = n_mlist = n_olist = 0;
			f = function_definitions;
			while (f) {
			    f->n_called = 0;
			    f = f->next;
			}
			splev = (sp_lev *)alloc(sizeof(sp_lev));
			splev->n_opcodes = 0;
			splev->opcodes = NULL;
			(yyval.map) = (yyvsp[(3) - (3)].map);
		  }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 252 "./lev_comp.y"
    {
		      add_opvars(splev, "iiiiiiiio", LVLINIT_NONE,0,0,0, 0,0,0,0, SPO_INITLEVEL);
		  }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 256 "./lev_comp.y"
    {
		      long filling = what_map_char((char) (yyvsp[(5) - (6)].i));
		      if (filling == INVALID_TYPE || filling >= MAX_TYPE)
			  yyerror("INIT_MAP: Invalid fill char type.");
		      add_opvars(splev, "iiiiiiiio", LVLINIT_SOLIDFILL,filling,0,(long)(yyvsp[(6) - (6)].i), 0,0,0,0, SPO_INITLEVEL);
		      max_x_map = COLNO-1;
		      max_y_map = ROWNO;
		  }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 265 "./lev_comp.y"
    {
		      long filling = what_map_char((char) (yyvsp[(5) - (5)].i));
		      if (filling == INVALID_TYPE || filling >= MAX_TYPE)
			  yyerror("INIT_MAP: Invalid fill char type.");
		      add_opvars(splev, "iiiiiiiio", LVLINIT_MAZEGRID,filling,0,0, 0,0,0,0, SPO_INITLEVEL);
		      max_x_map = COLNO-1;
		      max_y_map = ROWNO;
		  }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 274 "./lev_comp.y"
    {
		      long fg = what_map_char((char) (yyvsp[(5) - (16)].i));
		      long bg = what_map_char((char) (yyvsp[(7) - (16)].i));
		      long smoothed = (yyvsp[(9) - (16)].i);
		      long joined = (yyvsp[(11) - (16)].i);
		      long lit = (yyvsp[(13) - (16)].i);
		      long walled = (yyvsp[(15) - (16)].i);
		      long filling = (yyvsp[(16) - (16)].i);
		      if (fg == INVALID_TYPE || fg >= MAX_TYPE)
			  yyerror("INIT_MAP: Invalid foreground type.");
		      if (bg == INVALID_TYPE || bg >= MAX_TYPE)
			  yyerror("INIT_MAP: Invalid background type.");
		      if (joined && fg != CORR && fg != ROOM)
			  yyerror("INIT_MAP: Invalid foreground type for joined map.");

		      if (filling == INVALID_TYPE)
			  yyerror("INIT_MAP: Invalid fill char type.");

		      add_opvars(splev, "iiiiiiiio", LVLINIT_MINES,filling,walled,lit, joined,smoothed,bg,fg, SPO_INITLEVEL);
			max_x_map = COLNO-1;
			max_y_map = ROWNO;
		  }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 299 "./lev_comp.y"
    {
		      (yyval.i) = -1;
		  }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 303 "./lev_comp.y"
    {
		      (yyval.i) = what_map_char((char) (yyvsp[(2) - (2)].i));
		  }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 314 "./lev_comp.y"
    {
		      add_opvars(splev, "io", 0, SPO_LEVEL_FLAGS);
		  }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 318 "./lev_comp.y"
    {
		      add_opvars(splev, "io", (long)(yyvsp[(3) - (3)].i), SPO_LEVEL_FLAGS);
		  }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 324 "./lev_comp.y"
    {
		      (yyval.i) = ((yyvsp[(1) - (3)].i) | (yyvsp[(3) - (3)].i));
		  }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 328 "./lev_comp.y"
    {
		      (yyval.i) = (yyvsp[(1) - (1)].i);
		  }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 384 "./lev_comp.y"
    {
		      struct lc_funcdefs *funcdef;

		      if (in_function_definition)
			  yyerror("Recursively defined functions not allowed.");

		      in_function_definition++;

		      if (funcdef_defined(function_definitions, (yyvsp[(2) - (4)].map), 1))
			  yyerror("Function already defined once.");

		      funcdef = funcdef_new(-1, (yyvsp[(2) - (4)].map));
		      funcdef->next = function_definitions;
		      function_definitions = funcdef;
		      function_splev_backup = splev;
		      splev = &(funcdef->code);

		  }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 403 "./lev_comp.y"
    {
		      add_opvars(splev, "io", 0, SPO_RETURN);
		      splev = function_splev_backup;
		      in_function_definition--;
		  }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 411 "./lev_comp.y"
    {
		      struct lc_funcdefs *tmpfunc;
		      tmpfunc = funcdef_defined(function_definitions, (yyvsp[(1) - (3)].map), 1);
		      if (tmpfunc) {
			  long l;
			  if (!(tmpfunc->n_called)) {
			      /* we haven't called the function yet, so insert it in the code */
			      struct opvar *jmp = New(struct opvar);
			      set_opvar_int(jmp, splev->n_opcodes+1);
			      add_opcode(splev, SPO_PUSH, jmp);
			      add_opcode(splev, SPO_JMP, NULL); /* we must jump past it first, then CALL it, due to RETURN. */

			      tmpfunc->addr = splev->n_opcodes;
			      splev_add_from(splev, &(tmpfunc->code));
			      set_opvar_int(jmp, splev->n_opcodes - jmp->vardata.l);
			  }
			  l = tmpfunc->addr - splev->n_opcodes - 2;
			  add_opvars(splev, "iio", 0, l, SPO_CALL);
			  tmpfunc->n_called++;
		      } else {
			  yyerror("No such function defined.");
		      }
		  }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 437 "./lev_comp.y"
    {
		      add_opcode(splev, SPO_EXIT, NULL);
		  }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 443 "./lev_comp.y"
    {
		      (yyval.i) = 100;
		  }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 447 "./lev_comp.y"
    {
		      if ((yyvsp[(1) - (1)].i) < 0 || (yyvsp[(1) - (1)].i) > 100) yyerror("unexpected percentile chance");
		      (yyval.i) = (yyvsp[(1) - (1)].i);
		  }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 454 "./lev_comp.y"
    {
		      /* val > rn2(100) */
		      add_opvars(splev, "ioi", 100, SPO_RN2, (long)(yyvsp[(1) - (1)].i));
		      (yyval.i) = SPO_JGE; /* TODO: shouldn't this be SPO_JG? */
                  }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 462 "./lev_comp.y"
    {
		      struct opvar *chkjmp;
		      if (in_switch_statement > 0)
			  yyerror("Cannot nest switch-statements.");

		      if ((yyvsp[(3) - (4)].i) < 1)
			  yyerror("Switch with fewer than 1 available choices.");

		      in_switch_statement++;

		      n_switch_case_list = 0;
		      n_switch_break_list = 0;
		      switch_default_case = NULL;

		      add_opvars(splev, "io", (long)(yyvsp[(3) - (4)].i), SPO_RN2);

		      chkjmp = New(struct opvar);
		      set_opvar_int(chkjmp, splev->n_opcodes+1);
		      switch_check_jump = chkjmp;
		      add_opcode(splev, SPO_PUSH, chkjmp);
		      add_opcode(splev, SPO_JMP, NULL);
		  }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 485 "./lev_comp.y"
    {
		      struct opvar *endjump = New(struct opvar);
		      int i;

		      set_opvar_int(endjump, splev->n_opcodes+1);

		      add_opcode(splev, SPO_PUSH, endjump);
		      add_opcode(splev, SPO_JMP, NULL);

		      set_opvar_int(switch_check_jump, splev->n_opcodes - switch_check_jump->vardata.l);

		      for (i = 0; i < n_switch_case_list; i++) {
			  add_opvars(splev, "oio", SPO_COPY, switch_case_value[i], SPO_CMP);
			  set_opvar_int(switch_case_list[i], switch_case_list[i]->vardata.l - splev->n_opcodes-1);
			  add_opcode(splev, SPO_PUSH, switch_case_list[i]);
			  add_opcode(splev, SPO_JE, NULL);
		      }

		      if (switch_default_case) {
			  set_opvar_int(switch_default_case, switch_default_case->vardata.l - splev->n_opcodes-1);
			  add_opcode(splev, SPO_PUSH, switch_default_case);
			  add_opcode(splev, SPO_JMP, NULL);
		      }

		      set_opvar_int(endjump, splev->n_opcodes - endjump->vardata.l);

		      for (i = 0; i < n_switch_break_list; i++) {
			  set_opvar_int(switch_break_list[i], splev->n_opcodes - switch_break_list[i]->vardata.l);
		      }

		      add_opcode(splev, SPO_POP, NULL); /* get rid of the value in stack */
		      in_switch_statement--;


		  }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 527 "./lev_comp.y"
    {
		      if (n_switch_case_list < MAX_SWITCH_CASES) {
			  struct opvar *tmppush = New(struct opvar);
			  set_opvar_int(tmppush, splev->n_opcodes);
			  switch_case_value[n_switch_case_list] = (yyvsp[(2) - (3)].i);
			  switch_case_list[n_switch_case_list++] = tmppush;
		      } else yyerror("Too many cases in a switch.");
		  }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 536 "./lev_comp.y"
    {
		  }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 539 "./lev_comp.y"
    {
		      struct opvar *tmppush = New(struct opvar);

		      if (switch_default_case)
			  yyerror("Switch default case already used.");

		      set_opvar_int(tmppush, splev->n_opcodes);
		      switch_default_case = tmppush;
		  }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 549 "./lev_comp.y"
    {
		  }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 558 "./lev_comp.y"
    {
		      struct opvar *tmppush = New(struct opvar);
		      set_opvar_int(tmppush, splev->n_opcodes);
		      if (n_switch_break_list >= MAX_SWITCH_BREAKS)
			  yyerror("Too many BREAKs inside single SWITCH");
		      switch_break_list[n_switch_break_list++] = tmppush;

		      add_opcode(splev, SPO_PUSH, tmppush);
		      add_opcode(splev, SPO_JMP, NULL);
		  }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 569 "./lev_comp.y"
    {
		  }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 574 "./lev_comp.y"
    {
		      struct opvar *tmppush = New(struct opvar);

		      if (n_if_list >= MAX_NESTED_IFS) {
			  yyerror("IF: Too deeply nested IFs.");
			  n_if_list = MAX_NESTED_IFS - 1;
		      }

		      if ((yyvsp[(3) - (4)].i) < 1)
			  yyerror("Loop with fewer than 1 repeats.");

		      add_opvars(splev, "i", (long)(yyvsp[(3) - (4)].i));

		      set_opvar_int(tmppush, splev->n_opcodes);
		      if_list[n_if_list++] = tmppush;

		      add_opvars(splev, "o", SPO_DEC);
		  }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 593 "./lev_comp.y"
    {
		      struct opvar *tmppush;

		      add_opvars(splev, "oio", SPO_COPY, 0, SPO_CMP);

		      tmppush = (struct opvar *) if_list[--n_if_list];
		      set_opvar_int(tmppush, tmppush->vardata.l - splev->n_opcodes-1);
		      add_opcode(splev, SPO_PUSH, tmppush);
		      add_opcode(splev, SPO_JG, NULL);
		      add_opcode(splev, SPO_POP, NULL); /* get rid of the count value in stack */
		  }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 607 "./lev_comp.y"
    {
		      struct opvar *tmppush2 = New(struct opvar);

		      if (n_if_list >= MAX_NESTED_IFS) {
			  yyerror("IF: Too deeply nested IFs.");
			  n_if_list = MAX_NESTED_IFS - 1;
		      }

		      add_opcode(splev, SPO_CMP, NULL);

		      set_opvar_int(tmppush2, splev->n_opcodes+1);

		      if_list[n_if_list++] = tmppush2;

		      add_opcode(splev, SPO_PUSH, tmppush2);

		      add_opcode(splev, (yyvsp[(2) - (2)].i), NULL);
		  }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 626 "./lev_comp.y"
    {
		     /* do nothing */
		  }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 632 "./lev_comp.y"
    {
		      if (n_if_list > 0) {
			  struct opvar *tmppush;
			  tmppush = (struct opvar *) if_list[--n_if_list];
			  set_opvar_int(tmppush, splev->n_opcodes - tmppush->vardata.l);
		      } else yyerror("IF: Huh?!  No start address?");
		  }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 640 "./lev_comp.y"
    {
		      if (n_if_list > 0) {
			  struct opvar *tmppush = New(struct opvar);
			  struct opvar *tmppush2;

			  set_opvar_int(tmppush, splev->n_opcodes+1);
			  add_opcode(splev, SPO_PUSH, tmppush);

			  add_opcode(splev, SPO_JMP, NULL);

			  tmppush2 = (struct opvar *) if_list[--n_if_list];

			  set_opvar_int(tmppush2, splev->n_opcodes - tmppush2->vardata.l);
			  if_list[n_if_list++] = tmppush;
		      } else yyerror("IF: Huh?!  No else-part address?");
		  }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 657 "./lev_comp.y"
    {
		      if (n_if_list > 0) {
			  struct opvar *tmppush;
			  tmppush = (struct opvar *) if_list[--n_if_list];
			  set_opvar_int(tmppush, splev->n_opcodes - tmppush->vardata.l);
		      } else yyerror("IF: Huh?! No end address?");
		  }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 667 "./lev_comp.y"
    {
		      if (strlen((yyvsp[(3) - (3)].map)) > 254)
			  yyerror("Message string > 255 characters.");
		      else {
			  add_opvars(splev, "so", (yyvsp[(3) - (3)].map), SPO_MESSAGE);
		      }
		  }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 677 "./lev_comp.y"
    {
		      struct opvar *tmppush2 = New(struct opvar);

		      if (n_if_list >= MAX_NESTED_IFS) {
			  yyerror("IF: Too deeply nested IFs.");
			  n_if_list = MAX_NESTED_IFS - 1;
		      }

		      add_opcode(splev, SPO_CMP, NULL);

		      set_opvar_int(tmppush2, splev->n_opcodes+1);

		      if_list[n_if_list++] = tmppush2;

		      add_opcode(splev, SPO_PUSH, tmppush2);

		      add_opcode(splev, (yyvsp[(3) - (4)].i), NULL);
		  }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 696 "./lev_comp.y"
    {
		     /* do nothing */
		  }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 702 "./lev_comp.y"
    {
		      if (n_if_list > 0) {
			  struct opvar *tmppush;
			  tmppush = (struct opvar *) if_list[--n_if_list];
			  set_opvar_int(tmppush, splev->n_opcodes - tmppush->vardata.l);
		      } else yyerror("IF: Huh?!  No start address?");
		  }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 710 "./lev_comp.y"
    {
		      if (n_if_list > 0) {
			  struct opvar *tmppush = New(struct opvar);
			  struct opvar *tmppush2;

			  set_opvar_int(tmppush, splev->n_opcodes+1);
			  add_opcode(splev, SPO_PUSH, tmppush);

			  add_opcode(splev, SPO_JMP, NULL);

			  tmppush2 = (struct opvar *) if_list[--n_if_list];

			  set_opvar_int(tmppush2, splev->n_opcodes - tmppush2->vardata.l);
			  if_list[n_if_list++] = tmppush;
		      } else yyerror("IF: Huh?!  No else-part address?");
		  }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 727 "./lev_comp.y"
    {
		      if (n_if_list > 0) {
			  struct opvar *tmppush;
			  tmppush = (struct opvar *) if_list[--n_if_list];
			  set_opvar_int(tmppush, splev->n_opcodes - tmppush->vardata.l);
		      } else yyerror("IF: Huh?! No end address?");
		  }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 739 "./lev_comp.y"
    {
		      add_opvars(splev, "iiiiiio", -1, -1, -1, -1, -1, -1, SPO_CORRIDOR);
		  }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 745 "./lev_comp.y"
    {
		      add_opvars(splev, "iiiiiio",
				 (yyvsp[(3) - (5)].corpos).room, (yyvsp[(3) - (5)].corpos).door, (yyvsp[(3) - (5)].corpos).wall,
				 (yyvsp[(5) - (5)].corpos).room, (yyvsp[(5) - (5)].corpos).door, (yyvsp[(5) - (5)].corpos).wall,
				 SPO_CORRIDOR);
		  }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 752 "./lev_comp.y"
    {
		      add_opvars(splev, "iiiiiio",
				 (yyvsp[(3) - (5)].corpos).room, (yyvsp[(3) - (5)].corpos).door, (yyvsp[(3) - (5)].corpos).wall,
				 -1, -1, (long)(yyvsp[(5) - (5)].i),
				 SPO_CORRIDOR);
		  }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 761 "./lev_comp.y"
    {
			(yyval.corpos).room = (yyvsp[(2) - (7)].i);
			(yyval.corpos).wall = (yyvsp[(4) - (7)].i);
			(yyval.corpos).door = (yyvsp[(6) - (7)].i);
		  }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 769 "./lev_comp.y"
    {
		      if (((yyvsp[(2) - (4)].i) < 100) && ((yyvsp[(1) - (4)].i) == OROOM))
			  yyerror("Only typed rooms can have a chance.");
		      else {
			  add_opvars(splev, "iii", (long)(yyvsp[(1) - (4)].i), (long)(yyvsp[(2) - (4)].i), (long)(yyvsp[(4) - (4)].i));
		      }
                  }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 779 "./lev_comp.y"
    {
		      add_opvars(splev, "iiiiiiio", (long)(yyvsp[(8) - (8)].i), ERR, ERR,
				 (yyvsp[(5) - (8)].crd).x, (yyvsp[(5) - (8)].crd).y, (yyvsp[(7) - (8)].sze).width, (yyvsp[(7) - (8)].sze).height, SPO_SUBROOM);
		  }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 784 "./lev_comp.y"
    {
		      add_opcode(splev, SPO_ENDROOM, NULL);
		  }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 790 "./lev_comp.y"
    {
		      add_opvars(splev, "iiiiiiio", (long)(yyvsp[(10) - (10)].i),
				 (yyvsp[(7) - (10)].crd).x, (yyvsp[(7) - (10)].crd).y, (yyvsp[(5) - (10)].crd).x, (yyvsp[(5) - (10)].crd).y,
				 (yyvsp[(9) - (10)].sze).width, (yyvsp[(9) - (10)].sze).height, SPO_ROOM);
		  }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 796 "./lev_comp.y"
    {
		      add_opcode(splev, SPO_ENDROOM, NULL);
		  }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 802 "./lev_comp.y"
    {
			(yyval.i) = 1;
		  }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 806 "./lev_comp.y"
    {
			(yyval.i) = (yyvsp[(2) - (2)].i);
		  }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 812 "./lev_comp.y"
    {
			if ( (yyvsp[(2) - (5)].i) < 1 || (yyvsp[(2) - (5)].i) > 5 ||
			    (yyvsp[(4) - (5)].i) < 1 || (yyvsp[(4) - (5)].i) > 5 ) {
			    yyerror("Room position should be between 1 & 5!");
			} else {
			    (yyval.crd).x = (yyvsp[(2) - (5)].i);
			    (yyval.crd).y = (yyvsp[(4) - (5)].i);
			}
		  }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 822 "./lev_comp.y"
    {
			(yyval.crd).x = (yyval.crd).y = ERR;
		  }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 828 "./lev_comp.y"
    {
			if ( (yyvsp[(2) - (5)].i) < 0 || (yyvsp[(4) - (5)].i) < 0) {
			    yyerror("Invalid subroom position !");
			} else {
			    (yyval.crd).x = (yyvsp[(2) - (5)].i);
			    (yyval.crd).y = (yyvsp[(4) - (5)].i);
			}
		  }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 837 "./lev_comp.y"
    {
			(yyval.crd).x = (yyval.crd).y = ERR;
		  }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 843 "./lev_comp.y"
    {
		      (yyval.crd).x = (yyvsp[(2) - (5)].i);
		      (yyval.crd).y = (yyvsp[(4) - (5)].i);
		  }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 848 "./lev_comp.y"
    {
		      (yyval.crd).x = (yyval.crd).y = ERR;
		  }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 854 "./lev_comp.y"
    {
			(yyval.sze).width = (yyvsp[(2) - (5)].i);
			(yyval.sze).height = (yyvsp[(4) - (5)].i);
		  }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 859 "./lev_comp.y"
    {
			(yyval.sze).height = (yyval.sze).width = ERR;
		  }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 865 "./lev_comp.y"
    {
		      yyerror("NAME for rooms is not used anymore.");
		      Free((yyvsp[(3) - (3)].map));
		  }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 872 "./lev_comp.y"
    {
		       yyerror("CHANCE for rooms is not used anymore.");
		   }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 878 "./lev_comp.y"
    {
			/* ERR means random here */
			if ((yyvsp[(7) - (9)].i) == ERR && (yyvsp[(9) - (9)].i) != ERR) {
		     yyerror("If the door wall is random, so must be its pos!");
			} else {
			    add_opvars(splev, "iiiio", (long)(yyvsp[(9) - (9)].i), (long)(yyvsp[(5) - (9)].i), (long)(yyvsp[(3) - (9)].i), (long)(yyvsp[(7) - (9)].i), SPO_ROOM_DOOR);
			}
		  }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 887 "./lev_comp.y"
    {
		      add_opvars(splev, "iiio",
				 (yyvsp[(5) - (5)].crd).x, (yyvsp[(5) - (5)].crd).y, (long)(yyvsp[(3) - (5)].i), SPO_DOOR);
		  }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 902 "./lev_comp.y"
    {
		      (yyval.i) = (yyvsp[(1) - (1)].i);
		  }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 906 "./lev_comp.y"
    {
		      (yyval.i) = ((yyvsp[(1) - (3)].i) | (yyvsp[(3) - (3)].i));
		  }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 916 "./lev_comp.y"
    {
		      add_opvars(splev, "iiiisiio", 0, 1, 1, 1, (char *)0, 0, 0, SPO_MAP);
		      max_x_map = COLNO-1;
		      max_y_map = ROWNO;
		  }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 922 "./lev_comp.y"
    {
		      add_opvars(splev, "iiii", 1, (long)(yyvsp[(2) - (3)].i), (long)((yyvsp[(1) - (3)].i) % 10), (long)((yyvsp[(1) - (3)].i) / 10));
		      scan_map((yyvsp[(3) - (3)].map), splev);
		      Free((yyvsp[(3) - (3)].map));
		  }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 928 "./lev_comp.y"
    {
		      add_opvars(splev, "iiii", 2, (long)(yyvsp[(4) - (5)].i), (yyvsp[(3) - (5)].crd).x, (yyvsp[(3) - (5)].crd).y);
		      scan_map((yyvsp[(5) - (5)].map), splev);
		      Free((yyvsp[(5) - (5)].map));
		  }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 936 "./lev_comp.y"
    {
			(yyval.i) = (yyvsp[(3) - (5)].i) + ((yyvsp[(5) - (5)].i) * 10);
		  }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 950 "./lev_comp.y"
    {
		     char *tmp_olist;

		     tmp_olist = (char *) alloc(n_olist+1);
		     (void) memcpy((genericptr_t)tmp_olist,
				   (genericptr_t)olist, n_olist);
		     tmp_olist[n_olist] = 0;
		     add_opvars(splev, "so", tmp_olist, SPO_RANDOM_OBJECTS);

		     on_olist = n_olist;
		     n_olist = 0;
		  }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 963 "./lev_comp.y"
    {
		     char *tmp_plist;
		     int i;

		     tmp_plist = (char *) alloc(n_plist*2+1);

		     for (i=0; i<n_plist; i++) {
			tmp_plist[i*2] = plist[i].x+1;
			tmp_plist[i*2+1] = plist[i].y+1;
		     }
		     tmp_plist[n_plist*2] = 0;
		     add_opvars(splev, "so", tmp_plist, SPO_RANDOM_PLACES);

		     on_plist = n_plist;
		     n_plist = 0;
		  }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 980 "./lev_comp.y"
    {
		     char *tmp_mlist;

		     tmp_mlist = (char *) alloc(n_mlist+1);
		     (void) memcpy((genericptr_t)tmp_mlist,
				   (genericptr_t)mlist, n_mlist);
		     tmp_mlist[n_mlist] = 0;
		     add_opvars(splev, "so", tmp_mlist, SPO_RANDOM_MONSTERS);
		     on_mlist = n_mlist;
		     n_mlist = 0;
		  }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 994 "./lev_comp.y"
    {
			if (n_olist < MAX_REGISTERS)
			    olist[n_olist++] = (yyvsp[(1) - (1)].i);
			else
			    yyerror("Object list too long!");
		  }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 1001 "./lev_comp.y"
    {
			if (n_olist < MAX_REGISTERS)
			    olist[n_olist++] = (yyvsp[(1) - (3)].i);
			else
			    yyerror("Object list too long!");
		  }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 1010 "./lev_comp.y"
    {
			if (n_mlist < MAX_REGISTERS)
			    mlist[n_mlist++] = (yyvsp[(1) - (1)].i);
			else
			    yyerror("Monster list too long!");
		  }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 1017 "./lev_comp.y"
    {
			if (n_mlist < MAX_REGISTERS)
			    mlist[n_mlist++] = (yyvsp[(1) - (3)].i);
			else
			    yyerror("Monster list too long!");
		  }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 1026 "./lev_comp.y"
    {
		      if (n_plist < MAX_REGISTERS) {
			    plist[n_plist].x = (yyvsp[(1) - (1)].crd).x;
			    plist[n_plist].y = (yyvsp[(1) - (1)].crd).y;
			    n_plist++;
		      } else
			    yyerror("Location list too long!");
		  }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 1035 "./lev_comp.y"
    {
		      if (n_plist < MAX_REGISTERS) {
			    plist[n_plist].x = (yyvsp[(1) - (1)].crd).x;
			    plist[n_plist].y = (yyvsp[(1) - (1)].crd).y;
			    n_plist++;
		      } else
			    yyerror("Location list too long!");
		  }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 1047 "./lev_comp.y"
    {
		      long chance = (yyvsp[(3) - (5)].i);
		      long n_sounds = (yyvsp[(5) - (5)].i);
		      if (chance < 0) chance = 0;
		      add_opvars(splev, "iio", chance, n_sounds, SPO_LEVEL_SOUNDS);
		  }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 1056 "./lev_comp.y"
    {
		      (yyval.i) = 1;
		  }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 1060 "./lev_comp.y"
    {
		      (yyval.i) = 1 + (yyvsp[(3) - (3)].i);
		  }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 1066 "./lev_comp.y"
    {
		      add_opvars(splev, "is", (long)(yyvsp[(2) - (5)].i), (yyvsp[(4) - (5)].map));
		  }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 1072 "./lev_comp.y"
    {
		      long chance = (yyvsp[(3) - (5)].i);
		      long total_mons = (yyvsp[(5) - (5)].i);
		      if (chance < 0) chance = 0;
		      else if (chance > 100) chance = 100;

		      if (total_mons < 1) yyerror("Monster generation: zero monsters defined?");
		      add_opvars(splev, "iio", chance, total_mons, SPO_MON_GENERATION);
		  }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 1084 "./lev_comp.y"
    {
		      (yyval.i) = 1;
		  }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 1088 "./lev_comp.y"
    {
		      (yyval.i) = 1 + (yyvsp[(3) - (3)].i);
		  }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 1094 "./lev_comp.y"
    {
		      long token = (yyvsp[(4) - (5)].i);
		      if ((yyvsp[(2) - (5)].i) < 1) yyerror("Monster generation chances are zero?");
		      if (token == ERR) yyerror("Monster generation: Invalid monster symbol");
		      add_opvars(splev, "iii", token, 1, (long)(yyvsp[(2) - (5)].i));
		  }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 1101 "./lev_comp.y"
    {
		      long token;
		      if ((yyvsp[(2) - (5)].i) < 1) yyerror("Monster generation chances are zero?");
		      token = get_monster_id((yyvsp[(4) - (5)].map), (char)0);
		      if (token == ERR) yyerror("Monster generation: Invalid monster name");
		      add_opvars(splev, "iii", token, 0, (long)(yyvsp[(2) - (5)].i));
		  }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 1111 "./lev_comp.y"
    {
		      add_opvars(splev, "io", 0, SPO_MONSTER);

		      if ( 1 == (yyvsp[(2) - (4)].i) ) {
			  if (n_if_list > 0) {
			      struct opvar *tmpjmp;
			      tmpjmp = (struct opvar *) if_list[--n_if_list];
			      set_opvar_int(tmpjmp, splev->n_opcodes - tmpjmp->vardata.l);
			  } else yyerror("conditional creation of monster, but no jump point marker.");
		      }
		  }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 1123 "./lev_comp.y"
    {
		      add_opvars(splev, "io", 1, SPO_MONSTER);
		      (yyval.i) = (yyvsp[(2) - (4)].i);
		  }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 1128 "./lev_comp.y"
    {
		     add_opvars(splev, "o", SPO_END_MONINVENT);
		     if ( 1 == (yyvsp[(5) - (8)].i) ) {
			 if (n_if_list > 0) {
			     struct opvar *tmpjmp;
			     tmpjmp = (struct opvar *) if_list[--n_if_list];
			     set_opvar_int(tmpjmp, splev->n_opcodes - tmpjmp->vardata.l);
			 } else yyerror("conditional creation of monster, but no jump point marker.");
		     }
		 }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 1141 "./lev_comp.y"
    {
		      long token = NON_PM;
		      if ((yyvsp[(3) - (6)].map)) {
			  token = get_monster_id((yyvsp[(3) - (6)].map), (char) (yyvsp[(1) - (6)].i));
			  if (token == ERR) {
			      yywarning("Invalid monster name!  Making random monster.");
			      token = NON_PM;
			  }
			  Free((yyvsp[(3) - (6)].map));
		      }
		      add_opvars(splev, "iiii", (yyvsp[(5) - (6)].crd).x, (yyvsp[(5) - (6)].crd).y, (long)(yyvsp[(1) - (6)].i), token);
		  }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 1156 "./lev_comp.y"
    {
		      struct opvar *stopit = New(struct opvar);
		      set_opvar_int(stopit, SP_M_V_END);
		      add_opcode(splev, SPO_PUSH, stopit);
		      (yyval.i) = 0x00;
		  }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 1163 "./lev_comp.y"
    {
		      if (( (yyvsp[(1) - (2)].i) & (yyvsp[(2) - (2)].i) ))
			  yyerror("MONSTER extra info already used.");
		      (yyval.i) = ( (yyvsp[(1) - (2)].i) | (yyvsp[(2) - (2)].i) );
		  }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 1171 "./lev_comp.y"
    {
		      add_opvars(splev, "si", (yyvsp[(2) - (2)].map), SP_M_V_NAME);
		      (yyval.i) = 0x0001;
		  }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 1176 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", (long)(yyvsp[(2) - (2)].i), SP_M_V_PEACEFUL);
		      (yyval.i) = 0x0002;
		  }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 1181 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", (long)(yyvsp[(2) - (2)].i), SP_M_V_ASLEEP);
		      (yyval.i) = 0x0004;
		  }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 1186 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", (long)(yyvsp[(2) - (2)].i), SP_M_V_ALIGN);
		      (yyval.i) = 0x0008;
		  }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 1191 "./lev_comp.y"
    {
		      add_opvars(splev, "sii", (yyvsp[(3) - (3)].map), (long)(yyvsp[(2) - (3)].i), SP_M_V_APPEAR);
		      (yyval.i) = 0x0010;
		  }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 1196 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", 1, SP_M_V_FEMALE);
		      (yyval.i) = 0x0020;
		  }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 1201 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", 1, SP_M_V_INVIS);
		      (yyval.i) = 0x0040;
		  }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 1206 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", 1, SP_M_V_CANCELLED);
		      (yyval.i) = 0x0080;
		  }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 1211 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", 1, SP_M_V_REVIVED);
		      (yyval.i) = 0x0100;
		  }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 1216 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", 1, SP_M_V_AVENGE);
		      (yyval.i) = 0x0200;
		  }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 1221 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", (long)(yyvsp[(4) - (4)].i), SP_M_V_FLEEING);
		      (yyval.i) = 0x0400;
		  }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 1226 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", (long)(yyvsp[(4) - (4)].i), SP_M_V_BLINDED);
		      (yyval.i) = 0x0800;
		  }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 1231 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", (long)(yyvsp[(4) - (4)].i), SP_M_V_PARALYZED);
		      (yyval.i) = 0x1000;
		  }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 1236 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", 1, SP_M_V_STUNNED);
		      (yyval.i) = 0x2000;
		  }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 1241 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", 1, SP_M_V_CONFUSED);
		      (yyval.i) = 0x4000;
		  }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 1246 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", (long)(yyvsp[(4) - (4)].i), SP_M_V_SEENTRAPS);
		      (yyval.i) = 0x8000;
		  }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 1253 "./lev_comp.y"
    {
		      int token = get_trap_type((yyvsp[(1) - (1)].map));
		      if (token == ERR || token == 0)
			  yyerror("Unknown trap type!");
		      (yyval.i) = (1L << (token - 1));
		  }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 1260 "./lev_comp.y"
    {
		      (yyval.i) = (long) ~0;
		  }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 1264 "./lev_comp.y"
    {
		      int token = get_trap_type((yyvsp[(1) - (3)].map));
		      if (token == ERR || token == 0)
			  yyerror("Unknown trap type!");

		      if ((1L << (token - 1)) & (yyvsp[(3) - (3)].i))
			  yyerror("MONSTER seen_traps, same trap listed twice.");

		      (yyval.i) = ((1L << (token - 1)) | (yyvsp[(3) - (3)].i));
		  }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 1277 "./lev_comp.y"
    {
		  }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 1287 "./lev_comp.y"
    {
		      add_opvars(splev, "io", (long)SP_OBJ_CONTENT, SPO_OBJECT);
		      if ( 1 == (yyvsp[(2) - (4)].i) ) {
			  if (n_if_list > 0) {
			      struct opvar *tmpjmp;
			      tmpjmp = (struct opvar *) if_list[--n_if_list];
			      set_opvar_int(tmpjmp, splev->n_opcodes - tmpjmp->vardata.l);
			  } else yyerror("conditional creation of obj, but no jump point marker.");
		      }
		  }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 1298 "./lev_comp.y"
    {
		      add_opvars(splev, "io", (long)(SP_OBJ_CONTENT|SP_OBJ_CONTAINER), SPO_OBJECT);
		      (yyval.i) = (yyvsp[(2) - (4)].i);
		  }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 1303 "./lev_comp.y"
    {
		      add_opcode(splev, SPO_POP_CONTAINER, NULL);

		      if ( 1 == (yyvsp[(5) - (8)].i) ) {
			  if (n_if_list > 0) {
			      struct opvar *tmpjmp;
			      tmpjmp = (struct opvar *) if_list[--n_if_list];
			      set_opvar_int(tmpjmp, splev->n_opcodes - tmpjmp->vardata.l);
			  } else yyerror("conditional creation of obj, but no jump point marker.");
		      }
		  }
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 1317 "./lev_comp.y"
    {
		      add_opvars(splev, "io", 0, SPO_OBJECT); /* 0 == not container, nor contents of one. */
		      if ( 1 == (yyvsp[(2) - (4)].i) ) {
			  if (n_if_list > 0) {
			      struct opvar *tmpjmp;
			      tmpjmp = (struct opvar *) if_list[--n_if_list];
			      set_opvar_int(tmpjmp, splev->n_opcodes - tmpjmp->vardata.l);
			  } else yyerror("conditional creation of obj, but no jump point marker.");
		      }
		  }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 1328 "./lev_comp.y"
    {
		      add_opvars(splev, "io", (long)SP_OBJ_CONTAINER, SPO_OBJECT);
		      (yyval.i) = (yyvsp[(2) - (4)].i);
		  }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 1333 "./lev_comp.y"
    {
		     add_opcode(splev, SPO_POP_CONTAINER, NULL);

		     if ( 1 == (yyvsp[(5) - (8)].i) ) {
			 if (n_if_list > 0) {
			     struct opvar *tmpjmp;
			     tmpjmp = (struct opvar *) if_list[--n_if_list];
			     set_opvar_int(tmpjmp, splev->n_opcodes - tmpjmp->vardata.l);
			 } else yyerror("conditional creation of obj, but no jump point marker.");
		     }
		 }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 1347 "./lev_comp.y"
    {
		      long token = -1;
		      if ((yyvsp[(3) - (4)].map)) {
			  token = get_object_id((yyvsp[(3) - (4)].map), (yyvsp[(1) - (4)].i));
			  if (token == ERR) {
			      yywarning("Illegal object name!  Making random object.");
			      token = -1;
			  }
			  Free((yyvsp[(3) - (4)].map));
		      }
		      add_opvars(splev, "iiii", -1, -1, (long)(yyvsp[(1) - (4)].i), token);
		  }
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 1362 "./lev_comp.y"
    {
		      long token = -1;
		      if ((yyvsp[(3) - (6)].map)) {
			  token = get_object_id((yyvsp[(3) - (6)].map), (yyvsp[(1) - (6)].i));
			  if (token == ERR) {
			      yywarning("Illegal object name!  Making random object.");
			      token = -1;
			  }
			  Free((yyvsp[(3) - (6)].map));
		      }
		      add_opvars(splev, "iiii", (yyvsp[(5) - (6)].crd).x, (yyvsp[(5) - (6)].crd).y, (long)(yyvsp[(1) - (6)].i), token);
		}
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 1377 "./lev_comp.y"
    {
		      struct opvar *stopit = New(struct opvar);
		      set_opvar_int(stopit, SP_O_V_END);
		      add_opcode(splev, SPO_PUSH, stopit);
		      (yyval.i) = 0x00;
		  }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 1384 "./lev_comp.y"
    {
		      if (( (yyvsp[(1) - (2)].i) & (yyvsp[(2) - (2)].i) ))
			  yyerror("OBJECT extra info already used.");
		      (yyval.i) = ( (yyvsp[(1) - (2)].i) | (yyvsp[(2) - (2)].i) );
		  }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 1392 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", (long)(yyvsp[(2) - (2)].i), SP_O_V_CURSE);
		      (yyval.i) = 0x0001;
		  }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 1397 "./lev_comp.y"
    {
		      long token = get_monster_id((yyvsp[(2) - (2)].map), (char)0);
		      if (token == ERR) {
			  /* "random" */
			  yywarning("OBJECT: Are you sure you didn't mean NAME:\"foo\"?");
			  token = NON_PM - 1;
		      }
		      add_opvars(splev, "ii", token, SP_O_V_CORPSENM);
		      Free((yyvsp[(2) - (2)].map));
		      (yyval.i) = 0x0002;
		  }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 1409 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", (long)(yyvsp[(2) - (2)].i), SP_O_V_SPE);
		      (yyval.i) = 0x0004;
		  }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 1414 "./lev_comp.y"
    {
		      add_opvars(splev, "si", (yyvsp[(4) - (4)].map), SP_O_V_NAME);
		      (yyval.i) = 0x0008;
		  }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 1419 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", (long)(yyvsp[(4) - (4)].i), SP_O_V_QUAN);
		      (yyval.i) = 0x0010;
		  }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 1424 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", 1, SP_O_V_BURIED);
		      (yyval.i) = 0x0020;
		  }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 1429 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", (long)(yyvsp[(2) - (2)].i), SP_O_V_LIT);
		      (yyval.i) = 0x0040;
		  }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 1434 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", (long)(yyvsp[(4) - (4)].i), SP_O_V_ERODED);
		      (yyval.i) = 0x0080;
		  }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 1439 "./lev_comp.y"
    {
		      if ((yyvsp[(2) - (2)].i) == D_LOCKED) {
			  add_opvars(splev, "ii", 1, SP_O_V_LOCKED);
			  (yyval.i) = 0x0100;
		      } else if ((yyvsp[(2) - (2)].i) == D_BROKEN) {
			  add_opvars(splev, "ii", 1, SP_O_V_BROKEN);
			  (yyval.i) = 0x0200;
		      } else
			  yyerror("OBJECT state can only be locked or broken.");
		  }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 1450 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", 1, SP_O_V_TRAPPED);
		      (yyval.i) = 0x0400;
		  }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 1455 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", (long)(yyvsp[(4) - (4)].i), SP_O_V_RECHARGED);
		      (yyval.i) = 0x0800;
		  }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 1460 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", 1, SP_O_V_INVIS);
		      (yyval.i) = 0x1000;
		  }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 1465 "./lev_comp.y"
    {
		      add_opvars(splev, "ii", 1, SP_O_V_GREASED);
		      (yyval.i) = 0x2000;
		  }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 1472 "./lev_comp.y"
    {
		      add_opvars(splev, "iiio", (yyvsp[(6) - (6)].crd).x, (yyvsp[(6) - (6)].crd).y, (long)(yyvsp[(4) - (6)].i), SPO_TRAP);
		      if ( 1 == (yyvsp[(2) - (6)].i) ) {
			  if (n_if_list > 0) {
			      struct opvar *tmpjmp;
			      tmpjmp = (struct opvar *) if_list[--n_if_list];
			      set_opvar_int(tmpjmp, splev->n_opcodes - tmpjmp->vardata.l);
			  } else yyerror("conditional creation of trap, but no jump point marker.");
		      }
		  }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 1485 "./lev_comp.y"
    {
		       long d, state = 0;
		       /* convert dir from a DIRECTION to a DB_DIR */
		       d = (yyvsp[(5) - (7)].i);
		       switch(d) {
		       case W_NORTH: d = DB_NORTH; break;
		       case W_SOUTH: d = DB_SOUTH; break;
		       case W_EAST:  d = DB_EAST;  break;
		       case W_WEST:  d = DB_WEST;  break;
		       default:
			   yyerror("Invalid drawbridge direction");
			   break;
		       }

		       if ( (yyvsp[(7) - (7)].i) == D_ISOPEN )
			   state = 1;
		       else if ( (yyvsp[(7) - (7)].i) == D_CLOSED )
			   state = 0;
		       else
			   yyerror("A drawbridge can only be open or closed!");
		       add_opvars(splev, "iiiio", (yyvsp[(3) - (7)].crd).x, (yyvsp[(3) - (7)].crd).y, state, d, SPO_DRAWBRIDGE);
		   }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 1510 "./lev_comp.y"
    {
		      add_opvars(splev, "iiiiio",
				 (yyvsp[(3) - (5)].crd).x, (yyvsp[(3) - (5)].crd).y, (long)(yyvsp[(5) - (5)].i), 1, 0, SPO_MAZEWALK);
		  }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 1515 "./lev_comp.y"
    {
		      add_opvars(splev, "iiiiio",
				 (yyvsp[(3) - (8)].crd).x, (yyvsp[(3) - (8)].crd).y,
				 (long)(yyvsp[(5) - (8)].i), (long)(yyvsp[(7) - (8)].i), (long)(yyvsp[(8) - (8)].i), SPO_MAZEWALK);
		  }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 1523 "./lev_comp.y"
    {
		      add_opvars(splev, "iiiio", -1,-1,-1,-1, SPO_WALLIFY);
		  }
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 1527 "./lev_comp.y"
    {
		      add_opvars(splev, "iiiio",
				 (yyvsp[(3) - (3)].lregn).x1, (yyvsp[(3) - (3)].lregn).y1, (yyvsp[(3) - (3)].lregn).x2, (yyvsp[(3) - (3)].lregn).y2, SPO_WALLIFY);
		  }
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 1534 "./lev_comp.y"
    {
		      add_opvars(splev, "iiio", (yyvsp[(3) - (5)].crd).x, (yyvsp[(3) - (5)].crd).y, (long)(yyvsp[(5) - (5)].i), SPO_LADDER);
		  }
    break;

  case 220:

/* Line 1806 of yacc.c  */
#line 1540 "./lev_comp.y"
    {
		      add_opvars(splev, "iiio", (yyvsp[(3) - (5)].crd).x, (yyvsp[(3) - (5)].crd).y, (long)(yyvsp[(5) - (5)].i), SPO_STAIR);
		  }
    break;

  case 221:

/* Line 1806 of yacc.c  */
#line 1546 "./lev_comp.y"
    {
		      add_opvars(splev, "iiiii iiiii iiso",
				 (yyvsp[(3) - (7)].lregn).x1, (yyvsp[(3) - (7)].lregn).y1, (yyvsp[(3) - (7)].lregn).x2, (yyvsp[(3) - (7)].lregn).y2, (yyvsp[(3) - (7)].lregn).area,
				 (yyvsp[(5) - (7)].lregn).x1, (yyvsp[(5) - (7)].lregn).y1, (yyvsp[(5) - (7)].lregn).x2, (yyvsp[(5) - (7)].lregn).y2, (yyvsp[(5) - (7)].lregn).area,
				 (long)(((yyvsp[(7) - (7)].i)) ? LR_UPSTAIR : LR_DOWNSTAIR),
				 0, (char *)0, SPO_LEVREGION);
		  }
    break;

  case 222:

/* Line 1806 of yacc.c  */
#line 1556 "./lev_comp.y"
    {
		      add_opvars(splev, "iiiii iiiii iiso",
				 (yyvsp[(3) - (7)].lregn).x1, (yyvsp[(3) - (7)].lregn).y1, (yyvsp[(3) - (7)].lregn).x2, (yyvsp[(3) - (7)].lregn).y2, (yyvsp[(3) - (7)].lregn).area,
				 (yyvsp[(5) - (7)].lregn).x1, (yyvsp[(5) - (7)].lregn).y1, (yyvsp[(5) - (7)].lregn).x2, (yyvsp[(5) - (7)].lregn).y2, (yyvsp[(5) - (7)].lregn).area,
				 LR_PORTAL, 0, (yyvsp[(7) - (7)].map), SPO_LEVREGION);
		  }
    break;

  case 223:

/* Line 1806 of yacc.c  */
#line 1565 "./lev_comp.y"
    {
		      long rtype;
		      switch((yyvsp[(6) - (6)].i)) {
		      case -1: rtype = LR_TELE; break;
		      case  0: rtype = LR_DOWNTELE; break;
		      case  1: rtype = LR_UPTELE; break;
		      }
		      add_opvars(splev, "iiiii iiiii iiso",
				 (yyvsp[(3) - (6)].lregn).x1, (yyvsp[(3) - (6)].lregn).y1, (yyvsp[(3) - (6)].lregn).x2, (yyvsp[(3) - (6)].lregn).y2, (yyvsp[(3) - (6)].lregn).area,
				 (yyvsp[(5) - (6)].lregn).x1, (yyvsp[(5) - (6)].lregn).y1, (yyvsp[(5) - (6)].lregn).x2, (yyvsp[(5) - (6)].lregn).y2, (yyvsp[(5) - (6)].lregn).area,
				 rtype, 0, (char *)0, SPO_LEVREGION);
		  }
    break;

  case 224:

/* Line 1806 of yacc.c  */
#line 1580 "./lev_comp.y"
    {
		      add_opvars(splev, "iiiii iiiii iiso",
				 (yyvsp[(3) - (5)].lregn).x1, (yyvsp[(3) - (5)].lregn).y1, (yyvsp[(3) - (5)].lregn).x2, (yyvsp[(3) - (5)].lregn).y2, (yyvsp[(3) - (5)].lregn).area,
				 (yyvsp[(5) - (5)].lregn).x1, (yyvsp[(5) - (5)].lregn).y1, (yyvsp[(5) - (5)].lregn).x2, (yyvsp[(5) - (5)].lregn).y2, (yyvsp[(5) - (5)].lregn).area,
				 (long)LR_BRANCH, 0, (char *)0, SPO_LEVREGION);
		  }
    break;

  case 225:

/* Line 1806 of yacc.c  */
#line 1589 "./lev_comp.y"
    {
			(yyval.i) = -1;
		  }
    break;

  case 226:

/* Line 1806 of yacc.c  */
#line 1593 "./lev_comp.y"
    {
			(yyval.i) = (yyvsp[(2) - (2)].i);
		  }
    break;

  case 227:

/* Line 1806 of yacc.c  */
#line 1599 "./lev_comp.y"
    {
		      add_opvars(splev, "iio", (yyvsp[(3) - (3)].crd).x, (yyvsp[(3) - (3)].crd).y, SPO_FOUNTAIN);
		  }
    break;

  case 228:

/* Line 1806 of yacc.c  */
#line 1605 "./lev_comp.y"
    {
		      add_opvars(splev, "iio", (yyvsp[(3) - (3)].crd).x, (yyvsp[(3) - (3)].crd).y, SPO_SINK);
		  }
    break;

  case 229:

/* Line 1806 of yacc.c  */
#line 1611 "./lev_comp.y"
    {
		      add_opvars(splev, "iio", (yyvsp[(3) - (3)].crd).x, (yyvsp[(3) - (3)].crd).y, SPO_POOL);
		  }
    break;

  case 230:

/* Line 1806 of yacc.c  */
#line 1617 "./lev_comp.y"
    {
		      long chance, from_ter, to_ter;

		      chance = (yyvsp[(11) - (11)].i);
		      if (chance < 0) chance = 0;
		      else if (chance > 100) chance = 100;

		      from_ter = what_map_char((char) (yyvsp[(5) - (11)].i));
		      if (from_ter >= MAX_TYPE) yyerror("Replace terrain: illegal 'from' map char");

		      to_ter = what_map_char((char) (yyvsp[(7) - (11)].i));
		      if (to_ter >= MAX_TYPE) yyerror("Replace terrain: illegal 'to' map char");

		      add_opvars(splev, "iiii iiiio",
				 (yyvsp[(3) - (11)].lregn).x1, (yyvsp[(3) - (11)].lregn).y1, (yyvsp[(3) - (11)].lregn).x2, (yyvsp[(3) - (11)].lregn).y2,
				 from_ter, to_ter, (long)(yyvsp[(9) - (11)].i), chance, SPO_REPLACETERRAIN);
		  }
    break;

  case 231:

/* Line 1806 of yacc.c  */
#line 1637 "./lev_comp.y"
    {
		     long c;

		     c = what_map_char((char) (yyvsp[(6) - (8)].i));
		     if (c >= MAX_TYPE) yyerror("Terrain: illegal map char");

		     add_opvars(splev, "iiii iiio",
				(yyvsp[(4) - (8)].crd).x, (yyvsp[(4) - (8)].crd).y, -1, -1,
				0, c, (yyvsp[(8) - (8)].i), SPO_TERRAIN);

		     if ( 1 == (yyvsp[(2) - (8)].i) ) {
			 if (n_if_list > 0) {
			     struct opvar *tmpjmp;
			     tmpjmp = (struct opvar *) if_list[--n_if_list];
			     set_opvar_int(tmpjmp, splev->n_opcodes - tmpjmp->vardata.l);
			 } else yyerror("conditional terrain modification, but no jump point marker.");
		     }
		 }
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 1657 "./lev_comp.y"
    {
		     long areatyp, c, x2,y2;

		     areatyp = (yyvsp[(6) - (12)].i);
		     if (areatyp == 1) {
			 x2 = (yyvsp[(8) - (12)].i);
			 y2 = -1;
		     } else {
			 x2 = -1;
			 y2 = (yyvsp[(8) - (12)].i);
		     }

		     c = what_map_char((char) (yyvsp[(10) - (12)].i));
		     if (c >= MAX_TYPE) yyerror("Terrain: illegal map char");

		     add_opvars(splev, "iiii iiio",
				(yyvsp[(4) - (12)].crd).x, (yyvsp[(4) - (12)].crd).y, x2, y2,
				areatyp, c, (long)(yyvsp[(12) - (12)].i), SPO_TERRAIN);

		     if ( 1 == (yyvsp[(2) - (12)].i) ) {
			 if (n_if_list > 0) {
			     struct opvar *tmpjmp;
			     tmpjmp = (struct opvar *) if_list[--n_if_list];
			     set_opvar_int(tmpjmp, splev->n_opcodes - tmpjmp->vardata.l);
			 } else yyerror("conditional terrain modification, but no jump point marker.");
		     }
		 }
    break;

  case 233:

/* Line 1806 of yacc.c  */
#line 1686 "./lev_comp.y"
    {
		     long c;

		     c = what_map_char((char) (yyvsp[(8) - (10)].i));
		     if (c >= MAX_TYPE) yyerror("Terrain: illegal map char");

		     add_opvars(splev, "iiii iiio",
				(yyvsp[(4) - (10)].lregn).x1, (yyvsp[(4) - (10)].lregn).y1, (yyvsp[(4) - (10)].lregn).x2, (yyvsp[(4) - (10)].lregn).y2,
				(long)(3 + (yyvsp[(6) - (10)].i)), c, (long)(yyvsp[(10) - (10)].i), SPO_TERRAIN);

		     if ( 1 == (yyvsp[(2) - (10)].i) ) {
			 if (n_if_list > 0) {
			     struct opvar *tmpjmp;
			     tmpjmp = (struct opvar *) if_list[--n_if_list];
			     set_opvar_int(tmpjmp, splev->n_opcodes - tmpjmp->vardata.l);
			 } else yyerror("conditional terrain modification, but no jump point marker.");
		     }
		 }
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 1707 "./lev_comp.y"
    {
		      long c;
		      c = what_map_char((char) (yyvsp[(5) - (10)].i));
		      if ((c == INVALID_TYPE) || (c >= MAX_TYPE)) yyerror("Terrain: illegal map char");
		      add_opvars(splev, "iiii iiiio",
				 (yyvsp[(3) - (10)].lregn).x1, (yyvsp[(3) - (10)].lregn).y1, (yyvsp[(3) - (10)].lregn).x2, (yyvsp[(3) - (10)].lregn).y2,
				 c, (long)(yyvsp[(7) - (10)].i), (long)(yyvsp[(9) - (10)].i), (long)(yyvsp[(10) - (10)].i), SPO_RANDLINE);
		  }
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 1717 "./lev_comp.y"
    {
			(yyval.i) = 0;
		  }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 1721 "./lev_comp.y"
    {
			(yyval.i) = (yyvsp[(2) - (2)].i);
		  }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 1727 "./lev_comp.y"
    {
		    long c, typ;

		    typ = what_map_char((char) (yyvsp[(5) - (11)].i));
		    if (typ == INVALID_TYPE || typ >= MAX_TYPE) {
			yyerror("SPILL: Invalid map character!");
		    }

		    c = (yyvsp[(9) - (11)].i);
		    if (c < 1) yyerror("SPILL: Invalid count!");

		    add_opvars(splev, "iiiiiio", (yyvsp[(3) - (11)].crd).x, (yyvsp[(3) - (11)].crd).y,
			       typ, (long)(yyvsp[(7) - (11)].i), c, (long)(yyvsp[(11) - (11)].i), SPO_SPILL);
		}
    break;

  case 238:

/* Line 1806 of yacc.c  */
#line 1744 "./lev_comp.y"
    {
		     add_opvars(splev, "iiiio",
				(yyvsp[(3) - (3)].lregn).x1, (yyvsp[(3) - (3)].lregn).y1, (yyvsp[(3) - (3)].lregn).x2, (yyvsp[(3) - (3)].lregn).y2, SPO_NON_DIGGABLE);
		  }
    break;

  case 239:

/* Line 1806 of yacc.c  */
#line 1751 "./lev_comp.y"
    {
		     add_opvars(splev, "iiiio",
				(yyvsp[(3) - (3)].lregn).x1, (yyvsp[(3) - (3)].lregn).y1, (yyvsp[(3) - (3)].lregn).x2, (yyvsp[(3) - (3)].lregn).y2, SPO_NON_PASSWALL);
		  }
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 1758 "./lev_comp.y"
    {
		      long rt, irr;

		      rt = (yyvsp[(7) - (8)].i);
		      if (( (yyvsp[(8) - (8)].i) ) & 1) rt += MAXRTYPE+1;

		      irr = ((( (yyvsp[(8) - (8)].i) ) & 2) != 0);

		      if ( (yyvsp[(3) - (8)].lregn).x1 > (yyvsp[(3) - (8)].lregn).x2 || (yyvsp[(3) - (8)].lregn).y1 > (yyvsp[(3) - (8)].lregn).y2 )
			  yyerror("Region start > end!");

		      if (rt == VAULT && (irr ||
					 ( (yyvsp[(3) - (8)].lregn).x2 - (yyvsp[(3) - (8)].lregn).x1 != 1) ||
					 ( (yyvsp[(3) - (8)].lregn).y2 - (yyvsp[(3) - (8)].lregn).y1 != 1)))
			 yyerror("Vaults must be exactly 2x2!");

		     add_opvars(splev, "iiii iiio",
				(yyvsp[(3) - (8)].lregn).x1, (yyvsp[(3) - (8)].lregn).y1, (yyvsp[(3) - (8)].lregn).x2, (yyvsp[(3) - (8)].lregn).y2,
				(long)(yyvsp[(5) - (8)].i), rt, irr, SPO_REGION);
		  }
    break;

  case 241:

/* Line 1806 of yacc.c  */
#line 1781 "./lev_comp.y"
    {
		      add_opvars(splev, "iiiio", (yyvsp[(3) - (7)].crd).x, (yyvsp[(3) - (7)].crd).y,
				 (long)(yyvsp[(7) - (7)].i), (long)(yyvsp[(5) - (7)].i), SPO_ALTAR);
		  }
    break;

  case 242:

/* Line 1806 of yacc.c  */
#line 1788 "./lev_comp.y"
    {
		      add_opvars(splev, "iisio",
				 (yyvsp[(3) - (5)].crd).x, (yyvsp[(3) - (5)].crd).y, (yyvsp[(5) - (5)].map), 2, SPO_GRAVE);
		  }
    break;

  case 243:

/* Line 1806 of yacc.c  */
#line 1793 "./lev_comp.y"
    {
		      add_opvars(splev, "iisio",
				 (yyvsp[(3) - (5)].crd).x, (yyvsp[(3) - (5)].crd).y, (char *)0, 1, SPO_GRAVE);
		  }
    break;

  case 244:

/* Line 1806 of yacc.c  */
#line 1798 "./lev_comp.y"
    {
		      add_opvars(splev, "iisio",
				 (yyvsp[(3) - (3)].crd).x, (yyvsp[(3) - (3)].crd).y, (char *)0, 0, SPO_GRAVE);
		  }
    break;

  case 245:

/* Line 1806 of yacc.c  */
#line 1805 "./lev_comp.y"
    {
		      add_opvars(splev, "iiio", (long)(yyvsp[(3) - (5)].i), (yyvsp[(5) - (5)].crd).y, (yyvsp[(5) - (5)].crd).x, SPO_GOLD);
		  }
    break;

  case 246:

/* Line 1806 of yacc.c  */
#line 1811 "./lev_comp.y"
    {
		      add_opvars(splev, "iisio",
				 (yyvsp[(3) - (7)].crd).x, (yyvsp[(3) - (7)].crd).y, (yyvsp[(7) - (7)].map), (long)(yyvsp[(5) - (7)].i), SPO_ENGRAVING);
		  }
    break;

  case 248:

/* Line 1806 of yacc.c  */
#line 1819 "./lev_comp.y"
    {
			(yyval.i) = - MAX_REGISTERS - 1;
		  }
    break;

  case 251:

/* Line 1806 of yacc.c  */
#line 1827 "./lev_comp.y"
    {
			(yyval.i) = - MAX_REGISTERS - 1;
		  }
    break;

  case 254:

/* Line 1806 of yacc.c  */
#line 1835 "./lev_comp.y"
    {
			(yyval.map) = (char *) 0;
		  }
    break;

  case 256:

/* Line 1806 of yacc.c  */
#line 1842 "./lev_comp.y"
    {
			(yyval.map) = (char *) 0;
		  }
    break;

  case 257:

/* Line 1806 of yacc.c  */
#line 1848 "./lev_comp.y"
    {
			int token = get_trap_type((yyvsp[(1) - (1)].map));
			if (token == ERR)
				yyerror("Unknown trap type!");
			(yyval.i) = token;
			Free((yyvsp[(1) - (1)].map));
		  }
    break;

  case 259:

/* Line 1806 of yacc.c  */
#line 1859 "./lev_comp.y"
    {
			int token = get_room_type((yyvsp[(1) - (1)].map));
			if (token == ERR) {
				yywarning("Unknown room type!  Making ordinary room...");
				(yyval.i) = OROOM;
			} else
				(yyval.i) = token;
			Free((yyvsp[(1) - (1)].map));
		  }
    break;

  case 261:

/* Line 1806 of yacc.c  */
#line 1872 "./lev_comp.y"
    {
			(yyval.i) = 0;
		  }
    break;

  case 262:

/* Line 1806 of yacc.c  */
#line 1876 "./lev_comp.y"
    {
			(yyval.i) = (yyvsp[(2) - (2)].i);
		  }
    break;

  case 263:

/* Line 1806 of yacc.c  */
#line 1880 "./lev_comp.y"
    {
			(yyval.i) = (yyvsp[(2) - (4)].i) + ((yyvsp[(4) - (4)].i) << 1);
		  }
    break;

  case 266:

/* Line 1806 of yacc.c  */
#line 1888 "./lev_comp.y"
    {
			(yyval.crd).x = (yyval.crd).y = -MAX_REGISTERS-1;
		  }
    break;

  case 269:

/* Line 1806 of yacc.c  */
#line 1898 "./lev_comp.y"
    {
		      (yyval.i) = 0;
		  }
    break;

  case 270:

/* Line 1806 of yacc.c  */
#line 1902 "./lev_comp.y"
    {
		      (yyval.i) = (yyvsp[(2) - (2)].i);
		  }
    break;

  case 275:

/* Line 1806 of yacc.c  */
#line 1914 "./lev_comp.y"
    {
			(yyval.i) = - MAX_REGISTERS - 1;
		  }
    break;

  case 278:

/* Line 1806 of yacc.c  */
#line 1924 "./lev_comp.y"
    {
		      if (!in_function_definition) {
			  if (on_plist == 0)
		                yyerror("No random places defined!");
			  else if ( (yyvsp[(3) - (4)].i) >= on_plist )
				yyerror("Register Index overflow!");
		      }
		      (yyval.crd).x = (yyval.crd).y = - (yyvsp[(3) - (4)].i) - 1;
		  }
    break;

  case 279:

/* Line 1806 of yacc.c  */
#line 1936 "./lev_comp.y"
    {
		      if (!in_function_definition) {
			  if (on_olist == 0)
		                yyerror("No random objects defined!");
			  else if ( (yyvsp[(3) - (4)].i) >= on_olist )
				yyerror("Register Index overflow!");
		      }
		      (yyval.i) = - (yyvsp[(3) - (4)].i) - 1;
		  }
    break;

  case 280:

/* Line 1806 of yacc.c  */
#line 1948 "./lev_comp.y"
    {
		      if (!in_function_definition) {
			  if (on_mlist == 0)
		                yyerror("No random monsters defined!");
			  if ( (yyvsp[(3) - (4)].i) >= on_mlist )
				yyerror("Register Index overflow!");
		      }
		      (yyval.i) = - (yyvsp[(3) - (4)].i) - 1;
		  }
    break;

  case 281:

/* Line 1806 of yacc.c  */
#line 1960 "./lev_comp.y"
    {
			if ( (yyvsp[(3) - (4)].i) >= 3 )
				yyerror("Register Index overflow!");
			else
				(yyval.i) = - (yyvsp[(3) - (4)].i) - 1;
		  }
    break;

  case 282:

/* Line 1806 of yacc.c  */
#line 1969 "./lev_comp.y"
    {
		      (yyval.crd) = (yyvsp[(1) - (1)].crd);
		  }
    break;

  case 283:

/* Line 1806 of yacc.c  */
#line 1975 "./lev_comp.y"
    {
			if (check_monster_char((char) (yyvsp[(1) - (1)].i)))
				(yyval.i) = (yyvsp[(1) - (1)].i) ;
			else {
				yyerror("Unknown monster class!");
				(yyval.i) = ERR;
			}
		  }
    break;

  case 284:

/* Line 1806 of yacc.c  */
#line 1986 "./lev_comp.y"
    {
			char c = (yyvsp[(1) - (1)].i);
			if (check_object_char(c))
				(yyval.i) = c;
			else {
				yyerror("Unknown char class!");
				(yyval.i) = ERR;
			}
		  }
    break;

  case 288:

/* Line 1806 of yacc.c  */
#line 2005 "./lev_comp.y"
    {
		      /* by default we just do it, unconditionally. */
		      (yyval.i) = 0;
		  }
    break;

  case 289:

/* Line 1806 of yacc.c  */
#line 2010 "./lev_comp.y"
    {
		      /* otherwise we generate an IF-statement */
		      struct opvar *tmppush2 = New(struct opvar);
		      if (n_if_list >= MAX_NESTED_IFS) {
			  yyerror("IF: Too deeply nested IFs.");
			  n_if_list = MAX_NESTED_IFS - 1;
		      }
		      add_opcode(splev, SPO_CMP, NULL);
		      set_opvar_int(tmppush2, splev->n_opcodes+1);
		      if_list[n_if_list++] = tmppush2;
		      add_opcode(splev, SPO_PUSH, tmppush2);
		      add_opcode(splev, (yyvsp[(1) - (1)].i), NULL);
		      (yyval.i) = 1;
		  }
    break;

  case 292:

/* Line 1806 of yacc.c  */
#line 2031 "./lev_comp.y"
    {
		        if ((yyvsp[(2) - (5)].i) < 0 || (yyvsp[(4) - (5)].i) < 0 || (yyvsp[(2) - (5)].i) >= COLNO || (yyvsp[(4) - (5)].i) >= ROWNO)
		           yyerror("Coordinates out of map range!");
			(yyval.crd).x = (yyvsp[(2) - (5)].i);
			(yyval.crd).y = (yyvsp[(4) - (5)].i);
		  }
    break;

  case 293:

/* Line 1806 of yacc.c  */
#line 2040 "./lev_comp.y"
    {
		      (yyval.lregn).x1 = (yyvsp[(1) - (3)].crd).x;
		      (yyval.lregn).y1 = (yyvsp[(1) - (3)].crd).y;
		      (yyval.lregn).x2 = (yyvsp[(3) - (3)].crd).x;
		      (yyval.lregn).y2 = (yyvsp[(3) - (3)].crd).y;
		      (yyval.lregn).area = 1;
		  }
    break;

  case 294:

/* Line 1806 of yacc.c  */
#line 2050 "./lev_comp.y"
    {
			(yyval.lregn) = (yyvsp[(1) - (1)].lregn);
		  }
    break;

  case 295:

/* Line 1806 of yacc.c  */
#line 2054 "./lev_comp.y"
    {
/* This series of if statements is a hack for MSC 5.1.  It seems that its
   tiny little brain cannot compile if these are all one big if statement. */
			if ((yyvsp[(3) - (10)].i) <= 0 || (yyvsp[(3) - (10)].i) >= COLNO)
				yyerror("Region out of level range (x1)!");
			else if ((yyvsp[(5) - (10)].i) < 0 || (yyvsp[(5) - (10)].i) >= ROWNO)
				yyerror("Region out of level range (y1)!");
			else if ((yyvsp[(7) - (10)].i) <= 0 || (yyvsp[(7) - (10)].i) >= COLNO)
				yyerror("Region out of level range (x2)!");
			else if ((yyvsp[(9) - (10)].i) < 0 || (yyvsp[(9) - (10)].i) >= ROWNO)
				yyerror("Region out of level range (y2)!");
			(yyval.lregn).x1 = (yyvsp[(3) - (10)].i);
			(yyval.lregn).y1 = (yyvsp[(5) - (10)].i);
			(yyval.lregn).x2 = (yyvsp[(7) - (10)].i);
			(yyval.lregn).y2 = (yyvsp[(9) - (10)].i);
			(yyval.lregn).area = 1;
		  }
    break;

  case 296:

/* Line 1806 of yacc.c  */
#line 2074 "./lev_comp.y"
    {
/* This series of if statements is a hack for MSC 5.1.  It seems that its
   tiny little brain cannot compile if these are all one big if statement. */
			if ((yyvsp[(2) - (9)].i) < 0 || (yyvsp[(2) - (9)].i) > (int)max_x_map)
			  yyerror("Region out of map range (x1)!");
			else if ((yyvsp[(4) - (9)].i) < 0 || (yyvsp[(4) - (9)].i) > (int)max_y_map)
			  yyerror("Region out of map range (y1)!");
			else if ((yyvsp[(6) - (9)].i) < 0 || (yyvsp[(6) - (9)].i) > (int)max_x_map)
			  yyerror("Region out of map range (x2)!");
			else if ((yyvsp[(8) - (9)].i) < 0 || (yyvsp[(8) - (9)].i) > (int)max_y_map)
			  yyerror("Region out of map range (y2)!");
			(yyval.lregn).area = 0;
			(yyval.lregn).x1 = (yyvsp[(2) - (9)].i);
			(yyval.lregn).y1 = (yyvsp[(4) - (9)].i);
			(yyval.lregn).x2 = (yyvsp[(6) - (9)].i);
			(yyval.lregn).y2 = (yyvsp[(8) - (9)].i);
		  }
    break;



/* Line 1806 of yacc.c  */
#line 4894 "y.tab.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 2094 "./lev_comp.y"


/*lev_comp.y*/

