/* include/autoconf.h.  Generated from autoconf.hin by configure.  */
/* sys/autoconf/autoconf.hin.  Generated from sys/autoconf/configure.ac by autoheader.  */

#ifndef AUTOCONF_H
#undef AUTOCONF_H
#define AUTOCONF_H

/* Exceptions to autopickup (experimental) */
#undef AUTOPICKUP_EXCEPTIONS

/* Open doors by walking into them */
#undef AUTO_OPEN
#define AUTO_OPEN /**/

/* Blackmarket */
#undef BLACKMARKET
#define BLACKMARKET /**/

/* A BSD like system */
#undef BSD

/* Allow smaller screens */
#undef CLIPPING
#define CLIPPING /**/

/* Compression program */
#undef COMPRESS
#define COMPRESS "/bin/bzip2"

/* Extension of compressed files */
#undef COMPRESS_EXTENSION
#define COMPRESS_EXTENSION ".bz2"

/* Options to pass to the compression program, if any */
#undef COMPRESS_OPTIONS

/* Curses interface */
#undef CURSES_GRAPHICS
#define CURSES_GRAPHICS /**/

/* Unix on win32 */
#undef CYGWIN32

/* The default windowing system */
#undef DEFAULT_WINDOW_SYS
#define DEFAULT_WINDOW_SYS "tty"

/* Pseudo random number device */
#undef DEV_RANDOM
#define DEV_RANDOM "/dev/urandom"

/* Data librarian */
#undef DLB
#define DLB /**/

/* Dummy graphics */
#undef DUMMY_GRAPHICS

/* Number of dumped messages */
#undef DUMPMSGS
#define DUMPMSGS 20

/* Name of character dump file */
#undef DUMP_FN

/* CSS file should be included in the HTML dump */
#undef DUMP_HTML_CSS_EMBEDDED

/* Path to the css dump file */
#undef DUMP_HTML_CSS_FILE

/* Dump an HTML file */
#undef DUMP_HTML_LOG

/* Dumping character stats */
#undef DUMP_LOG
#define DUMP_LOG /**/

/* Dump a text file */
#undef DUMP_TEXT_LOG
#define DUMP_TEXT_LOG /**/

/* Dungeon growth */
#undef DUNGEON_GROWTH
#define DUNGEON_GROWTH /**/

/* Engraving the E-word repels monsters */
#undef ELBERETH
#define ELBERETH /**/

/* Show experience on bottom line */
#undef EXP_ON_BOTL
#define EXP_ON_BOTL /**/

/* Gold is kept on object chains (experimental) */
#undef GOLDOBJ

/* Define to 1 if you have the <curses.h> header file. */
#undef HAVE_CURSES_H
#define HAVE_CURSES_H 1

/* Define to 1 if you have the declaration of `strncmpi', and to 0 if you
   don't. */
#undef HAVE_DECL_STRNCMPI
#define HAVE_DECL_STRNCMPI 0

/* Define to 1 if you have the declaration of `strnicmp', and to 0 if you
   don't. */
#undef HAVE_DECL_STRNICMP
#define HAVE_DECL_STRNICMP 0

/* Define to 1 if you have the `fcntl' function. */
#undef HAVE_FCNTL
#define HAVE_FCNTL 1

/* Define to 1 if you have the <inttypes.h> header file. */
#undef HAVE_INTTYPES_H
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <memory.h> header file. */
#undef HAVE_MEMORY_H
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#undef HAVE_STDINT_H
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#undef HAVE_STDLIB_H
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#undef HAVE_STRINGS_H
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#undef HAVE_STRING_H
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#undef HAVE_SYS_STAT_H
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#undef HAVE_SYS_TYPES_H
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <termcap.h> header file. */
#undef HAVE_TERMCAP_H
#define HAVE_TERMCAP_H 1

/* Define this if you have the tparm function in an included lib. */
#undef HAVE_TPARM
#define HAVE_TPARM 1

/* Define to 1 if you have the <unistd.h> header file. */
#undef HAVE_UNISTD_H
#define HAVE_UNISTD_H 1

/* Use UnNetHack's compression routines */
#undef INTERNAL_COMP

/* Keystone Kops */
#undef KOPS
#define KOPS /**/

/* GNU Linux */
#undef LINUX
#define LINUX /**/

/* Live game progress logfile */
#undef LIVELOGFILE

/* Reporting killing of uniques and ghosts of former players */
#undef LIVELOG_BONES_KILLER

/* Shoutting into the live game logfile */
#undef LIVELOG_SHOUT

/* TTY graphics menu color */
#undef MENU_COLOR
#define MENU_COLOR /**/

/* Use regular expressions */
#undef MENU_COLOR_REGEX
#define MENU_COLOR_REGEX /**/

/* GNU regex is available */
#undef MENU_COLOR_REGEX_GNU
#define MENU_COLOR_REGEX_GNU /**/

/* Posix regex is available */
#undef MENU_COLOR_REGEX_POSIX

/* Microsoft Window's native graphics */
#undef MSWIN_GRAPHICS

/* No void type available */
#undef NOVOID

/* Define to the address where bug reports for this package should be sent. */
#undef PACKAGE_BUGREPORT
#define PACKAGE_BUGREPORT "bhaak@gmx.net"

/* Define to the full name of this package. */
#undef PACKAGE_NAME
#define PACKAGE_NAME "UNNETHACK"

/* Define to the full name and version of this package. */
#undef PACKAGE_STRING
#define PACKAGE_STRING "UNNETHACK 3.5.1"

/* Define to the one symbol short name of this package. */
#undef PACKAGE_TARNAME
#define PACKAGE_TARNAME "unnethack"

/* Define to the version of this package. */
#undef PACKAGE_VERSION
#define PACKAGE_VERSION "3.5.1"

/* Require some questions to be answered with 'yes' instead of 'y' */
#undef PARANOID
#define PARANOID /**/

/* Compare High Score entries by user id instead of user name */
#undef PERS_IS_UID

/* QWERTZ keyboard layout support */
#undef QWERTZ
#define QWERTZ /**/

/* Shuffling order of Elemental Planes */
#undef RANDOMIZED_PLANES
#define RANDOMIZED_PLANES /**/

/* Show elapsed time on bottom line */
#undef REALTIME_ON_BOTL

/* Redo last command */
#undef REDO
#define REDO /**/

/* Special Rogue-like levels */
#undef REINCARNATION
#define REINCARNATION /**/

/* Show score on bottom line */
#undef SCORE_ON_BOTL

/* Succubi/incubi seduction */
#undef SEDUCE
#define SEDUCE /**/

/* Display number of created monsters at the end of game */
#undef SHOW_BORN
#define SHOW_BORN /**/

/* Display extinct monsters at the end of game */
#undef SHOW_EXTINCT
#define SHOW_EXTINCT /**/

/* simple mail dgamelaunch support */
#undef SIMPLE_MAIL

/* Kitchen sinks */
#undef SINKS
#define SINKS /**/

/* TTY graphics status color */
#undef STATUS_COLORS
#define STATUS_COLORS /**/

/* Define to 1 if you have the ANSI C header files. */
#undef STDC_HEADERS
#define STDC_HEADERS 1

/* Ability to ride monsters */
#undef STEED
#define STEED /**/

/* Use strncmpi */
#undef STRNCMPI

/* A System V like system */
#undef SYSV
#define SYSV /**/

/* Using msleep */
#undef TIMED_DELAY
#define TIMED_DELAY /**/

/* Tourist class */
#undef TOURIST
#define TOURIST /**/

/* Console output */
#undef TTY_GRAPHICS
#define TTY_GRAPHICS /**/

/* Allow user-defined mapping from messages to sounds) */
#undef USER_SOUNDS

/* Using Mersenne Twister as RNG */
#undef USE_MERSENNE_TWISTER

/* Fancy mazes */
#undef WALLIFIED_MAZE
#define WALLIFIED_MAZE /**/

/* Log information about running games */
#undef WHEREIS_FILE

/* An MS-Windows system */
#undef WIN32

/* enable wizard mode for the specified user */
#undef WIZARD
#define WIZARD "wizard"

/* X11 graphics */
#undef X11_GRAPHICS

/* More verbose logfile */
#undef XLOGFILE
#define XLOGFILE "xlogfile"

/* Define to 1 if `lex' declares `yytext' as a `char *' by default, not a
   `char[]'. */
#undef YYTEXT_POINTER
#define YYTEXT_POINTER 1

#endif /* AUTOCONF_H */
