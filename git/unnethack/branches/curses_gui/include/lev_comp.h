/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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

/* Line 2068 of yacc.c  */
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



/* Line 2068 of yacc.c  */
#line 299 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


