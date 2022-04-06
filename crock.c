/* Hullo, Emacs (et al), this is -*-C-*- code. Thus, behave! */
#define VERSION "3.13"
/* meryl.csd.uu.se!/home/ida/guest/kpj/a004/crock.c, 1993-03-22 06:38:13 CET,
									kpj
312	Use select() on 4.3BSD systems. */
/* sauron.smilax.zyx.se!C:/usr/local/crock/crock.c 1992-02-05 02:42:46 MET,kpj
311	End of moby update:
|	Merged in support for TOPS-20 Sargasso C compiler. */
/* sauron.smilax.zyx.se!C:/usr/local/crock/crock.c 1992-02-05 02:19:04 MET,kpj
310	Change clear screen sequence to $[2J$[H for ANSI devices. */
/* sauron.smilax.zyx.se!C:/usr/local/crock/crock.c 1992-02-05 02:01:23 MET,kpj
309	Merged in edit from diverging version:
| sauron.smilax.zyx.se!D:/usr/src/crock/crock.c 1990-10-13 04:03:35 CET, kpj
|  25	Make this compile with MicroSoft C. Change code to make MSC happy.
|	Merge and optimize video fiddling on IBM PC.  Less #ifdef's. Handle
|	MSC /Za switch gracefully. */
/* sauron.smilax.zyx.se!R:/src/crock/crock.c 1991-10-08 19:44:06 MET, kpj
308	Started including [partial] X11 support. */
/* remo.smilax.zyx.se!C:/kpj/crock.c 1991-08-28 16:29:08 MDT, kpj
307	GNUDOS: An unholy marriage between GNU and MS/PC/DR-DOS.
	Cannot use BIOS calls.  NARROW is now permanently on for MESSYDOG.
	`-n' does nothing on GNUDOS. DVIDEO can be set for GNUDOS. */
/* sauron.smilax.zyx.se!C:/etc/bin/src/crock/crock.c 1991-08-28 14:35:42 MDT
									kpj
306	Hack attack ends..
	Optimized screen output and cursor movement (need DVIDEO or HASTTYSIZ)
	Sargasso-10 and KCC-20 code updated to handle HASTTYSIZ
	Can use relative addressing only with OPTIMIZER (need to know where
	you are on the screen)
	Try to use the `IBM Extended ASCII' for something useful.
	Microsoft C does not have sleep().  It also rejects add_str() and
	add_character() macros, since their arguments happen to be defined
	with #ifdef ... #endif partly.
	Variable `T1' optimized away
	Argument `-D' sets debugging mode (next argument is file name, or if
	not present or starts with `-', use stderr (rather messy)).
	Understand UNIX form argument: `-abcd' means `-a -b -c -d', etc.
	If debugging, a massive debug output crashes in the debug file
	[really should be possible to enable debug on various features, but
	that's not included `at this time'].
	Moby renaming of rest of variables:
	from		to			from		to
	----		--			----		--
	Exitt()		exitt()			BIOSmode	bios_mode
	Timex()		timex()			VideoOff	video_off
	Sleep()		zleep()			VideoPage	video_page
	ImageMode()	init_world()		VideoSeg	video_seg
	BigNormalMode()	restore_world()		VideoAttr	video_attr
	NormalMode()	restore_modes()		HR		hr
	Locate()	locate()		OldH		old_hour
	real_Locate()	real_locate()		OldM		old_minute
	CrockDraw()	crock_draw()		OldS		ols_second
	UserX()		user_x()		Minute		minute
	Hour		hour			Second		second
	Type		type			Length		length
	Oldhc		old_hpos		OldVC		old_vpos
	Txt		i			Byte		byte
	Hpos[]		save_hpos[]		VPos[]		save_vpos[]
	HIncr[]		h_incr[]		VIncr[]		v_incr[]
	Foo[]		hand_char[]		Hand[]		hand_data[]
	SChar[]		sec_char[]		Cursor		cursor
	real_h_position	real_hpos		real_v_position	real_vpos
	shadow_hpos	virt_hpos		shadow_vpos	virt_vpos
	Pr1meMode	prime_mode		Pr1meSleep	prime_sleep
	Pr1meKbhit	prime_kbhit		erasure_ptr	eras_ptr
	erasure_hpos[]	eras_hpos[]		erasure_vpos[]	eras_vpos[]
	hc		hpos			VC		vpos
	Bottom()	bottom()		T		quadrant
	N		slope		*/
/* sauron.smilax.zyx.se!D:/usr/local/crock/crock.c 1991-08-25 05:21:15 MDT,kpj
   305	Hack attack starts.. */
/* sauron.smilax.zyx.se!D:/usr/local/crock/crock.c 1991-08-13 00:30:15 MDT,kpj
   304	Compilation option NARROW enables code to set 40 character wide screen
	video mode on MS/PC/DR-DOS if `-n' argument specified.  Save old mode
	and restore it at exit. */
/* sauron.smilax.zyx.se!D:/usr/local/crock/crock.c 1991-08-13 00:16:36 MDT,kpj
   303	Display version only when `-v' argument given. */
/* remo.smilax.zyx.se!C:/kpj/crock.c 1991-08-10 18:29:10 MDT, kpj
   302	GCC: function parameters are widened:
	   SHORT (short int)	 to	int
	   UCHAR (unsigned char) to	int
	Change: Locate(), dca(), rca(). */
/* sauron.smilax.zyx.se!B:/crock.c 1991-08-07 23:41:56 MDT, kpj
   301	Display version if "-v" parameter specified. */
/* sauron.smilax.zyx.se!D:/usr/new/src/crock.c 1991-08-05 00:36:32 MDT, kpj
   300	Major munging taking place (version 3.x):
	Documentation of compilation switches to file `crock.doc'.
	Code from anders@ifi.uio.no removed and is no longer present.
	Code from CKN@<some obscure Pr1me somewhere> moved to `crock.pr1'
					and #include'd under #ifdef PR1MEC.
	Additions: Optimize ANSI sequences. */
/* ======================================================================== */
/* kuling:/us/guest/kpj/crock.c,  4-Aug-91 21:43:45,  Edit: kpj@kuling
   30	Write a kbhit() for Berkeley systems, using ioctl(), according to the
	manual.  [It does not work as advertised.] */
/* smaug.smilax.zyx.se!C:/kpj/crock.c 1991-08-03 20:58:16 MDT, kpj
   29	Make this compile with GCC port on MS/PC/DR-DOS under #define GNUDOS.
	GNUDOS is a Unix system with kbhit(). */
/* sauron.smilax.zyx.se!D:/usr/new/src/crock.c 1991-08-02 22:39:08 MDT, kpj
   28	Make this compile with Microsoft C 5.00 under MS/PC/DR-DOS:
	- Same capabilities as Turbo C (prototypes, "void", etc)
	- Text on "#endif" converted to comments.
	- Be explicit about data conversions.
	- Cannot use direct video.
	- Get rid of cursor during execution.
	Turbo C in ANSI mode:
	- Keyword "interrupt" is unknown.
	  #define "interrupt" to nothing ("interrupt" used in <dos.h>)
	- Keyword "far" in unknown, no far pointers can be used.
	  Use peek() and poke() functions instead.
	- Register aliases (_AL, _AX, etc) are unknown.
	  Use int86() instead of direct DOS calls.
	- Get rid of cursor during execution, not just #ifdef DVIDEO.
	General:
	- Bug in ANSI driver fixed.
	- `Byte' is USHORT, not char. */
/* sauron.smilax.zyx.se!D:/usr/new/src/crock.c 1991-08-02 22:35:11 MDT, kpj
   27	Put cursor at left margin when leaving program in ANSI mode. */
/* emil!/home/emil/guest/kpj/a004/crock.c, 1991-07-44 17:12:52,Edit:emil!kpj
   26	SUN-4 has not "const" */
/* emil!/home/emil/guest/kpj/a004/crock.c, 1991-05-33 16:37:44,Edit:emil!kpj
   25	Change FUNNYCHR conditional to default off.  Variable HC
	conflicts with curses/termcap usage, changed to "hc".
	Add NOBSP conditional for the situation when cannot use Backspace
	to move the cursor in ANSI mode. */
/* sauron.smilax.zyx.se!D:/usr/src/crock/crock.c 1990-08-15 09.42.20 CST, kpj
   24	Added direct video memory access for Turbo C, under #ifdef DVIDEO.
	Somewhat faster. */
/* sauron.smilax.zyx.se!D:/usr/src/crock/crock.c 1990-08-15 08.58.25 CST, kpj
   23	Fixed bug from edit #19: SHORT cannot be #define'd as char, since it
	char may or may not be unsigned.  #define SHORT as short. */
/* sauron.smilax.zyx.se!D:/usr/src/crock/crock.c 1990-08-15 08.27.22 CST, kpj
   22	Handle CTRL/BREAK condition as normal exit, under #ifdef CTRLBRK */
/* sauron.smilax.zyx.se!D:/usr/src/crock/crock.c 1990-08-14 21.18.52 CST, kpj
   21	Added prototypes and header files. Don't expect char to be (un)signed.
	No nested comments, please. */
/* Betong.SUB.SU.SE!C:\KPJ\A004\CROCK.C 1989-08-09 15:28:03 kpj
   20	Bug in reversed initial clock picture. */
/* sauron.smilax.zyx.se!D:\PIKLUCKA\CROCK\CROCK.C 1989-05-22 19:54:58 kpj
   19	Make it faster by using SHORT where possible.  On MS-DOS (aka
	PC-DOS) the sleep() just loops until the time have changed; so
	in order to not lose a second here and there we just don't "sleep"
	on these single-process systems. Sigh, what a lossage! */
/* sauron.smilax.zyx.se!D:\PIKLUCKA\CROCK\CROCK.C 1989-05-20 18:02:07 kpj
   18	Merged in Pr1me hacks by ckn under #ifdef PR1MEC
	[Pr1me C hacks by CKN (some guy living in Farsta, Sweden)]
*/
/* AIDA::PS:<SLASK>CROCK.C.4 28-Apr-89 07:35:52 LEBEL.DEMON
   17	Make it run under KCC-20 compiler (again). "\8" was not understood by
	KCC. Use "\b" instead. */
/* sauron.smilax.zyx.se!D:\PIKLUCKA\CROCK\CROCK.C 1989-04-21 22:48:31 EET kpj
   16	Merge in code for reversed clock: REVCLK conditional compilation
	flag adds in code to reverse clock when "-b" parameter given.  The
	terminal code: AMIGA and IBM-PC have ANSI drivers.  For all the rest,
	put the code in ANSI conditionals, and merge in all the drivers for
	various terminals (from edits 1..7): EL1521, TEK4025, VK100 (GIGI). */
/* suadb.dsv.su.se/guest/stud/ar/crock.c 21-Apr-1989 19:00:09 EET, edit by ar
   15	Make this work under VAX BSD 4.2 C compiler. */
/* sauron.smilax.zyx.se!D:\PIKLUCKA\CROCK\CROCK.C 1989-04-20 01:14:50 GMT+0100
									kpj
   14	Optimize code. */
/* sauron.smilax.zyx.se!D:\PIKLUCKA\CROCK\CROCK.C 1989-04-17 23:32:16 GMT+0100
									kpj
   13	Add support for BSD 4.2 Curses package. It looks awful, though. */
/* smilax.smilax.zyx.se!Crock:crock.c 1989-04-15 19:52:34 GMT+0100 kpj
   12	Amiga Aztec/Manx C compiler 3.4a has a bug which makes it hate any
	"const" in the code, and the pre-processor has the idea that it is
	an error to redefine "const" to anything.  Sigh.  Define ESC.
	There is a Draw() and SetSignal() procedures in the Manx/Aztec library
	so we have to rename our procedures to CrockDraw() and CrockSignal()
	to avoid ambiguity. */
/* Smertz!D:\PIKLUCKA\CROCK\CROCK.C 1989-04-15 14:37:15 GMT, kpj
   11	Edit 10 is for SUN4, actually.  Things are done differently in other
	UNIX system.  Parameterize the code. */
/* ifi.uio.no!/svarte/home/anders/c/crock.c,  Tue Apr 11 00:55:21 1989
							edit by: anders */
/* 10	Up an running on UNIX */
/* Smertz!D:\PIKLUCKA\CROCK\CROCK.C 1989-04-10 21:22:04 kpj
   9	Add DCROCK option, to display time in digital "hh:mm:ss" format too */
/* Betong!C:\KPJ\A004\CROCK.C 1989-04-10 17:43:19 kpj
   8	Make it somewhat faster. */
/* Betong!C:\KPJ\A004\CROCK.C 1989-04-10 13:17:19 kpj
   7	Make it work on IBM-PC using Turbo C (rather UNIX-like).
	The UNIX interface not fully ready yet, though. */
/* Athena::Ps:<KPJ-Jaakkola.A004>Crock.C.8 880120-0928,KPJ-Jaakkola */
/* 6	Make program run on TOPS-20 using KCC compiler. */
/* Oden::DSKD:CROCK.C<10,50,A004> 1988-01-19 16:14:08, KPJ @ IBM <10,50> */
/* 5	Sargasso-10 code is excessively slow, so we use extremely kludgey
	assembly hacks and better C code to make it faster. */
/* Oden::DSKD:CROCK.C<10,50,A004> 1988-01-18 21:52:49, KPJ @ GR\N <10,50> */
/* 4	MSTIME returns milliseconds, not 1/100 of seconds. */
/* Oden::DSKD:CROCK.C<10,50,A004> 1988-01-18 17:33:49, KPJ @ IBM <10,50> */
/* 3	Converted more from MIDAS version, which is more C compatible. */
/* Oden::DSKD:CROCK.C<10,50,A004> 1988-01-16 13:03:11, KPJ @ H.HOLE <10,50> */
/* 2	First somewhat working Sargasso-10 version. */
/* Oden::DSKD:CROCK.C<10,50,A004> 1988-01-14 16:12:12, KPJ @ IBM <10,50> */
/* 1	First attempt in converting from AmigaBasic to C. */
/* ====================================================================
   A BASIC version for AMIGA and MS-Dog (both extremely slow) by KPJ.
   MIDAS (for Bottoms-10) version by KPJ.
   Original MIDAS (for ITS) version edit history:
	Original program hacked up by GLS
	10X/20X version hacked by KLH.
	Some 10X modifications done by EAK.
   ====================================================================	*/

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* Shorthand for MS/PC/DR-DOS compilers.				*/

#ifdef	__MSDOS__
#define	MESSYDOG
#endif
#ifdef	MSDOS
#define	MESSYDOG
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* 0.	NOTE:	To make this code compile with the Sargasso C compiler	*/
/*		on the *old* Tops-10 operating system,  NO preprocessor	*/
/*		lines herein may have comments on them,  and NO files	*/
/*		can be #include'd WITHOUT APPROPRIATE #ifdef'S.  This	*/
/*		is true even for <stdio.h>,  which is <stdio.HDR> with	*/
/*		Sargasso-10 C compiler,  a moby loser.			*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* 1.	Here we define what capabilities our *system* has.  We do it to	*/
/*	have less #ifdef's and #endif's in the rest of the program.	*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	SARG10
/* Sargasso-10 C compiler: has nothing, use Tops-10 coding.		*/
/* [306] Use .TRMOP(.TOWID and .TOPSZ) to get screen size.		*/
#define	HASUSERX
#define	HASTTYSIZ
#endif

#ifdef	SARG20
/* Sargasso-20 C compiler: has nothing, use TOPS-20 coding.		*/
#define	HASUSERX
#define	HASTTYSIZ
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	KCC
/* KCC C compiler:  has setbuf(), use TOPS-20 "jsys" package for rest	*/
/* [306]	    has code to get terminal width and height.		*/
#define	HASUSERX
#define	HASSETBUF
#define	HASTTYSIZ
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef __TURBOC__
/* Turbo C on MS/PC/DR-DOS (OS/2 not supported as yet)			*/
/* Has: Un*x format time(), quiet exit(), setbuf() and kbhit()		*/
/* We don't use any signals, it's too complicated.			*/
/* [306] has code to deduce terminal width and height (from video mode)	*/
#define	HASTIME
#define HASEXIT
#define	HASSETBUF
#define	HASKBHIT
#define	HASSLEEP
#define	HASTTYSIZ
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	PR1MEC		
/* Prime C: no setbuf(), various Prime specific code in `crock.pr1'	*/
/* [306] currently no code to get terminal width and height.		*/
#define	HASUSERX
#include "crock.pr1"
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	AMIGA
/* Amiga: either Manx/Aztec C or Lattice C compiler.			*/
/* Manx/Aztec is the default.  Lattice C compiler is untested.		*/

#ifndef MANX
#ifndef	LATTICE
#define	MANX
#endif
#endif

/* Amiga: Manx/Aztec C compiler: has setbuf(), time(), quiet exit()	*/
/*	  No kbhit(), signal(), sleep()					*/
/* [306]  currently no code to get screen width and height.		*/

#ifdef	MANX
#define	HASSETBUF
#define	HASTIME
#define	HASEXIT
#endif

#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	X11
/*	... stuff to define X11 environment ... */
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* Convert various Un*x systems into the `generic' Un*x version to make	*/
/* the code later somewhat less burdened with #ifdef's.			*/

#ifdef	unix
#define UNIX			/* Handle this anomaly			*/
#endif

#ifdef	SUN4
#define	UNIX			/* SUN-4 is a Un*x system		*/
#endif

#ifdef	BSD42
#define	UNIX			/* BSD 4.2 is a Un*x system		*/
#define	BSD			/* [312]				*/
#endif

#ifdef	X11
#define	HASUSERX		/* [313] We use X Window System I/O.	*/
#endif

#ifdef	BSD43
				/* [312] 4.3BSD is a Un*x system	*/
#define	UNIX			/* [312]				*/
#define	BSD			/* [312]				*/
#define	HASUSERX		/* [312]				*/
#define	HASVOID			/* [312] has `void' data type		*/
#endif				/* [312]				*/

#ifdef	GNUDOS
				/* GNU is like Un*x.			*/
/* DJ's GNU cc port to MS/PC/DR-DOS.					*/
/* Has: everything the generic Un*x has, and kbhit().			*/
#define	UNIX
#define	HASKBHIT
#define	HASTTYSIZ

#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	UNIX
/* Generic Un*x: signal(), time(), quiet exit(), setbuf(), sleep()	*/
/*		No kbhit(),  generally.					*/
/* [306]	Currently no code to get screen width and height.	*/
#define	HASSIGNAL
#define	HASTIME
#define	HASEXIT
#define	HASSETBUF
#ifdef	BSD43
/* [312]	4.3BSD uses select() instead of sleep().		*/
#endif
#ifndef	BSD43
#define	HASSLEEP
#endif
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	MSDOS
/* Microsoft C on MS/PC/DR-DOS (OS/2 not supported as yet)		*/
/* Has: Un*x format time(), quiet exit(), setbuf() and kbhit()		*/
/* We don't use any signals, it's too complicated.			*/
/* Like Turbo C, except not ISO C compatible (no __STDC__ defined)	*/
/* [306] has code to deduce screen width and height (from video mode)	*/
#define	HASTIME
#define HASEXIT
#define	HASSETBUF
#define	HASKBHIT
#define	HASSLEEP
#define	HASTTYSIZ
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	HASKBHIT
/* If we have the kbhit() function, we also have user_x() function.	*/
#define	HASUSERX
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* Make sure we can exit the program.					*/

#ifndef	HASEXIT
#ifndef	KCC
#ifndef	SARG20
#ifndef	SARG10
	"error: no code in exitt() -- cannot exit program";	/* bug	*/
#endif
#endif
#endif
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* Make sure we can get current time (hours, minutes, seconds).		*/

#ifndef	HASTIME
#ifndef	KCC
#ifndef	SARG20
#ifndef	SARG10
	"error: no code in timex() -- cannot get time";		/* bug	*/
#endif
#endif
#endif
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* Make sure we can sleep one second.					*/

#ifndef	SARG10
#ifndef	SARG20
#ifndef	KCC			/* TOPS-20 special code does DISMS%	*/
#ifndef	HASSLEEP		/* sleep()				*/
#ifndef	PR1MEC			/* Prime code has own sleep()		*/
#ifndef	AMIGA			/* AMIGA uses Delay()			*/
#ifndef	BSD43			/* [312] 4.3BSD uses select()		*/
	"error: no code in zleep() -- cannot sleep 1 second";	/* bug	*/
#endif				/* [312]				*/
#endif
#endif
#endif
#endif
#endif
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* Make sure we can detect user input.					*/

#ifdef	HASUSERX
#ifndef	BSD43
#ifndef	PR1MEC
#ifndef	HASKBHIT
#ifndef	KCC
#ifndef	SARG20
#ifndef	SARG10
	"error: no code in user_x() -- cannot detect input";	/* bug	*/
#endif
#endif
#endif
#endif
#endif
#endif
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* Check if main() has arguments.					*/

#ifdef	DCROCK
#define	ARGV
#else
#ifdef	REVCLK
#define	ARGV
#else
#ifdef	VERSION
#define	ARGV
#else
#ifdef	NARROW			/* [304]				*/
#define	ARGV			/* [304]				*/
#else
#ifdef	X11			/* [313]				*/
#define	ARGV			/* [313]				*/
#else				/* [313]				*/
/* don't #define ARGV */
#endif				/* [313]				*/
#endif				/* [304]				*/
#endif
#endif
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* Check if can get (terminal) screen width (in number of characters)	*/
/* and height (in lines).  We need this to use the OPTIMIZER code, if	*/
/* not DVIDEO is set.							*/

#ifndef	DVIDEO
#ifndef	HASTTYSIZ
#ifdef	OPTIMIZER
#undef	OPTIMIZER
	"error(OPTIMIZER): no code to get terminal screen size";
#endif
#endif
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	MSDOS
				/* Microsoft C 5.00 and later */
#define	sleep(x)
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* 3.	The `crock' program can use various types of terminal equipment	*/
/*	and we define here what kind of terminal driver (if any) we are	*/
/*	to generate code for.  See the file `crock.doc' for details.	*/

#ifdef	X11
/* `X Window System, Version 11' package has own drivers.		*/
#define	HASDRV
#endif

#ifdef	CURSES
/* The `curses' package (requires `curses' and `termcap' packages).	*/
#define	HASDRV
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* Various forms of ANSI compatible terminal drivers supported.		*/

#ifdef	VT100
				/* VT100: DIGITAL VT100 terminal.	*/
#define	ANSI
#endif
/* .................................................................... */
#ifdef	VK100
				/* VK100: DIGITAL VK100 (GIGI) terminal. */
#define	ANSI
#endif
/* .................................................................... */
#ifdef	AMIGA
			/* AMIGA: Commodore AMIGA personal computer.	*/
#define	ANSI
#endif
/* .................................................................... */
/* IBM Personal Computer and clones (and GNUDOS).			*/
/* If not DVIDEO (direct video memory write) enabled,  we default to an	*/
/* ANSI.SYS driver.  This has an impact to how the backup store of the	*/
/* optimized screen output will be implemented.  DVIDEO enables us to	*/
/* let the hardware be our backup store: the video RAM.			*/

#ifdef	DVIDEO
					/* Direct video memory writes. */
#define	HASDRV

#else
					/* Assume ANSI driver loaded. */
#ifdef	__TURBOC__
#define	ANSI
#endif

#ifdef	MSDOS
#define	ANSI
#endif

#ifdef	GNUDOS
#define	ANSI
#endif

#endif

#ifdef	ANSI
#define	TRMNAM	"ANSI (e.g. VT100 or VK100/GIGI)"
#define	TRMTYP	"ANSI"
#define	HASDRV
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* Tektronix 4025 terminal driver.					*/
/* Commands start with a `command character' and different sites have	*/
/* different ones,  so we parametrize it:  TEKCHR (CTRL/Backslash by	*/
/* default).								*/

#ifdef	TE4025
#define	TEK425
#endif

#ifdef	TEK425
#define	TRMNAM	"Tektronix 4025"
#define	TRMTYP	"TE4025"
#define	HASDRV

#ifndef	TEKCHR
#define	TEKCHR	'\034'
#endif

#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* Elite 1520 or Elite 1521.						*/

#ifdef	EL1520
#define	EL1521
#endif

#ifdef	EL1521
#define	HASDRV
#define	TRMNAM	"Elite 1520/1521"
#define	TRMTYP	"EL1521"
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* If no terminal driver defined,  no terminal driver code generated.	*/

#ifndef	HASDRV
	"error: no terminal driver specified";	/* generate an error	*/
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* 4.	System dependent definitions and header files.			*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifndef	SARG10
#ifndef	SARG20
#include <stdio.h>	/* Loaded by all, except Sargasso-10 (sigh..)	*/
#endif
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	SARG10
			/* Sargasso-10 is a total loser			*/
#include <stdio.HDR>
			/* Make Un*x-flavored I/O on Bottoms-10		*/
#define _UNIXCON
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	SARG20
			/* Sargasso-20 is a total loser, too		*/
#include <TOPS20.HDR>
#define	_UNIXCON
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef KCC
#include <jsys.h>	/* KCC on TOPS-20: use `jsys()' system calls	*/
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	GNUDOS
#include <pc.h>		/* DJ's GCC port: Declare kbhit()		*/
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	SUN4
#include <sys/types.h>		/* Declare time_t, etc.			*/
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	BSD
				/* [412] BSD of some kind		*/
#ifdef LINUX
#include <linux/types.h>
#define _SYS_TYPES_H
#include <bsd/sgtty.h>
#else
#include <sys/types.h>		/* Declare time_t, etc.			*/
#include <sgtty.h>		/* Declare FIONREAD, etc.		*/
#endif
#endif
#ifdef	BSD43
#include <sys/time.h>		/* [412] Declare select()		*/
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	__STDC__
				/* ISO C compilers:			*/
#include <stdlib.h>		/* Declare exit(),  etc.		*/
#include <string.h>		/* Declare strcmp(), etc.		*/
#ifdef	__TURBOC__		/* (Turbo C in ISO mode:)		*/
#define	interrupt		/* Disable "interrupt"			*/
#include <dos.h>		/* Declare inregs, outregs, etc.	*/
#include <conio.h>		/* Declare kbhit(),  etc.		*/
#define	_AHin	 inregs.h.ah
#define	_ALin	 inregs.h.al	/* [304]				*/
#define	_AXin	 inregs.x.ax
#define _BHin	 inregs.h.bh
#define	_CHin	 inregs.h.ch
#define	_CLin	 inregs.h.cl
#define	_CXin	 inregs.x.cx
#define	_DHin	 inregs.h.dh
#define	_DLin	 inregs.h.dl
#define	_AHout	outregs.h.ah
#define	_ALout	outregs.h.al	/* [304]				*/
#define	_BHout	outregs.h.bh
#define	_CHout	outregs.h.ch
#define	_CXout	outregs.x.cx
#define	_DHout	outregs.h.dh
#define	_DLout	outregs.h.dl
#define	_int(x) int86(x,&inregs,&outregs)
#endif
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	__TURBOC__
#ifndef	__STDC__		/* (Turbo C not in ISO mode:)		*/
#include <dos.h>		/* Declare inregs, outregs, etc.	*/
#include <conio.h>		/* Declare kbhit(),  etc.		*/
#include <stdlib.h>		/* Declare exit(),  etc.		*/
#include <string.h>		/* Declare strcmp(), etc.		*/
#define	_AHin	_AH
#define	_ALin	_AL		/* [304]				*/
#define	_AHout	_AH
#define	_ALout	_AL		/* [304]				*/
#define	_AXin	_AX
#define	_BHin	_BH
#define	_BHout	_BH
#define	_CHin	_CH
#define	_CHout	_CH
#define	_CLin	_CL
#define	_CXin	_CX
#define	_CXout	_CX
#define	_DHin	_DH
#define	_DHout	_DH
#define	_DLin	_DL
#define	_DLout	_DL
#define	_int(x)	geninterrupt(x)
#endif
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	MSDOS
				/* Microsoft C:				*/
#include <conio.h>		/* Declare kbhit(),  etc.		*/
#include <stdlib.h>		/* Declare exit(),  etc.		*/
#include <string.h>		/* Declare strcmp(), etc.		*/
#include <dos.h>		/* Declare inregs, outregs, etc.	*/
#define	_AHin	 inregs.h.ah
#define	_ALin	 inregs.h.al	/* [304]				*/
#define	_AXin	 inregs.x.ax
#define _BHin	 inregs.h.bh
#define	_CHin	 inregs.h.ch
#define	_CLin	 inregs.h.cl
#define	_CXin	 inregs.x.cx
#define	_DHin	 inregs.h.dh
#define	_DLin	 inregs.h.dl
#define	_AHout	outregs.h.ah
#define	_ALout	outregs.h.al	/* [304]				*/
#define	_BHout	outregs.h.bh
#define	_CHout	outregs.h.ch
#define	_CXout	outregs.x.cx
#define	_DHout	outregs.h.dh
#define	_DLout	outregs.h.dl
#define	_int(x) int86(x,&inregs,&outregs)
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	X11
#include <X11/Xlib.h>		/* [313] declare interface functions	*/
#ifdef	ISONESS			/* [313]				*/
#include <stdlib.h>		/* [313] declare getenv()		*/
#else				/* [313]				*/
extern char* getenv();		/* [313] we need these			*/
#endif
#include <pwd.h>		/* [313] declare getpwuid()		*/
#ifdef	NeedFunctionPrototypes	/* [313] need function prototypes?	*/
#define	ISONESS			/* [313] yes, turn on ISOness		*/
#endif				/* [313]				*/
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	HASSIGNAL
#include <signal.h>		/* Declare signal(), etc.		*/
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	HASTIME
#include <time.h>		/* Declare time(),  etc.		*/
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	CURSES
#include <curses.h>		/* Declare `curses' package.		*/
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* See if FUNNYCHR is not necessary: MESSYDOG uses "IBM Extended ASCII"	*/
/* and AMIGA uses ISO 8859-1 character sets.				*/

#ifdef	GNUDOS
#undef	FUNNYCHR
#endif

#ifdef	__MSDOS__
#undef	FUNNYCHR		/* MS/PC/DR-DOS				*/
#endif

#ifdef	MSDOS
#undef	FUNNYCHR		/* MS/PC/DR-DOS				*/
#endif

#ifdef	AMIGA
#undef	FUNNYCHR		/* AMIGA				*/
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* General data type declarations.					*/

#define	SHORT	short int
#define	UCHAR	unsigned char
#define	ANYTHING 42
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* See if want rca() routine.						*/
/* See if want dca() routine.						*/

#ifdef	ANSI
#ifdef	OPTIMIZER
#define	WANT_RCA
#define	MAXRIGHT 4
#endif
#define	OFFSET 1
#define	WANT_DCA
#endif

#ifdef	TEK425
#ifdef	OPTIMIZER
#define	WANT_RCA
#define	MAXRIGHT 6
#endif
#define	WANT_DCA
#endif

#ifdef	CURSES
#undef	WANT_RCA
#undef	WANT_DCA
#endif

#ifdef	DVIDEO
#undef	WANT_RCA
#undef	WANT_DCA
#endif

#ifdef	EL1521
#undef	WANT_RCA
#define	WANT_DCA
#endif

#ifndef	OFFSET
#define	OFFSET 0
#endif

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* 5.	Prototypes.							*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifndef	ISONESS
				/* [313] need function prototypes?	*/
#ifdef	__STDC__
#define	ISONESS			/* ISO C has prototypes.		*/
#endif

#ifdef	MESSYDOG
#define	ISONESS			/* Microsoft C and Turbo C,  too	*/
#endif

#ifdef	GCC
#define	ISONESS			/* GNU cc				*/
#endif
#endif

#ifdef	ISONESS
#define	VOID	void
#define	VOIDARG	void
#ifndef	CONST
#define	CONST	const
#endif
#define	SIGNAL	void
#define AND ,
#define DEFUN(F, L, P) F(P)
#define EXFUN(F, P) F P
#else
#ifdef	HASVOID
#ifndef VOID
#define	VOID	void
#endif
#else
#define	VOID	int
#endif
#define	VOIDARG	/* nothing */
#define	CONST	/* nothing */
#ifndef	SIGNAL
				/* [312] */
#define	SIGNAL	int
#endif
#define AND ;
#define DEFUN(F, L, P) F L P ;
#define EXFUN(F, P) F()
#endif

VOID EXFUN(exitt,(VOIDARG));		/* non-printing process termin.	*/
VOID EXFUN(timex,(SHORT *, SHORT *, SHORT *));	/* wall-clock time */
VOID EXFUN(zleep,(VOIDARG));		/* sleep one second		*/
VOID EXFUN(init_world,(VOIDARG));	/* initialize world		*/
VOID EXFUN(restore_world,(VOIDARG));	/* [306] restore everything	*/
VOID EXFUN(restore_modes,(VOIDARG));	/* restore original modes	*/
SIGNAL EXFUN(doquit,(VOIDARG));		/* [312] normal exit		*/

#ifdef	WANT_DCA
VOID EXFUN(dca,(int, int));		/* [302] direct cursor addr.g	*/
#endif
#ifdef	WANT_RCA
VOID EXFUN(rca,(int, int));		/* [302] relative screen move	*/
#endif

#ifdef	OPTIMIZER
#define	INTERFACE
#endif

#ifndef	CURSES
#define	INTERFACE
#endif

#ifdef	X11
#define	INTERFACE	/* [313] Use real_clear(), etc. routines.	*/
#undef	OPTIMIZER	/* [313] No optimizer code.			*/
#undef	CURSES		/* [313] No curses.				*/
#undef	DVIDEO		/* [313] No direct video access.		*/
#endif

#ifdef	CURSES
#ifdef	OPTIMIZER
int EXFUN(backup_store,(int,int));	/* [306] read backup store	*/

#define	real_addch(x)	 addch(x)
VOID EXFUN(locate,(int,int));	/* [306] interface routine to move()	*/
VOID EXFUN(add_str,(char *));	/* [306] interface routine to addstr()	*/
VOID EXFUN(real_clear,(VOIDARG)); /* [306] interface routine to clear()	*/
VOID EXFUN(add_character,(int));/* [306] interface routine to addch()	*/
VOID EXFUN(refresh_screen,(VOIDARG)); /* [306] interface routine to refresh()*/
VOID EXFUN(print_word,(char *,SHORT));	/* [306] interface to printw()	*/
#else
	/* not OPTIMIZER */

#define	add_str		 addstr
#define	locate(x,y)	 move((x)-1,(y)-1)
#define	real_clear()	 clear()
#define	add_character	 addch
#define	refresh_screen() refresh()
#define	print_word	 printw
#endif
	/* not OPTIMIZER */
#else
	/* not CURSES */

#ifdef	OPTIMIZER

int EXFUN(backup_store,(int,int));	/* [306] read backup store	*/
int EXFUN(add_erase,(int,int));		/* [306] add erasure table entry */
VOID EXFUN(del_erase,(int));	/* [306] delete erasure table entry	*/

#ifdef	DVIDEO
VOID EXFUN(real_addch,(int));	/* [306] write character to screen	*/
#else
#define	real_addch	putchar
#endif
VOID EXFUN(add_str,(char *));	/* [306] write string at cursor		*/
VOID EXFUN(add_character,(int)); /* [306] write character at cursor	*/
VOID EXFUN(refresh_screen,(VOIDARG));	/* [306] refresh screen		*/
VOID EXFUN(print_word,(char *,int));	/* [306] format at cursor	*/
/* locate(): see below */	/* [306] virtual cursor movement	*/
VOID EXFUN(real_locate,(int,int)); /* [306] physical cursor movement	*/
#else
	/* not OPTIMIZER */
#ifdef	X11
VOID EXFUN(add_character,(int));/* [313] We use these to do the I/O.	*/
VOID EXFUN(add_str,(char *));	/* [313] . . .				*/
#else
#ifdef	MSDOS
VOID EXFUN(add_character,(int))	/* [306] Microsoft C barfs on macro	*/
VOID EXFUN(add_str,(char *));	/* [306] . . .				*/
#else
#define	add_str(x)	 printf("%s",x)
#define	add_character	 putchar
#endif
#endif

#define	refresh_screen()
#define print_word	 printf
#define	locate		 real_locate
#endif

VOID EXFUN(locate,(int,int));	/* [306] virtual cursor movement	*/
VOID EXFUN(real_clear,(VOIDARG));/* [306] clear screen, handle optimizer */
#endif

VOID EXFUN(crock_draw,(VOIDARG));	/* super-hairy hand drawer	*/

#ifdef	HASUSERX
int EXFUN(user_x,(VOIDARG));		/* user input checker		*/
#endif
VOID EXFUN(begin,(VOIDARG));		/* initialize, paint clock	*/

#ifdef	ARGV
char *progname;				/* program name			*/
VOID EXFUN(main,(int, char*[]));	/* reversed clock: parameters	*/
#else
VOID EXFUN(main,(VOIDARG));		/* normal clock: no parameters	*/
#endif

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* 6.	System dependent variable area.					*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	SARG20
				/* TOPS-20 stuff:			*/
   int ccoc1;			/* CCOC, word 1				*/
   int ccoc2;			/* CCOC, word 2				*/
#endif
#ifdef	KCC
				/* TOPS-20 stuff:			*/
#ifndef	OPTIMIZER
   int te_width;		/* [306] Terminal width			*/
#endif
   int ac[5];			/* jsys() ackumulators: AC 1 .. 5	*/
   int ccoc1;			/* CCOC, word 1				*/
   int ccoc2;			/* CCOC, word 2				*/
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	GNUDOS
   int te_width;		/* [307] screen width			*/
   int video_off;		/* [307] video memory address offset	*/
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/

#ifdef	MESSYDOG
				/* BIOS calls stuff:			*/
#ifdef	MSDOS
   union REGS  inregs;		/*  input registers to int86()		*/
   union REGS outregs;		/* output registers to int86()		*/
#endif
#ifdef	__STDC__
   union REGS  inregs;		/*  input registers to int86()		*/
   union REGS outregs;		/* output registers to int86()		*/
#endif
   unsigned char oldmode;	/* [306] old video mode			*/
#ifdef	NARROW			/* [304]				*/
   int bios_mode;		/* [304] current BIOS video mode	*/
#else				/* [304]				*/
#ifdef	DVIDEO			/* [304]				*/
   int bios_mode;		/* [304] current BIOS video mode	*/
#endif				/* [304]				*/
#endif				/* [304]				*/
#ifdef	DVIDEO			/* (direct video memory access:)	*/
   int video_off;		/* [306] video memory address offset	*/
   int video_seg;		/* video memory address segment	part	*/
#endif
   SHORT video_page;		/* video page				*/
   unsigned int cursor;		/* cursor start,,stop			*/
   SHORT video_attr;		/* video attributes to use		*/
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* 7.	Variables which are not system dependent.			*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#define	SPACE	' '
#define	ESC	'\033'

#ifdef	DEBUG
   FILE *debug = NULL;		/* [306] debug file			*/
#endif
#ifdef	OPTIMIZER
   SHORT eras_ptr;		/* [306] erasure pointer		*/
   SHORT real_hpos;		/* [306] real horizontal position	*/
   SHORT real_vpos;		/* [306] real vertical position		*/
   SHORT virt_hpos;		/* [306] virtual horizontal position	*/
   SHORT virt_vpos;		/* [306] virtual vertical position	*/
   int te_width;		/* [306] terminal width			*/
   int te_height;		/* [306] terminal height		*/

#ifndef	DVIDEO
   char **videomem;		/* [306] video memory pointer		*/
#endif
#else
#ifdef	MESSYDOG
   int te_width;		/* [306] terminal width			*/
   int te_height;		/* [306] terminal height		*/
#endif
#ifdef	DVIDEO
   SHORT virt_hpos;		/* [306] virtual horizontal position	*/
   SHORT virt_vpos;		/* [306] virtual vertical position	*/
#endif
#ifdef	X11

#endif
#endif				/* [306]				*/

#ifdef	DCROCK
   UCHAR dcrock = 0;		/* "hh:mm:ss"-P				*/
#endif
#ifdef	REVCLK
   UCHAR bkward = 0;		/* backward-P (true when reversed clock) */
#endif
#ifdef	VERSION
   UCHAR version = 0;		/* version-P				*/
#endif

#ifdef	NARROW
#define	NARRVAR
#else
#ifdef	MESSYDOG
#define	NARRVAR
#endif
#ifdef	GNUDOS
#define	NARRVAR
#endif
#endif

#ifdef	NARRVAR
   UCHAR narrow = 0;		/* [306] narrow-P			*/
				/* [306] =1: `-n', =2:narrow screen	*/
#endif
#undef	NARRVAR

#ifdef	DCROCK
   UCHAR hr;			/* unscaled hour */
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
   SHORT old_hour;		/* old hour (-1: no old hour) */
   SHORT old_minute;		/* old minute (-1: no old minute) */
   SHORT old_second;		/* old second (-1: no old minute) */
#define	UNDEF	-1
   SHORT hour;			/* current hour (0:23) */
   SHORT minute;		/* current minute (0:59) */
   SHORT second;		/* current second (0:59) */
   SHORT i;			/* loop index */
#ifdef	OPTIMIZER
#ifndef	DVIDEO
   SHORT j;			/* [312] loop index too */
#endif
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
   /* Parameters to crock_draw() */

   SHORT T;			/* "Time" (0:59) to draw */
   UCHAR type;			/* type (0:erase,1:hour,2:minute,3:second) */
#define	ERASE	0
#define	HOUR	1
#define	MINUTE	2
#define	SECOND	3
   UCHAR length;		/* hand length */
   UCHAR Z2;			/* Start position in POS[] (0:none) */
   SHORT Z;			/* Negative length of table */
   SHORT A;

   SHORT old_hpos;		/* Old horizontal cursor position (1:nn)
				   (or -1 when not initialized) */
   SHORT old_vpos;		/* Old vertical cursor position (1:nn)
				   (or -1 when not initialized) */
   SHORT TT;

   UCHAR byte;			/* byte value read from hand_data[]	*/
   UCHAR Index2;		/* Loop index in Draw() */
#define	POSMAX 30
   SHORT save_hpos[POSMAX];	/* horizontal positions (-1: unused) */
   SHORT save_vpos[POSMAX];	/* vertical positions (-1:unused) */
#ifdef	OPTIMIZER
   SHORT eras_hpos[POSMAX];	/* [306] erased horizontal positions	*/
   SHORT eras_vpos[POSMAX];	/* [306] erased horizontal positions	*/
#endif

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* 8.	Constant drawing data						*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#define	STARV	12
#define STARH	21
#ifdef	MESSYDOG
			/* [306] `\004' is a diamond */
#define	CENTRE	'\004'
#else
#define	CENTRE	'*'
#endif

#ifdef	DCROCK
#define	DCVPOS  12
#define	DCHPOS	50
#define	NCVPOS	23
#define	NCHPOS	1
#endif

   CONST SHORT v_incr[]= {-1, 1, 1,-1};	/* signs of vertical increments	*/
   CONST SHORT h_incr[]= { 1, 1,-1,-1};	/* signs of horiz. increments	*/
   CONST char hand_char[] =		/* erase, hour, minute characters */
#ifdef	MESSYDOG
			/* [306] `\001' is black happy face */
			/* [306] `\002' is white happy face */
	   " \002\001";
#else
	   " @o";
#endif
   CONST char *hand_data[] = {		/* second's drawing data */
#ifdef	NARROW					/* [304] */
       "100100100100100100005100100100006100008007",
       "100100102110100100005102110100006100008007",
       "100102110102110102005110102110006100008007",
       "100112112110102110005102110102006110008007",
       "112112110102112110005102112112006110008007",
       "112112112112112112005112112112006112008007",
       "112112112114013112112005114013112006112008114007",
       "114013112114013112114013005112114013112006114008013007",
       "013114013114013114013114013114005013114013114006013008114007",
       "013112013114013114011013114011013005112114011013114006011008013007",
       "011013114011013114011013114011013005114011013114011013006114008007",
      "011013114011011013114011011013114005011011013114011011006013008114007",
      "011011013114014011011013114014011005011013114014011011006013008114007",
      "011011011013013114014011011011013005013114014011011011006013008013007",
      "011011011011013013013013114014014005014011011011011013006013008013007",
      "011011011011011011011011011011011005011011011011011011006011008011007"
#else							/* [304] */
       "100100100100100100005100100100006100007",
       "100100102110100100005102110100006100007",
       "100102110102110102005110102110006100007",
       "100112112110102110005102110102006110007",
       "112112110102112110005102112112006110007",
       "112112112112112112005112112112006112007",
       "112112112114013112112005114013112006112114007",
       "114013112114013112114013005112114013112006114013007",
       "013114013114013114013114013114005013114013114006013114007",
       "013112013114013114011013114011013005112114011013114006011013007",
       "011013114011013114011013114011013005114011013114011013006114007",
      "011013114011011013114011011013114005011011013114011011006013114007",
      "011011013114014011011013114014011005011013114014011011006013114007",
      "011011011013013114014011011011013005013114014011011011006013013007",
      "011011011011013013013013114014014005014011011011011013006013013007",
      "011011011011011011011011011011011005011011011011011011006011011007"
#endif
    };

/* Normally, `crock' will use vertical bar (|) and backslash (\) when	*/
/* painting the second's hand.  However,  if you are using a "national"	*/
/* version of 7-bit ASCII,  these characters may be inappropriate.  For	*/
/* example,  they are o-with-umlaut and O-with-umlaut when using the	*/
/* Swedish national forms of ASCII,  SIS D47 and SIS E47.  To fix this,	*/
/* #define FUNNYCHR,  and `crock' will use greater-than and exclamation	*/
/* instead of backslash and vertical bar.				*/

   CONST char *sec_char[] = {	/* second's drawing characters */
#ifdef	FUNNYCHR		/* default: can't use "|\" at all	*/
        "!-/',",
	"!->,'",
	"!-/,'",
	"!->',"
#else
#ifdef	MESSYDOG
/*
 *	Useless hack to use `IBM Extended ASCII' for something:
 *		`\304' is like `-' but longer
 */
        "|\304/',",		/* [306] */
	"|\304\\,'",		/* [306] */
	"|\304/,'",		/* [306] */
	"|\304\\',"		/* [306] */
#else
        "|-/',",
	"|-\\,'",
	"|-/,'",
	"|-\\',"
#endif
#endif
   };

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* 9.	Non-terminal associated functions.				*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* exitt() returns to caller (operating system or superior fork) with	*/
/*	   no output.  For system which do not slaughter forks which	*/
/*	   exit,  exitt() may return and continue.			*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/

VOID exitt(){
#ifdef	SARG10
	static int exit_code[] = {
	   (0047<<27)|(001<<23)|012,		/* EXIT  1,		*/
	   (0263<<27)|(017<<23)			/* POPJ  17,		*/
	};
	static int (*exit_ptr)() = exit_code;

	(*exit_ptr)();				/* EXIT	1,		*/
#endif
#ifdef	SARG20
	static int exit_code[] = {
	   (0104<<27)|0170,			/* HALTF%		*/
	   (0263<<27)|(017<<23)			/* POPJ  17,		*/
	};
	static int (*exit_ptr)() = exit_code;

	(*exit_ptr)();				/* HALTF%		*/
#endif
#ifdef	KCC
	jsys(HALTF);				/* HALTF%		*/
#endif
#ifdef	HASEXIT
	exit(0);			/* normal process termination	*/
#endif
}
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* timex()	computes wall-clock time, and returns it to caller.	*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
VOID timex(h,m,s) SHORT *h,*m,*s;{	/* compute wall-clock time */
#ifdef	HASTIME
	time_t		timer;		/* internal version */
	struct	tm *	timep;		/* exploded version */
					/* [312] */
	(VOID) time(&timer);		/* seconds since Jan 1, 1970 GMT */
	timep = localtime(&timer);	/* explode hour minute second */
	*h = (SHORT) timep->tm_hour;	/* hour */
	*m = (SHORT) timep->tm_min;	/* minutes */
	*s = (SHORT) timep->tm_sec;	/* seconds */
#endif
#ifdef	SARG10
	int	i;
	int	j;

#define	MSTIME	023
	i  = calli(MSTIME,0)/1000;	/* read time of day in ms	*/
					/* convert to seconds		*/
	j  = i / 60;			/* compute minutes		*/
	*s = i - 60*j;			/* return seconds in minute	*/
	j  = (i = j) / 60;		/* compute hours		*/
	*m = i - 60*j;			/* return minutes in hour	*/
	j  = (i = j) /100;		/* extract hours		*/
	*h = i -100*j;			/* return hours			*/
#endif
#ifdef	SARG20
	int	i;
	int	j;
	static int odcnv[] = {
	   (0474<<27)|(002<<23),		/* SETO	 2,		*/
	   (0400<<27)|(004<<23),		/* SETZ  4,		*/
	   (0104<<27)|0222,			/* ODCNV%		*/
	   (0202<<27)|(004<<23)|(1<<22)|(017<<18)|0777777,
					        /* MOVEM 4,@-1(17)	*/
	   (0263<<27)|(017<<23)			/* POPJ  17,		*/
	};
	static int (*odcnv_ptr)() = odcnv;

	(*odcnv_ptr)(&i);			/* ODCNV%		*/
	i = i & 0777777;	/* extract time since midnight, seconds	*/
	j  = i / 60;		/* compute minutes			*/
	*s = i - 60*j;		/* return seconds			*/
	i = j;			/* shuffle				*
	j  = i / 60;		/* compute hours			*/
	*m = i - 60*j;		/* return minutes			*/
	i = j;			/* shuffle				*
	j = i /100;		/* extract hours			*/
	*h = i -100*j;		/* return hours				*/
#endif
#ifdef	KCC
	int	i;
	int	j;

	ac[2] = -1;		/* 2/	-1	(current date and time)	*/
	ac[4] = 0;		/* 4/	0	(no flags)		*/
	jsys(ODCNV,ac);		/* ODCNV%	(get time)		*/
				/* 4/		(flags,,time)		*/
	i  = ac[4] & 0777777;	/* extract time since midnight, seconds	*/
	j  = i / 60;		/* compute minutes			*/
	*s = i - 60*j;		/* return seconds			*/
	j  = (i = j) / 60;	/* compute hours			*/
	*m = i - 60*j;		/* return minutes			*/
	j = (i = j) /100;	/* extract hours			*/
	*h = i -100*j;		/* return hours				*/
#endif
}
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* zleep()	put current process into inactivity for 1 second.	*/
/*		(except on MS/PC/DR-DOS, where sleep() just loops until	*/
/*		 one second has elapsed)				*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
VOID zleep(){
#ifdef	PR1MEC
    prime_sleep();			/* PR1ME special		*/
#endif
#ifdef	HASSLEEP
    sleep(1);				/* sleep 1 second		*/
#endif
#ifdef	AMIGA
    Delay(50);				/* sleep 50 tics = 1 second	*/
#endif
#ifdef	KCC
    ac[1] = 1;				/* 1/ 1		(seconds)	*/
    jsys(DISMS,ac);			/* DISMS%			*/
#endif
#ifdef	SARG20
    static int disms[] = {
      (0201<<27)|(001<<23)|1000,	/* MOVEI  1,1000 ;1000 ms	*/
      (0104<<27)|0167,			/* DISMS%	 ;sleep so much	*/
      (0263<<27)|(017<<23)		/* POPJ   17,	 ;return	*/
    };
    static int (*disms_ptr)() = disms;

    (*disms_ptr)();			/* sleep one second		*/
#endif
#ifdef	SARG10
    static int sleep_code[] = {
      (0201<<27)|(001<<23)|1,		/* MOVEI  1,1	;one second	*/
      (0047<<27)|(001<<23)|031,		/* SLEEP  1,	;sleep so much	*/
      (0263<<27)|(017<<23)		/* POPJ   17,	;return		*/
    };
    static int (*sleep_ptr)() = sleep_code;

    (*sleep_ptr)();			/* sleep one second		*/
#endif
}
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* init_world()	initialize whatever modes and settings which need be	*/
/*		to different value, save old values for restore_modes()	*/
/*		to restore.						*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
VOID init_world(){
#ifdef	SARG10
#define	TOILF	0
#define	TOTNA	6
    static char *trmmsg[] = {
	"0\tTOILF%\tIllegal function code\n",
	"1\tTOPRV%\tNot privileged\n",
	"2\tTORGB%\tRange bad for some argument\n",
	"3\tTOADB%\tIllegal argument list or length\n",
	"4\tTOIMP%\tLine is not a dataset line\n",
	"5\tTODIL%\tError in dialling routine\n",
	"6\tTOTNA%\tTerminal not available"
    };
    static int totrm[] = {
    (0201<<27)|(002<<23)|01041,		/* MOVEI  2,.TOTRM  ;get type	*/
    (0474<<27)|(003<<23),		/* SETO	  3,	;controling TTY	*/
    (0201<<27)|(001<<23)|2,		/* MOVEI  1,2	;ptr to argblk	*/
    (0515<<27)|(001<<23)|2,		/* HRLI   1,2	;length argblk	*/
    (0047<<27)|(001<<23)|0116,		/* TRMOP. 1,	;get the type	*/
    (0210<<27)|(001<<23)|1,		/*  MOVN  1,1	;error, none	*/
    (0202<<27)|(001<<23)|(1<<22)|(017<<18)|0777777,
					/* MOVEM  1,@-1(17)	;store	*/
    (0263<<27)|(017<<23)		/* POPJ   17,		;return	*/
    };
    static int (*gettrm)() = totrm;
    int	trm;				/* SIXBIT terminal type		*/
    char actrm[8];			/* 6 characters + NUL + NUL	*/
    char *pek;
#ifdef	OPTIMIZER
    static int towid[] = {		/* get terminal width setting	*/
    (0201<<27)|(002<<23)|01012,		/* MOVEI  2,.TOWID  ;get width	*/
    (0474<<27)|(003<<23),		/* SETO	  3,	;controling TTY	*/
    (0201<<27)|(001<<23)|2,		/* MOVEI  1,2	;ptr to argblk	*/
    (0515<<27)|(001<<23)|2,		/* HRLI   1,2	;length argblk	*/
    (0047<<27)|(001<<23)|0116,		/* TRMOP. 1,	;get the type	*/
    (0210<<27)|(001<<23)|1,		/*  MOVN  1,1   ;error, none	*/
    (0202<<27)|(001<<23)|(1<<22)|(017<<18)|0777777,
					/* MOVEM  1,@-1(17)	;store	*/
    (0263<<27)|(017<<23)		/* POPJ   17,		;return	*/
    };
    static int (*getwid)() = towid;
    int wid;
    static int topsz[] = {
    (0201<<27)|(002<<23)|01023,		/* MOVEI  2,.TOPSZ  ;get pagsiz	*/
    (0474<<27)|(003<<23),		/* SETO	  3,	;controling TTY	*/
    (0201<<27)|(001<<23)|2,		/* MOVEI  1,2	;ptr to argblk	*/
    (0515<<27)|(001<<23)|2,		/* HRLI   1,2	;length argblk	*/
    (0047<<27)|(001<<23)|0116,		/* TRMOP. 1,	;get the type	*/
    (0210<<27)|(001<<23)|1,		/*  MOVN  1,1   ;error, none	*/
    (0202<<27)|(001<<23)|(1<<22)|(017<<18)|0777777,
					/* MOVEM  1,@-1(17)	;store	*/
    (0263<<27)|(017<<23)		/* POPJ   17,		;return	*/
    };
    static int (*getpsz)() = topsz;
    int psz;
#endif

    if (TRMTYP == (char *) NULL){
	 printf("\?Internal error - cannot handle any terminal type...\n");
	 exit(1);			/* return FAILURE		*/
    }
    (*gettrm)(&trm);			/* get SIXBIT terminal type	*/
    if (trm <= 0){			/* failed?			*/
	printf("\?TRMOP.(.TOTRM) failed: ");	/* say so		*/
	errcod = 0-trm;			/* get error code		*/
	goto TERROR;			/* display error message, die	*/
    }
    pek = &asctrm[6];			/* where to store terminal type	*/
    asctrm[7] = '\0';			/* safeguard			*/
    while (trm){
	 *pek-- = (char)((trm & 0x3F)+040);	/* SIXBIT to ASCII	*/
	 trm >>= 6;			/* shift one SIXBIT character	*/
      }
    pek = &asctrm[0];			/* where to start		*/
    while (*pek && *pek != SPACE)	/* find first SPACE or NUL	*/
	 ; /* VOID */
    *pek = '\0';			/* make ASCIZ			*/
    if (strcmp(asctrm,TRMTYP)){
	  printf("\?Can only handle %s terminals - not %s\n",TRMNAM,asctrm);
	  exit(1);			/* return FAILURE		*/
    }
#ifdef	OPTIMIZER
    (*getwid)(&wid);			/* get carriage width (16..255)	*/
    if (wid <= 0){			/* failed?			*/
	printf("\?TRMOP.(.TOWID) failed:");	/* say so		*/
	errcod = 0-wid;			/* display error message, die	*/
    }
    if (wid < 16 || wid > 255){		/* be paranoid			*/
	printf("\?TRMOP.(.TOWID) out of bounds: %o\n",wid);
	exit(1);			/* return FAILURE		*/
    }
    te_width = wid;			/* return terminal width	*/
    (*getpsz)(&psz);			/* get page size		*/
    if (psz <= 0){			/* failed?			*/
	printf("\?TRMOP.(.TOPSZ) failed:");	/* say so		*/
	goto TERROR;			/* display error message, die	*/
    }
    te_height = psz;			/* return terminal height	*/
#endif
    return;
	    /* Error message from TRMOP. */
TERROR:
    if (errcod < TOILF || errcode > TOTNA){	/* unknown error code?	*/
	    printf("unknown error code (%o octal)\n",errcod);
    else    printf("%s",trmmsg[errcod]);	/* say what's up	*/
    exit(1);					/* die hard		*/
#endif

#ifdef	SARG20
    static int mtopr1[] = {
    (0201<<27)|(001<<23)|0101,		/* MOVEI  1,.PRIOUT		*/
    (0201<<27)|(002<<23)|030,		/* MOVEI  2,.MORLW		*/
    (0104<<27)|077,			/* MTOPR%			*/
    (0202<<27)|(003<<23)|(1<<22)|(017<<18)|0777777,
					/* MOVEM  3,@-1(17)	;store	*/
    (0201<<27)|(001<<23)|0101,		/* MOVEI  1,.PRIOUT		*/
    (0201<<27)|(002<<23)|031,		/* MOVEI  2,.MOSLW		*/
    (0400<<27)|(003<<23),		/* SETZ   3,			*/
    (0104<<27)|077,			/* MTOPR%			*/
    (0263<<27)|(017<<23)		/* POPJ   17,		;return	*/
    };
    static int (*foo1)() = mtopr1;
#ifdef	OPTIMIZER
    static int mtopr2[] = {
    (0201<<27)|(001<<23)|0101,		/* MOVEI  1,.PRIOUT		*/
    (0201<<27)|(002<<23)|032,		/* MOVEI  2,.MORLL		*/
    (0104<<27)|077,			/* MTOPR%			*/
    (0202<<27)|(003<<23)|(1<<22)|(017<<18)|0777777,
					/* MOVEM  3,@-1(17)	;store	*/
    (0263<<27)|(017<<23)		/* POPJ   17,		;return	*/
    };
    static int (*foo2)() = mtopr2;
#endif

    (*foo1)(&te_width);			/* MTOPR%: get width, set zero	*/
#ifdef	OPTIMIZER
    (*foo2)(&te_height);		/* MTOPR%: get height		*/
#endif
#endif
#ifdef	KCC
     ac[1] = _PRIOU;		/*	1/ .PRIOUT			*/
     ac[2] = _MORLW;		/*	2/ .MORLW			*/
     jsys(MTOPR,ac);		/*	MTOPR%				*/
     te_width = ac[3];		/*	returns 3/ width		*/
				/*	set infinite terminal width:	*/
     ac[1] = _PRIOU;		/*	1/ .PRIOU			*/
     ac[2] = _MOSLW;		/*	2/ .MOSLW			*/
     ac[3] = 0;			/*	3/ 0				*/
     jsys(MTOPR,ac);		/*	MTOPR%				*/
#ifdef	OPTIMIZER
     ac[1] = _PRIOU;		/*	1/ .PRIOUT			*/
     ac[2] = _MORLL;		/*	2/ .MORLL			*/
     jsys(MTOPR,ac);		/*	MTOPR%				*/
     te_height = ac[3];		/*	return 3/ height		*/
#endif
#endif

#ifdef	PR1MEC
     prime_mode();			/* PR1IME specials	*/
#endif

#ifdef	HASSETBUF
     setbuf(stdout,(char*) NULL);	/* [312] unbuffered output	*/
#endif

#ifdef __TURBOC__
#ifdef CTRLBRK
   ctrlbrk(kpjbreak);			/* install CTRL/BREAK handler	*/
#endif
#endif

#ifdef	GNUDOS
  te_width  = ScreenCols();		/* [307] screen width		*/
#ifdef	OPTIMIZER
  te_height = ScreenRows();		/* [307] screen height		*/
#endif
  narrow = 2*(te_width < 42);		/* [307] see if narrow screen	*/
#endif

#ifdef	MESSYDOG
   _AHin    = 0x0F;			/* BIOS: get video mode		*/
   _int(0x10);				/* BIOS video service		*/
   oldmode  = _ALout;			/* [304] save video mode	*/
   video_page = _BHout;			/* save video page#		*/

   _BHin    = _BHout;			/* shuffle			*/
   _AHin    = 3;			/* read cursor position		*/
   _int(0x10);				/* BIOS video services		*/
   cursor   = _CXout;			/* save cursor style		*/
#ifdef	OPTIMIZER
   virt_vpos = _DHout;			/* [306] save row		*/
   virt_hpos = _DLout;			/* [306] save column		*/
#endif

#ifndef	DEBUG
   _CXin    = 0x0100;			/* get rid of cursor		*/
   _AHin    = 1;			/* set cursor size		*/
   _int(0x10);				/* BIOS video services		*/   
#endif
   _AHin    = 0x08;			/* read character, attribute	*/
   _BHin    = (UCHAR) video_page;	/* this video page		*/
   _int(0x10);				/* BIOS video services		*/   
   video_attr= _AHout;			/* save video attribute		*/
					/* get BIOS video mode		*/
#ifdef	DVIDEO				/* direct video memory		*/
   bios_mode = peek(0x0040,0x0049);	/* resides @0040h:0049h		*/
   video_seg = (bios_mode == 7) ?	/* test video mode		*/
	   0xB000 : 0xB800;		/* monochrome or colour?	*/
#endif
   _AHin = 0x0F;			/* [306] get current video mode	*/
   _int(0x10);				/* [306] BIOS video services	*/
   switch (_ALout){
   case 0:			/* 16 gray scale,	      all but MDA */
   case 1:			/* 16 foreground,8 background,all but MDA */
	te_width  = 40;
	te_height = 24;
	narrow = 2;		/* [306] make it work on those, too	*/
	break;
   case 2:			/* 16 gray scale,	      all but MDA */
   case 3:			/* VGA Colour Mode			*/
   case 6:			/* Graphics				*/
   case 7:			/* VGA Mono Mode			*/
	te_width  = 80;
	te_height = 24;
	break;
   case 0x54:			/* 43 lines and 132 characters		*/
	te_width  = 132;
	te_height = 43;
	break;
   case 0x55:			/* 25 lines and 132 characters		*/
	te_width  = 132;
	te_height = 25;
	break;
   default:
	restore_modes();	/* restore original modes		*/
	exitt();		/* cannot handle, give up		*/
   }
#ifdef	NARROW
   if (narrow == 1){			/* [306] `-n' ?			*/
      _AXin    = 0x0000;		/* [304] set video mode 0	*/
      _int(0x10);			/* [304] BIOS video service	*/
   }					/* [304]			*/
#endif
#endif

#ifdef	CURSES
   initscr();				/* curses: initialize screen	*/
#endif
#ifdef	X11
	    ...initialize X...
#endif

/* .....................................................................*/
/* Intercept any signals here.						*/
/* .....................................................................*/
#ifdef	HASSIGNAL
   signal(SIGINT,doquit);	/* stop on INTERRUPT		*/
   signal(SIGTERM,doquit);	/* stop on TERMINATE		*/
#endif
/* .....................................................................*/
/* Initialize the hardware, that is the terminal device.		*/
/* .....................................................................*/
#ifdef	VK100
					/* [306] VK-100 (GIGI)		*/
   putchar(ESC);			/* [306]			*/
   printf("PpS(I(R)W(I(Y))");		/* [306] matching )		*/
   putchar(ESC);			/* [306]			*/
   putchar('\\');			/* [306]			*/
#endif
#ifdef	TEK425
					/* [306] Tektronix 4025		*/
   printf("!COM %d\n",TEKCHR);		/* [306] Set command character	*/
#endif
/* .....................................................................*/
/* Initialize our screen memory handler cache memory to a known state.	*/
/* When we reach here, the screen state has been saved, the basic stuff	*/
/* is enabled, and we can change the screen from this point on.		*/
/* .....................................................................*/
#ifdef	OPTIMIZER
#ifndef	DVIDEO
    videomem = (char **) malloc(te_height*sizeof(char *));
    if (videomem == NULL){		/* [306] failed			*/
	restore_modes();		/* [306] give up		*/
	exitt();			/* [306] . . .			*/
    }					/* [306] . . .			*/
    for (i = 0; i < te_height; i++)
	videomem[i] = (char *) NULL;
    for (i = 0; i < te_height; i++){
	videomem[i] = (char *) malloc(te_width*sizeof(char));
	if (videomem[i] == NULL){
	    for (j = 0; j < i; j++)
		free(videomem[j]);
		free(videomem);
		restore_modes();
		exitt();
	}
	for (j = 0; j < te_width; j++)
	    videomem[i][j] = SPACE;
    }
#endif
#endif
}
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* restore_modes()  restores modes/settings changed by init_world()	*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
VOID restore_modes(){
#ifdef	DEBUG
     if (debug != NULL){
	 fclose(debug);
	 debug = NULL;
     }
#endif
#ifdef	SARG20
    static int mtopr[] = {
    (0201<<27)|(001<<23)|0101,		/* MOVEI  1,.PRIOUT		*/
    (0201<<27)|(002<<23)|031,		/* MOVEI  2,.MOSLW		*/
    (0200<<27)|(003<<23)|(1<<22)|(017<<18)|0777777,
					/* MOVE   3,@-1(17)	;load	*/
    (0104<<27)|077,			/* MTOPR%			*/
    (0263<<27)|(017<<23)		/* POPJ   17,		;return	*/
    };
    static int (*foo)() = mtopr;

    (*foo)(&te_width);
#endif
#ifdef	KCC
				/* TOPS-20: restore terminal width	*/
     ac[1] = _PRIOU;		/*	1/ .PRIOUT			*/
     ac[2] = _MOSLW;		/*	2/ .MOSLW			*/
     ac[3] = te_width;		/*	3/ width			*/
     jsys(MTOPR,ac);		/*	MTOPR%				*/
#endif
#ifdef	MESSYDOG
    if (narrow == 1){		/* [306] `-n' ?				*/
       _AHin   = 0x00;		/* [304] set video mode			*/
       _ALin   = oldmode;	/* [304] old video mode			*/
       _int(0x10);		/* [304] BIOS video service		*/
    }				/* [304]				*/
   _CXin    = cursor;		/* put back cursor			*/
   _AHin    = 1;		/* set cursor size			*/
   _int(0x10);			/* BIOS video services			*/   
#endif
#ifdef	X11
     ...terminate X11...
#endif
}
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* restore_world()	restore normal mode, and gets rid of anything	*/
/*			set up by init_world()				*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
VOID restore_world(){
#ifdef	OPTIMIZER
#ifndef	DVIDEO
     int i;			/* [306] loop counter			*/
#endif
#endif

     refresh_screen();		/* [306] refresh screen			*/
     restore_modes();		/* [306] restore hardware		*/
#ifdef	OPTIMIZER
#ifndef	DVIDEO
     for (i = 0; i < te_height; i++)
	 free(videomem[i]);	/* [306] kill cache			*/
     free(videomem);		/* [306] . . .				*/
#endif
#endif
#ifdef	HASSIGNAL
   signal(SIGINT,SIG_DFL);	/* restore default for INTERRUPT	*/
   signal(SIGTERM,SIG_DFL);	/* restore default for TERMINATE	*/
#endif
}
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* user_x()	Check if user has done any input lately.		*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	HASUSERX
int user_x(){
#ifdef	SARG10
   int hasinp;
   static int skpinc[] = {
       (0201<<27)|(001<<23)|1,		/* MOVEI  1,1	;default ON	*/
       (0051<<27)|(013<<23),		/* SKPINC	;empty?		*/
       (0201<<27)|(001<<23)|0,		/*  MOVEI 1,0	;was empty	*/
       (0202<<27)|(001<<23)|(1<<22)|(017<<18)|0777777,
					/* MOVEM  1,@-1(17)	;store	*/
       (0263<<27)|(017<<23)		/* POPJ   17,	;return		*/
    };
    static int (*inputp)() = skpinc;

    (*inputp)(&hasinp);			/* call above code		*/
    return hasinp;			/* return 0 or 1		*/
#endif
#ifdef	SARG20
   static int sibe[] = {
       (0201<<27)|(001<<23)|0777777,	/* MOVEI  1,.CTTRM		*/
       (0104<<27)|0102,			/* SIBE%			*/
       (0600<<27),			/*  TRN				*/
       (0202<<27)|(002<<23)|(1<<22)|(017<<18)|0777777,
					/* MOVEM  2,@-1(17)	;store	*/
       (0263<<27)|(017<<23)		/* POPJ   17,	;return		*/
   };
    int i;
    static int (*inputp)() = sibe;

    (*inputp)(&i);
    return i;
#endif
#ifdef	KCC
    ac[1] = _CTTRM;			/* 1/	controlling terminal	*/
    jsys(SIBE,ac);			/* SIBE%			*/
    return ac[2];			/* 2/	0=no or 1=yes		*/
#endif
#ifdef	PR1MEC
    return prime_kbhit();		/* PR1ME specials		*/
#endif
#ifdef	BSD43
					/* [312] 4.3BSD			*/
    fd_set fdvar;			/* [312] file descriptor set	*/
    struct timeval timeout;		/* [312] time out		*/
    FD_ZERO(&fdvar);			/* [312] clear set		*/
    FD_SET(0,&fdvar);			/* [312] check standard input	*/
    timeout.tv_sec = 1;			/* [312] wait 1 second		*/
    timeout.tv_usec = 0;		/* [312] . . .			*/
    switch (select(1,&fdvar,(fd_set *) NULL,(fd_set *) NULL,&timeout)){
    case 0:   return 0;			/* [312] timed out, continue	*/
    case -1:  perror("select");		/* [312]			*/
    default:  return 1;			/* [312] input detected, quit	*/
    }					/* [312]			*/
#endif
#ifdef	HASKBHIT
   return kbhit();			/* see if terminal buffer empty	*/
#endif
}
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* 10.	Terminal driver routines.					*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* rca()	Relative cursor addressing.				*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	WANT_RCA
#define	UP	0
#define	DOWN	1
#define	RIGHT	2
#define	LEFT	3
#endif

/* [306] When the screen cursor movement optimizer is enabled, this is	*/
/* [306] only called when something really is going to be written to	*/
/* [306] screen, since it was not in the cache.				*/

#ifdef	WANT_RCA
VOID rca(kar,much) int kar,much;{
#ifdef	DEBUG
   if (debug != NULL) fprintf(debug,"--> rca(%d,%d)",kar,much);
#endif
#ifdef	ANSI
#ifdef	DEBUG
   if (debug != NULL){
	   fprintf(debug,"= $[");	/* ] */
	   if (much > 1) fprintf(debug,"%d",much);
	   fprintf(debug,"%c\n",'A'+kar);
   }
#endif
   putchar(ESC);			/* [306]			*/
   putchar('[');			/* [306] matching ]		*/
   if (much > 1)			/* [306]			*/
      printf("%d",much);		/* [306]			*/
   putchar('A'+kar);			/* [306]			*/
#endif
/* .................................................................... */
#ifdef	TEK425
   switch (kar){
      case UP:		printf("%cUP %d\n", TEKCHR,much);	break;
      case DOWN:	printf("%cDOW %d\n",TEKCHR,much);	break;
      case LEFT:	printf("%cLEF %d\n",TEKCHR,much);	break;
      case RIGHT:	printf("%cRIG %d\n",TEKCHR,much);	break;
   }
#endif
}
#endif

#ifdef	WANT_DCA
VOID dca(vpos,hpos) int vpos,hpos;{
#ifdef	DEBUG
   if (debug != NULL) fprintf(debug,"--> dca(%d,%d)",vpos,hpos);
#endif
#ifdef	EL1521
    printf("\036%c%c",hpos+30,vpos+30);
#endif
/* .................................................................... */
#ifdef	ANSI
#ifdef	DEBUG
   if (debug != NULL){
	   fprintf(debug,"= $[");	/* ] */
	   if (vpos > 1) fprintf(debug,"%d",vpos);
	   if (hpos > 1) fprintf(debug,";%d",hpos);
	   fprintf(debug,"H\n");
   }
#endif
    putchar(ESC);			/* [306] direct cursor address	*/
    putchar('[');			/* [306] matching ]		*/
    if (vpos > 1)			/* [306]			*/
       printf("%d",vpos);		/* [306]			*/
    if (hpos > 1)			/* [306]			*/
       printf(";%d",hpos);		/* [306]			*/
    putchar('H');			/* [306]			*/
#endif
/* .................................................................... */
#ifdef	TEK425
    printf("%cJUM %d,%d\n",TEKCHR,vpos,hpos);
#endif
}
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* 11.	Terminal handling functions.					*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* real_clear()	Clear screen, physically.				*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	INTERFACE
VOID real_clear(){
#ifdef	OPTIMIZER
   int i;				/* [306] loop counter		*/
#ifndef	DVIDEO
   int row, col;			/* [306] loop counters		*/
#endif
#endif

#ifdef	DEBUG
   if (debug != NULL) fprintf(debug,"--> real_clear\n");
#endif
#ifdef	EL1521
   putchar('\015');			/* CTRL/L on ELITE 1520/1521	*/
#endif
/* .................................................................... */
#ifdef	TEK425
   printf(				/* [306] Set Monitor Mode	*/
	   "%cMON M\n%cERA\n",		/* [306] and Erase Screen	*/
	   TEKCHR,TEKCHR);		/* [306]			*/
#endif
/* .................................................................... */
#ifdef	ANSI
   putchar(ESC);			/* [306] Clear to End of Screen	*/
   printf("[2J");			/* [306]	matching ]	*/
   putchar(ESC);			/* [306] Cursor Home		*/
   printf("[H");			/* [306]	matching ]	*/
#endif
/* .................................................................... */
#ifdef	GNUDOS
#ifndef	ANSI
  ScreenSetCursor(0,0);			/* [307] home			*/
  ScreenClear();			/* [307] clear screen		*/
#endif
#endif
/* .................................................................... */
#ifdef DVIDEO	
#ifdef	MESSYDOG			/* direct video memory write	*/
  _BHin = video_attr;			/* video attributes		*/
  _CHin = 0;				/* start row			*/
  _CLin = 0;				/* start column			*/
  _DHin = te_height;			/* ending row			*/
  _DLin = te_width;			/* ending column		*/
  _AXin = 0x0600;			/* BIOS scroll page		*/
  _int(0x10);				/* BIOS video services		*/
#endif
#endif
/* ....................................................................	*/
/* [306] Change the optimizer variables to reflect the changes.		*/
/* ....................................................................	*/
#ifdef	OPTIMIZER
   real_hpos = real_vpos = OFFSET;		/* [306] cursors  home	*/
   virt_hpos = virt_vpos = OFFSET;		/* [306] . . .		*/
   for (i = 0; i < POSMAX; i++)			/* [306] clear erasures	*/
       eras_hpos[i] = eras_vpos[i] = UNDEF;	/* [306] . . .		*/
   eras_ptr = 0;				/* [306] table empty	*/
#ifdef	DEBUG
   if (debug != NULL)
	fprintf(debug,
	"real_clear:real_%%pos=(v=%d,h=%d) virt_%%pos=(v=%d,h=%d)\n",
		real_vpos,real_hpos,virt_vpos,virt_hpos);
#endif
#ifndef	DVIDEO
   for (row = 0; row < te_height; row++)	/* [306] clear memory	*/
       for (col = 0; col < te_width; col++)	/* [306] . . .		*/
	   videomem[row][col] = SPACE;		/* [306] . . .		*/
#endif
#endif
}
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* locate(vpos,hpos)	move virtual cursor to location (vpos,hpos)	*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	OPTIMIZER
VOID locate(vpos,hpos) int hpos,vpos;{
#ifdef	DEBUG
   if (debug != NULL) fprintf(debug,"--> virtual locate(%d,%d)\n",vpos,hpos);
#endif
   virt_vpos = vpos;		/* [306] remember new cursor position	*/
   virt_hpos = hpos;		/* [306] . . .				*/
#ifdef	DEBUG
   if (debug != NULL) fprintf(debug,"<-- virtual locate\n");
#endif
}
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* real_locate(vpos,hpos)						*/
/*		move hardware cursor to location (vpos,hpos).		*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/

#ifndef	CURSES
VOID real_locate(vpos,hpos) int vpos,hpos;{

#ifdef	DVIDEO
#ifdef	DEBUG
   if (debug != NULL) fprintf(debug,"--> real_locate(%d,%d)\n",vpos,hpos);
#endif
#ifdef	MESSYDOG
   _BHin = (unsigned char) video_page;	/* this video page		*/
   _DHin = (unsigned char) vpos;	/* row				*/
   _DLin = (unsigned char) hpos;	/* column			*/
   _AHin = 0x02;			/* BIOS set cursor position	*/
   _int(0x10);				/* BIOS video services		*/
#endif
#ifdef	GNUDOS
   ScreenSetCursor(vpos,hpos);		/* [307] set cursor position	*/
#endif

#else

#ifdef	WANT_RCA
    int hdiff;				/* [306] horizontal difference	*/
    int vdiff;				/* [306] vertical difference	*/
#ifdef	OPTIMIZER
    int i;				/* [306] loop counter		*/
    int flag;				/* [306] flag			*/
#endif
#endif

#ifdef	OPTIMIZER
#define	old_vpos	real_vpos
#define	old_hpos	real_hpos
#endif

#ifdef	DEBUG
   if (debug != NULL) fprintf(debug,"--> real_locate(%d,%d)\n",vpos,hpos);
#endif
#ifdef	WANT_RCA
	vdiff = vpos - old_vpos;
	if (vdiff < 0)
	   vdiff = 0 - vdiff;
	hdiff = hpos - old_hpos;
	if (hdiff < 0)
	   hdiff = 0 - hdiff;
#ifdef	DEBUG
	if (debug != NULL) fprintf(debug,"vdiff=%d hdiff=%d\n",vdiff,hdiff);
#endif
	if (vdiff < 2 || hdiff < 2){
	      if (vdiff){
		 if (vpos < old_vpos)
		    rca(UP,old_vpos - vpos);		/* UP */
		 else
		    rca(DOWN,vpos - old_vpos);		/* DOWN */
	      }
	      if (hdiff){
	         if (hpos < old_hpos)		/* if going to the left */
		    rca(LEFT,old_hpos - hpos);		/* LEFT */
		 else {
#ifdef	OPTIMIZER
/*
 *	If short cursor movement, see if we can get there with SPACEs instead.
 */
			flag = ((hpos - old_hpos) < MAXRIGHT);
#ifdef	DEBUG
	if (debug != NULL) fprintf(debug,
	    "use spaces? hpos=%d old_hpos=%d MAXRIGHT=%d flag=%d\n",
		   hpos,old_hpos,MAXRIGHT,flag);
#endif
			for (i = old_hpos; i < hpos; i++){
#ifdef	DEBUG
	if (debug != NULL) fprintf(debug,
		"i=%d, check backup_store(%d,%d) for SPACE\n",
			i,vpos,i);
#endif
			    if (backup_store(vpos,i) != SPACE){
				flag = 0;	/* sorry, cannot do	*/
#ifdef	DEBUG
			        if (debug != NULL)
				   fprintf(debug,"no,not SPACEs\n");
#endif
				break;
			    }
			}
#ifdef	DEBUG
			if (debug != NULL) fprintf(debug,"flag=%d\n",flag);
#endif
			if (flag)
			   for (i = old_hpos; i < hpos; i++){
#ifdef	DEBUG
				if (debug != NULL) fprintf(debug,
					"real_addch(SPACE)\n");
#endif
				real_addch(SPACE);	/* RIGHT */
			   }
			else
#endif
			   rca(RIGHT,hpos - old_hpos);	/* RIGHT */
		   }
		}
	}
	else
#endif
#ifdef	WANT_DCA
	     dca(vpos,hpos);
#endif
#undef	old_vpos
#undef	old_hpos
#endif

#ifdef	OPTIMIZER
    real_hpos = hpos;		/* [306] remember cursor pos	*/
    real_vpos = vpos;		/* [306] . . .			*/
#endif
#ifdef	DEBUG
    if (debug != NULL) fprintf(debug,"<-- real_locate()\n");
#endif
}
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* backup_store()	Return value from backup store.			*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/

#ifdef	OPTIMIZER
int backup_store(vpos,hpos) int vpos,hpos;{
   register char tecken;

#ifdef	DEBUG
   if (debug != NULL) fprintf(debug,"--> backup_store(%d,%d)\n",vpos,hpos);
#endif
#ifdef	DVIDEO
#ifdef	MESSYDOG
   video_off = 2*(te_width*vpos+hpos);	/* [306] beginning video offset	*/
   tecken =  peek(video_seg,video_off) & 0xFF;	/* [306] read video memory */
#endif
#ifdef	GNUDOS
   video_off = te_width*vpos+hpos;	/* [307] beginning video offset	*/
  tecken = ScreenPrimary[video_off] & 0xFF;	/* [307] read video memory */
#endif
#else
   tecken = videomem[vpos][hpos];	/* [306] remote video access	*/
#endif
#ifdef	DEBUG
   if (debug != NULL) fprintf(debug,"<-- backup_store(%d,%d)='%c'\n",
				   vpos,hpos,tecken);
#endif
   return tecken;
}
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* del_erase()		Remove an entry from erasure table.		*/
/* The entries are stored sorted first on vpos, then on hpos.		*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/

#ifdef	OPTIMIZER
VOID del_erase(xpos) int xpos;{		/* [306]			*/
     int i;				/* [306] loop counter		*/

#ifdef	DEBUG
     if (debug != NULL)
	fprintf(debug,"-->del_erase(%d)\n",xpos);
#endif
     for (i = xpos; i < eras_ptr; i++){	/* [306] loop over table	*/
	eras_hpos[i] = eras_hpos[i+1];	/* [306] . . .			*/
	eras_vpos[i] = eras_vpos[i+1];	/* [306] . . .			*/
#ifdef	DEBUG
	if (debug != NULL)
	   fprintf(debug,
	   "del_erase:eras_%%pos[%d]:=eras_%%pos[%d]=(v=%d,h=%d)\n",
		   i,i+1,eras_vpos[i],eras_hpos[i]);
#endif
     }					/* [306] . . .			*/
     eras_hpos[eras_ptr] = UNDEF;	/* [306] remove erasure	entry	*/
     eras_vpos[eras_ptr] = UNDEF;	/* [306] . . .			*/
#ifdef	DEBUG
     if (debug != NULL){
	fprintf(debug,"del_erase:eras_%%pos[%d]:=(v=-1,h=-1)\n",eras_ptr);
	fprintf(debug,"del_erase:eras_ptr:=%d\n",eras_ptr-1);
     }
#endif
     eras_ptr--;			/* [306] one less entry		*/
}					/* [306]			*/
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* add_erase()		Add erase entry to erase table.			*/
/*									*/
/* The entries are stored sorted first on vpos, then on hpos.		*/
/* The sorting is done here, when inserting the entry to the table.	*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/

#ifdef	OPTIMIZER
int add_erase(vpos,hpos) int vpos,hpos;{
     int currpos;			/* [306] current table index	*/
     int i;				/* [306] loop counter		*/

#ifdef	DEBUG
     if (debug != NULL){
	fprintf(debug,"--> add_erase(%d,%d)\n",vpos,hpos);
	for (i=0; i < eras_ptr; i++)
		fprintf(debug,"add_erase:eras_%%pos[%d]=(v=%d,h=%d)\n",
			i,eras_vpos[i],eras_hpos[i]);
     }
#endif

/*
 *	If table is full, this is an error condition.
 *	The same holds for invalid table index.
 */
     if (eras_ptr >= POSMAX){		/* [306] table full?		*/
#ifdef	DEBUG
	 if (debug != NULL){
	    fprintf(debug,"add_erase: table full, return 0\n");
	    for (i=0; i < eras_ptr; i++)
		fprintf(debug,"add_erase:eras_%%pos[%d]=(v=%d,h=%d)\n",
			i,eras_vpos[i],eras_hpos[i]);
	}
#endif
	 return 0;			/* [306] yes, return FAILURE	*/
     }					/* [306]			*/
     if (eras_ptr < 0){			/* [306] invalid index?		*/
#ifdef	DEBUG
	 if (debug != NULL){
	    fprintf(debug,"add_erase: invalid eras_ptr=%, return 0\n",
		    eras_ptr);
	    for (i=0; i < eras_ptr; i++)
		    fprintf(debug,"add_erase:eras_%%pos[%d]=(v=%d,h=%d)\n",
			    i,eras_vpos[i],eras_hpos[i]);
         }
#endif
	 return 0;			/* [306] yes, return FAILURE	*/
     }					/* [306]			*/
/*
 *	See if any old entry or entries for the same vpos (row,line).
 *	(We store the entries sorted first on vpos, then on hpos.)
 */
     for (i = 0; i < eras_ptr; i++){	/* [306] loop over table	*/
	currpos = i;			/* [306] this entry in progress	*/
	if (eras_vpos[i] == vpos)	/* [306] entry for this vpos?	*/
	   goto FOUND_VPOS;		/* [306] yes, go handle that	*/
        if (eras_vpos[i] > vpos)	/* [306] no, but should be?	*/
	   goto STORE_IT;		/* [306] yes, not present then	*/
     }					/* [306] no, try next		*/
/*
 *	Fell through: either table empty or the entry is appended.
 */
#ifdef DEBUG
     if (debug != NULL)
	fprintf(debug,"add_erase: no entry for vpos=%d, append entry\n",
		vpos);
#endif
     currpos = eras_ptr;		/* [306] store at end of table	*/
     goto STORE_IT;			/* [306] go store it		*/
/*
 *	At least one old entry present for same vpos.
 *	See if any old entry for the same hpos (column).
 */

FOUND_VPOS:

#ifdef	DEBUG
     if (debug != NULL)
	fprintf(debug,"add_erase: entry for vpos=%d found at %d\n",
		vpos,currpos);
#endif
     for (i = currpos; i < eras_ptr; i++){	/* [306] table loop	*/
	currpos = i;			/* [306] this in progress	*/
	if (eras_vpos[i] != vpos)	/* [306] end of entries?	*/
	   goto STORE_IT;		/* [306] yes, store here	*/
	if (eras_hpos[i] == hpos)	/* [306] found same location?	*/
	   return 1;			/* [306] yes, return SUCCESS	*/
	if (eras_hpos[i] > hpos)	/* [306] should be here?	*/
	   goto STORE_IT;		/* [306] yes, store here	*/
     }					/* [306] no, try next		*/
/*
 *	Fell through: the entry is appended.
 */
     currpos = eras_ptr;		/* [306] store at end of table	*/
#ifdef	DEBUG
     if (debug != NULL)
	fprintf(debug,"add_erase: no entry for hpos=%d, append entry\n",hpos);
#endif
					/* [306] fall through		*/
STORE_IT:

/*
 *	First make space for the new entry, in case it is occupied.
 */
#ifdef	DEBUG
     if (debug != NULL)
	fprintf(debug,"add_erase:new entry stored at %d\n",currpos);
#endif
     for (i = eras_ptr; i > currpos; i--){	/* [306] table loop	*/
#ifdef	DEBUG
	if (debug != NULL)
	   fprintf(debug,
		   "add_erase:eras_%%pos[%d]:=eras_%%pos[%d]=(v=%d,h=%d)\n",
		   i,i-1,eras_vpos[i-1],eras_hpos[i-1]);
#endif
	eras_vpos[i] = eras_vpos[i-1];	/* [306] move them up	*/
	eras_hpos[i] = eras_hpos[i-1];	/* [306] . . .		*/
     }					/* [306] . . .		*/

/*
 *	Now store the new entry, and increment the entry counter.
 */

#ifdef	DEBUG
     if (debug != NULL)
	fprintf(debug,"add_erase:eras_%%pos[%d]:=(v=%d,h=%d)\n",
		currpos,vpos,hpos);
#endif
     eras_hpos[currpos] = hpos;		/* [306] store horiz.position	*/
     eras_vpos[currpos] = vpos;		/* [306] store vertical pos.	*/

     eras_ptr++;			/* [306] one more entry		*/
#ifdef	DEBUG
     if (debug != NULL){
	fprintf(debug,"add_erase:eras_ptr:=%d\n",eras_ptr);
	for (i=0; i < eras_ptr; i++)
		fprintf(debug,"add_erase:eras_%%pos[%d]=(v=%d,h=%d)\n",
			i,eras_vpos[i],eras_hpos[i]);
     }
#endif
     return 1;				/* [306] return SUCCESS		*/
}					/* [306] . . .			*/
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* real_addch()		Write character to video memory (DVIDEO only).	*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	DVIDEO
VOID real_addch(tecken) int tecken;{	/* [306] write character	*/
#ifdef	OPTIMIZER
#define	vpos	real_vpos
#define	hpos	real_hpos
#else
#ifndef	GNUDOS
   register
#endif
   int hpos,vpos;

#ifdef	MESSYDOG
   _BHin    = video_page;		/* get video page		*/
   _AHin    = 3;			/* read cursor position		*/
   _int(0x10);				/* BIOS video services		*/
   vpos = _DHout;			/* row				*/
   hpos = _DLout;			/* column			*/
#endif
#ifdef	GNUDOS
   ScreenGetCursor(&vpos,&hpos);	/* [307] read cursor position	*/
#endif
#endif
#ifdef	MESSYDOG
					/* beginning video offset	*/
   video_off = 2*(te_width*vpos+hpos);
					/* write character		*/
   poke(video_seg,video_off,((peek(video_seg,video_off)) & ~0xFF) | tecken);
#endif
#ifdef	GNUDOS
   video_off = te_width*vpos+hpos;
   ScreenPrimary[video_off] &= ~0xFF;
   ScreenPrimary[video_off] |= tecken;
#endif
#ifdef	OPTIMIZER
#undef	vpos
#undef	hpos
#endif
}
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* add_character()	Write character at current cursor position.	*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/

#ifndef	OPTIMIZER
#undef	SLASK
#ifdef	MSDOS
#define	SLASK
#else
#ifdef	X11
#define	SLASK
#endif
#endif
#ifdef	SLASK
VOID add_character(x) int x;{		/* [306] MSC rejects macro	*/
#ifdef	MSDOS
	putchar(x);			/* [306] so we do this instead	*/
#endif
#ifdef	X11
	...display a character via X11...
#endif
}					/* [306]			*/
#undef	SLASK
#endif
#endif

#ifdef	OPTIMIZER
VOID add_character(tecken) int tecken;{
    int i;				/* [306] loop counter		*/

#ifdef	DEBUG
    if (debug != NULL)
	fprintf(debug,"--> add_character('%c')\n",tecken);
#endif
/*
 *	If already on screen, treat as if we just printed it.
 */
   if (backup_store(virt_vpos,virt_hpos) == tecken){
#ifdef	DEBUG
      if (debug != NULL)
	 fprintf(debug,"add_character:'%c' at virtual v=%d,h=%d\n",
		 tecken,virt_vpos,virt_hpos);
#endif
      for (i = 0; i < eras_ptr; i++){
	      if (eras_vpos[i] == virt_vpos &&
		  eras_hpos[i] == virt_hpos){
		  del_erase(i);
		  break;
	  }
      }
      virt_hpos++;			/* [306] bump virtual cursor	*/
      return;				/* [306] done			*/
   }

/*
 *	Character was not on screen.
 *	If it is a space, store it in the erasure tables,
 *	bump the virtual cursor, and return.
 *	If table is full, treat space as normal character.
 */
#ifdef	DEBUG
    if (debug != NULL)
	fprintf(debug,"add_character:'%c' not at virtual v=%d,h=%d\n",
		tecken,virt_vpos,virt_hpos);
#endif
   if (tecken == SPACE){			/* [306] SPACE		*/
      i = add_erase(virt_vpos,virt_hpos);	/* [306] table space?	*/
      if (i){				/* [306] . . .			*/
	 virt_hpos++;			/* [306] OK,move virtual cursor	*/
	 return;			/* [306] done			*/
      }					/* [306]			*/
#ifdef	DEBUG
      if (debug != NULL)
	 fprintf(debug,"add_character:treat SPACE as normal character\n");
#endif
   }					/* [306]			*/

/*
 *	Character was not space: must write it to screen.
 *	See if any erasures directly to the left of the added character.
 *	If so, move the start position to the leftmost erasure position.
 *	Move the hardware cursor, if needed.
 */
   if (real_vpos != virt_vpos || real_hpos != virt_hpos)
	real_locate(virt_vpos,virt_hpos);
/*
 *	Output the character to the screen.
 */
#ifdef	DEBUG
    if (debug != NULL)
	fprintf(debug,"add_character:real_addch('%c')\n",tecken);
#endif
    real_addch(tecken);			/* [306] put it there		*/
#ifndef	DVIDEO
    videomem[real_vpos][real_hpos] = (char) tecken;  /* [306] remember!	*/
#endif

/*
 *	Character written.
 *	Update all variables to reflect the currect state of affairs.
 */
    for (i = 0; i < eras_ptr; i++){	/* [306] loop over erasures	*/
       if (eras_hpos[i] == real_hpos &&	/* [306] cursor found there?	*/
	   eras_vpos[i] == real_vpos){	/* [306] . . .			*/
#ifdef	DEBUG
       if (debug != NULL)
	  fprintf(debug,"add_character:character overlaps erasure\n");
#endif
	   del_erase(i);		/* [306] yes, remove it		*/
	   break;			/* [306] done			*/
       }				/* [306] 			*/
    }
/*
 *	Finally, move cursors.
 */
    real_hpos++;			/* [306] bump hardware cursor	*/
    virt_hpos++;			/* [306] bump virtual cursor	*/
#ifdef	DEBUG
    if (debug != NULL) fprintf(debug,"<-- add_character\n");
#endif
}					/* [306]			*/
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* add_str()	Output a string at current cursor position.		*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifndef	OPTIMIZER
#ifdef	MSDOS
VOID add_str(x) char *x;{		/* [306] have to do this, sigh.	*/
	printf("%s",x);			/* [306] since rejected macro	*/
}					/* [306]			*/
#endif
#endif
#ifdef	OPTIMIZER
VOID add_str(x) char *x;{		/* [306]			*/
   register char c;			/* [306] current character	*/
   register char *y;			/* [306] string pointer		*/

#ifdef	DEBUG
   if (debug != NULL) fprintf(debug,"--> add_str(\"%s\")\n",x);
#endif
   y = x;				/* [306] get string pointer	*/
   for (;;){				/* [306] loop			*/
	c = *y++;			/* [306] get character		*/
	if (!c) break;			/* [306] end of string		*/
	add_character(c);		/* [306] write character	*/
   }					/* [306]			*/
#ifdef	DEBUG
   if (debug != NULL) fprintf(debug,"<-- add_str(\"%s\")\n",x);
#endif
}					/* [306]			*/
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* print_word()	Print a formatted string at current cursor position.	*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	OPTIMIZER
VOID print_word(fmt,bar) char *fmt; int bar;{
   char buf[80];			/* put stuff here		*/

#ifdef	DEBUG
   if (debug != NULL){
	   fprintf(debug,"--> print_word(\"%s\",",fmt);
	   fprintf(debug,fmt,bar);
	   fprintf(debug,")\n");
   }
#endif
   sprintf(buf,fmt,bar);		/* format stuff			*/
#ifdef	DEBUG
   if (debug != NULL)
	   fprintf(debug,"call add_str(\"%s\")\n",buf);
#endif
   add_str(buf);			/* [306] output string		*/
#ifdef	DEBUG
   if (debug != NULL) fprintf(debug,"<-- print_word\n");
#endif
}
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* refresh_screen()	Refresh screen.				[306]	*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	OPTIMIZER
VOID refresh_screen(){
   register int i;			/* [306] loop counter		*/
   register SHORT vpox;			/* [306] erasure vpos		*/
   register SHORT hpox;			/* [306] erasure hpos		*/
   
#ifdef	DEBUG
   if (debug != NULL)
	fprintf(debug,"--> refresh_screen()\n");
#endif

/*
 *	Do all erasures left.
 */

#ifdef	DEBUG
   if (debug != NULL){
	fprintf(debug,"refresh:eras_ptr=%d\n",eras_ptr);
	for (i=0; i < eras_ptr; i++)
	    fprintf(debug,"refresh:eras_%%pos[%d]=(v=%d,h=%d)\n",
		    i,eras_vpos[i],eras_hpos[i]);
   }
#endif
   for (i = 0; i < eras_ptr; i++){	/* [306] loop over table	*/
	vpox = eras_vpos[i];		/* [306] get erasure position	*/
	hpox = eras_hpos[i];		/* [306] . . .			*/
#ifdef	DEBUG
	if (debug != NULL)
	   fprintf(debug,"refresh:eras_%%pos[%d]=(v=%d,h=%d)\n",
		   i,vpox,hpox);
#endif
	if (backup_store(vpox,hpox) != SPACE){	/* [306] erased?	*/
#ifdef	DEBUG
	   if (debug != NULL)
		fprintf(debug,"refresh:must erase (v=%d,h=%d)\n",vpox,hpox);
#endif
	   if (real_hpos != hpox ||		/* [306] no		*/
	       real_vpos != vpox)		/* [306] need cursor?	*/
	      real_locate(vpox,hpox);	/* [306] yes, move real cursor	*/
#ifdef	DEBUG
	   if (debug != NULL)
		fprintf(debug,"refresh:real_addch(SPACE)\n");
#endif
	   real_addch(SPACE);		/* [306] erase the position	*/
#ifndef	DVIDEO
	   videomem[real_vpos][real_hpos] = SPACE;
#endif
	   real_hpos++;			/* [306] bump hardware cursor	*/
	}				/* [306]			*/
#ifdef	DEBUG
	if (debug != NULL)
	   fprintf(debug,"refresh:delete erasure %d\n",i);
#endif
   }					/* [306] . . .			*/
   for (i=0; i < eras_ptr; i++)
	   eras_vpos[i] = eras_hpos[i] = UNDEF;
   eras_ptr = 0;			/* [306]			*/

/*
 *	Move hardware cursor, if it is not there already.
 */

#ifdef	DEBUG
   if (debug != NULL)
	fprintf(debug,
	"refresh:move cursor from real=(v=%d,h=%d) to virtual=(v=%d,h=%d)\n",
		real_vpos,real_hpos,virt_vpos,virt_hpos);
#endif
   if (real_hpos != virt_hpos ||  real_vpos != virt_vpos)
      real_locate(virt_vpos,virt_hpos);
#ifdef	DEBUG
    if (debug != NULL)
	fprintf(debug,"<-- refresh_screen()\n");
#endif
}
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* bottom()	Move cursor to `bottom' line of screen.			*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#define bottom() locate(24,OFFSET)

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* crock_draw()	Super-hairy hand drawer.				*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* Inputs are: */
/* T		value (0:59) of hand to draw				*/
/* type  	(0:3) 0=erase, 1=hours, 2=minutes, 3=seconds		*/
/* length	hand length						*/
/* A									*/
/* Z									*/
/* Z2									*/
/* save_hpos[]	saved horizontal positions				*/
/* save_vpos[]	saved vertical positions				*/
/* STARH	horizontal position of centre (constant)		*/
/* STARV	vertical position of centre (constant)			*/
/* hand_data[]	hands data (constants)					*/
/* h_incr[]	Horizontal increments (constants)			*/
/* v_incr[]	Vertical increments (constants)				*/

VOID crock_draw(){
   static UCHAR i;		/* byte counter in hand_data[]		*/
   static SHORT vpos;		/* Vertical cursor position (1:nn)	*/
   static SHORT hpos;		/* Horizontal cursor position (1:nn)	*/
   static SHORT quadrant;	/* Quadrant (0,1,2,3) of crock picture	*/
   static UCHAR slope;		/* slope				*/

   old_hpos = old_vpos = UNDEF;	/* zap old cursor position, move first.	*/
   hpos = STARH;		/* desired cursor position begins at ..	*/
   vpos = STARV;		/* ... centre of clock.			*/
   quadrant = T / 15;		/* find out what quadrant hand is in ..	*/
   TT = T % 15;			/* ... (0,1,2,3 clockwise)		*/
				/* save quadrant (0,1,2,3) for later	*/

#ifdef	NARROW
/*
 *	This code is to make it possible to run this program on PCs
 *	with a 40-column wide screen.  The problem is that the crock
 *	picture is 41 characters: the second's hand will write over
 *	the rightmost part of the crock picture.  Solution: shorten
 *	the second's hand when between xx:xx:10 and xx:xx:25, inclusive.
 *	[NOTE: `length' is the hand length, it's a hand type.]
 */
   if (narrow &&			/* [304] 40 character screen?	*/
       ((quadrant == 0 && TT > 10) ||	/* [306] range [10:15] ?	*/
	(quadrant == 1 && TT < 5)) &&	/* [306] or range [16:25] ?	*/
       length > 6)			/* [304] and seconds hand?	*/
#ifdef	NARROW
      length = 8;			/* [304] yes, change hand type	*/
#else
       length = 6;			/* [307] ditto			*/
#endif
/*
 *	Another problem with 40-column screens: if reversed crock picture,
 *	the picture is actually 42 characters, as the "10" would be in
 *	column 40:41.  The solution is to shorten the second's data to the
 *	length of minute hand when passing the "10" location.
 */
#ifdef	REVCLK			/* [304]				*/
   if (narrow && bkward &&	/* [304] narrow and backwards?		*/
       !quadrant && TT == 10)	/* [306] and `10' ?			*/
      length = 6;		/* [304] yes, make hand even shorter	*/
#endif				/* [304]				*/
#endif				/* [304]				*/
   if (quadrant & 1)		/* if in quad 1 or 3 then set remainder ... */
     TT = 15-TT;		/* ... to mirror image of that (0 or 2) */
   slope = (UCHAR) TT;		/* using remainder, get proper hand-slope */
   i = 0;			/* initialize byte counter to first position*/
draw9:
   vpos += v_incr[quadrant] * (hand_data[slope][i++]-'0');
				/* Add or subtract vertical movement	*/
  hpos += h_incr[quadrant] * (hand_data[slope][i++]-'0');
				/* Add or subtract horizontal movement	*/
  byte = hand_data[slope][i++]-'0';
  if (byte < 5)				/* If not a special marker ...	*/
     goto draw0;			/* ... hack normally		*/
  if (length != byte)			/* If not end of hand ...	*/
     goto draw9;			/* ... continue drawing hand	*/

   while (Z++ < 0){
        save_hpos[Z2]   = -1;	/* [28] must zap remaining positions	*/
	save_vpos[Z2++] = -1;	/* [28] in the save_hpos[], save_vpos[]	*/
   }
   return;			/* When all positions covered, return */

/* Output a char of the hand in current position if safe. */

draw0:
   if (A){			/* If doing overwrite checking, do them */
      for (TT=A,Index2=0; ++TT; Index2++){
			      /* Current X match anything in table? */
         if (hpos == save_hpos[Index2] &&
				/* If X matches, does Y also match? */
	     vpos == save_vpos[Index2])
	       goto draw9;	/* If so, then this position is occupied. */
	 }
      }
				/* Safe, can actually output char. */
				/* See if either different from old. */
   if (hpos != old_hpos || vpos != old_vpos){
      locate(vpos,hpos);	/* Must send new coordinates */
      old_hpos = hpos;		/* save old */
      old_vpos = vpos;
   }

   old_hpos++;			/* Bump horiz pos since output moves cursor */
				/* Output appropriate char for this hand. */
   add_character(type == SECOND ? sec_char[quadrant][byte] : hand_char[type]);

   if (Z >= 0) goto draw9;	/* If hit end of table, don't remember pos. */
    save_hpos[Z2]   = hpos;	/* Otherwise remember, so we won't overwrite*/
    save_vpos[Z2++] = vpos;
    if (++Z) goto draw9;	/* Bump table, and draw another char ... */
    return;			/* ... unless out of room. */
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* 12.	Main program routines.						*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* doquit()	Normal_exit handler.					*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
SIGNAL doquit(){		/* [312] */
     bottom();			/* get to bottom line of screen		*/
     restore_world();		/* restore any modes we may have set	*/
     exitt();			/* return to superior			*/
}
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* kpjbreak()	My own CTRL/BREAK handler.				*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef __TURBOC__
#ifdef CTRLBRK
VOID kpjbreak(){
	getch();			/* read CTRL/BREAK character	*/
	doquit();			/* quit normally		*/
}
#endif
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* _Abort()	AMIGA Manx/Aztec C CTRL/C handler.			*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
#ifdef	AMIGA
#ifdef	MANX
VOID _Abort(){
     doquit();			/* CTRL/C -- die naturally		*/
}
#endif
#endif
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* begin()	Initialize world, paint clock picture.			*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
VOID begin(){
#ifdef	DEBUG
   if (debug != NULL){
	   fprintf(debug,"begin:DEBUG");
#ifdef	VERSION
	   fprintf(debug,",VERSION=\"%s\"",VERSION);
#else
	   fprintf(debug,",VERSION off");
#endif
#ifdef	DVIDEO
	   fprintf(debug,",DVIDEO on");
#else
	   fprintf(debug,",DVIDEO off");
#endif
#ifdef	NARROW
	   fprintf(debug,",NARROW on");
#else
	   fprintf(debug,",NARROW off");
#endif
#ifdef	REVCLK
	   fprintf(debug,",REVCLK on");
#else
	   fprintf(debug,",REVCLK off");
#endif
#ifdef	OPTIMIZER
	    fprintf(debug,",OPTIMIZER on");
#else
	   fprintf(debug,",OPTIMIZER off");
#endif
	   fprintf(debug,"\n");
   }
#endif
   init_world();		/* [306] do system dependent initiation	*/
   real_clear();		/* [306] clear screen			*/
   locate(1,10);		/* Output initial clock picture		*/
#ifdef	REVCLK
				/* [312] */
   add_str(bkward ? " 1 , , , ,12 , , , , 11" :"11 , , , ,12 , , , ,  1");
#else
   add_str("11 , , , ,12 , , , ,  1");
#endif
   locate(2,34);  add_character('\'');
   locate(3,36);  add_character('\'');
   locate(4,38);  add_character('\'');
   locate(5,40);  add_character('\'');
#ifdef	REVCLK
#ifdef	NARROW
   locate(6,41-bkward*narrow);/* [304] make `10' come out in narrow	*/
#else				/* [304]				*/
   locate(6,41);		/* [304]				*/
#endif				/* [304]				*/
#else
   locate(6,41);		/* [304]				*/
#endif
#ifdef	REVCLK
	     if (bkward)
		  add_str("10");
	     else
#endif
		  add_character('2');
   locate(7,41);  add_character(',');
   locate(8,41);  add_character(',');
   locate(10,41); add_character('\'');
   locate(11,41); add_character('\'');
   locate(12,41);
#ifdef	REVCLK
					/* [312] */
   add_character(bkward ? '9' : '3');
#else
   add_character('3');
#endif

   locate(13,41); add_character(',');
   locate(14,41); add_character(',');
   locate(16,41); add_character('\'');
   locate(17,41); add_character('\'');
   locate(18,41); 
#ifdef	REVCLK
						/* [312] */
   add_character(bkward ? '8' : '4');	
#else
   add_character('4');	
#endif

   locate(19,40); add_character(',');
   locate(20,38); add_character(',');
   locate(21,36); add_character(',');
   locate(22,34); add_character(',');
   locate(23,32);
#ifdef	REVCLK
						/* [312] */
   add_character(bkward ? '7' : '5');
#else
   add_character('5');
#endif

   locate(23,29); add_character('\'');
   locate(23,27); add_character('\'');
   locate(23,25); add_character('\'');
   locate(23,23); add_character('\'');
   locate(23,21); add_character('6');
   locate(23,19); add_character('\'');
   locate(23,17); add_character('\'');
   locate(23,15); add_character('\'');
   locate(23,13); add_character('\'');
   locate(23,10);
#ifdef	REVCLK
						/* [312] */
   add_character(bkward ? '5' : '7');
#else
   add_character('7');
#endif
   locate(22,8);  add_character(',');
   locate(21,6);  add_character(',');
   locate(20,4);  add_character(',');
   locate(19,2);  add_character(',');
   locate(18,1);
#ifdef	REVCLK
						/* [312] */
   add_character(bkward ? '4' : '8');
#else
   add_character('8');
#endif

   locate(17,1);  add_character('\'');
   locate(16,1);  add_character('\'');
   locate(14,1);  add_character(',');
   locate(13,1);  add_character(',');
   locate(12,1);
#ifdef	REVCLK
						/* [312] */
   add_character(bkward ? '3' : '9');
#else
   add_character('9');
#endif
   locate(11,1);  add_character('\'');
   locate(10,1);  add_character('\'');
   locate(8,1);   add_character(',');
   locate(7,1);   add_character(',');
   locate(6,1);
#ifdef	REVCLK
	       if (bkward)
		  add_character('2');
	       else
#endif
		  add_str("10");
   locate(5,2);   add_character('\'');
   locate(4,4);   add_character('\'');
   locate(3,6);   add_character('\'');
   locate(2,8);   add_character('\'');
#ifdef	VERSION
   if (version){			/* [303] `-v' ?			*/
#ifdef	NARROW
      if (narrow)			/* [304] narrow screeen?	*/
         locate(24,1);			/* [304] yes			*/
      else				/* [304]			*/
#endif
         locate(6,45);

      add_str("CROCK ");
      add_str(VERSION);
#ifdef	__TURBOC__
      add_str(" \304\304 Turbo C");
#endif
#ifdef	MSDOS
      add_str(" \304\304 Microsoft C");
#endif
#ifdef	GNUDOS
      add_str(" \304\304 Gnu C");
#endif
   }					/* [303]			*/
#endif
   locate(STARV,STARH);			/* Draw centre			*/
   add_character(CENTRE);		/* [306] . . .			*/

#ifdef	DEBUG
   if (debug != NULL){
      fprintf(debug,"initialize old_hour, old_minute, old_second\n");
      fprintf(debug,"clear save_hpos[], save-vpos[]\n");
   }
#endif
   old_hour = old_minute = old_second = UNDEF;
					/* Initialize old values	*/
   for (i=0; i < POSMAX; i++)
       save_hpos[i] = save_vpos[i] = UNDEF;	/* not used as yet	*/
#ifdef DCROCK
   if (dcrock){
#ifdef	NARROW
	if (narrow) locate(NCVPOS,NCHPOS);	/* [306] narrow format	*/
	else
#endif
		locate(DCVPOS,DCHPOS);		/* [306] wide format	*/
	add_str("hh:mm:ss");			/* output it		*/
   }
#endif
}
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
/* main()	Main program.						*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	*/
VOID
#ifdef	ARGV
main(argc,argv) char *argv[];
#else
main()
#endif
{
	/* Original program hacked up by GLS */
	/* 10X/20X version hacked by KLH. */
	/* Some 10X modifications done by EAK. */

#ifdef	ARGV
    int i,j;
    char tecken;

#endif

#ifdef	ARGV
    progname = *argv;
#endif

#ifdef	X11
    ...parse X11 arguments...
#endif

#ifdef	ARGV
    if (argc > 1)
	for (i=1; i < argc; i++){	/* Handle arguments */
	     if (argv[i][0] == '-' && argv[i][1] != '\0'){
		for (j = 1; j < strlen(argv[i]); j++){
		    tecken = argv[i][j];
#ifdef	DEBUG
		    if (tecken == 'D'){
			if (debug) continue;
			debug = stderr;
			if (i >= argc-1) continue;
			if (*argv[i+1] == '-') continue;
			i++;
			debug = fopen(argv[i],"wb");
			if (debug == NULL){
			   fprintf(stderr,"cannot open \"%s\" for output\n",
				   argv[i]);
			   exit(1);
		        }
			i--;
			continue;
		     } /* end if */
#endif
#ifdef	DCROCK
		     if (tecken == 'd') dcrock = 1;
#endif
#ifdef	REVCLK
		     if (tecken == 'b') bkward = 1;
#endif
#ifdef	VERSION
		     if (tecken == 'v') version = 1;
#endif
#ifdef	NARROW
		     if (tecken == 'n') narrow = 1;		/* [304] */
#endif
		} /* end for */
	    } /* end if */
	} /* end for */
#endif

    begin();			/* initialize and paint screen		*/

   /* Start a new clock picture here */

    for (;;){
#ifdef	X11
	   ...check for X11 event...
#endif
	   timex(&hour,&minute,&second);	/* get wall-clock time */
#ifdef	DCROCK
	   hr = (UCHAR) hour;			/* save unscaled hour */
#endif
	   hour = (SHORT) (5*(hour%12)+(minute/12));   /* compute hour */
#ifdef	REVCLK
	   if (bkward){
		hour   = (60-hour  ) % 60;
		minute = (60-minute) % 60;
		second = (60-second) % 60;
	   }
#endif
	   if (old_hour != hour){		/* no need to draw anything */
	        length  = 5;			/* length of hour hand */
		A       = 0;			/* no overwrite check */
		if (old_hour != UNDEF){		/* skip erase 1st time? */
		    type    = ERASE;		/* erasing */
		    Z       = 0;	/* mung save_hpos, save_vpos */
		    T       = old_hour;		/* time to un-draw */
		    crock_draw();		/* un-draw old hour */
		}
#ifdef DCROCK
		if (dcrock){
#ifdef	NARROW
		   if (narrow) locate(NCVPOS,NCHPOS);
		   else
#endif
			   locate(DCVPOS,DCHPOS);	/* hour position */
		   print_word("%02d",hr);	/* [306] unscaled hour */
	        }
#endif
		type    = HOUR;		/* drawing hour			*/
		Z       = -12;		/* -len of save_hpos, save_vpos	*/
		Z2      = 0;		/* start from beginning		*/
		T       = hour;		/* time to draw			*/
		crock_draw();		/* draw				*/
		old_hour = hour;	/* remember what hour		*/
	   }

	   if (old_minute != minute){		/* no need to draw anything */
		length  = 6;			/* length of minute hand */
		A       = -12;			/* neg length of used space */
		if (old_minute != UNDEF){	/* skip erasing 1st time? */
		      type    = ERASE;		/* erasing */
		      Z       = 0;	/* no mung save_hpos[], save_vpos[] */
		      Z2      = 12;	/* pos len of save_hpos, save_vpos  */
		      T       = old_minute;	/* this time is erased */
		      crock_draw();		/* un-draw */
	        }
#ifdef	DCROCK
		if (dcrock){
#ifdef	NARROW
		   if (narrow) locate(NCVPOS,NCHPOS+3);
		   else
#endif
			   locate(DCVPOS,DCHPOS+3);	/* minutes position */
		   print_word("%02d",minute);	/* [306] output it */
	        }
#endif
		type    = MINUTE;		/* minute hand */
		Z       = -18;			/* used space */
		T       = minute;		/* time to draw */
		crock_draw();			/* draw hand */
		old_minute = minute;		/* remember what minute */
	   }

	   if (old_second != second){		/* no need to draw anything */
		length	= 7;			/* length of seconds hand */
		A	= -(18+12);		/* hour+minute stuff */
		if (old_second != UNDEF){	/* skip erasing 1st time? */
		      type   = ERASE;		/* erasing */
		      Z      = 0;	/* no mung save_hpos[]/save_vpos[] */
		      T      = old_second;	/* this time to erase */
		      crock_draw();		/* un-draw */
	        }
#ifdef	DCROCK
		if (dcrock){
#ifdef	NARROW
		   if (narrow) locate(NCVPOS,NCHPOS+6);
		   else
#endif
			   locate(DCVPOS,DCHPOS+6);	/* seconds position */
		   print_word("%02d",second);	/* [306] output it */
	        }
#endif
		type   = SECOND;		/* seconds */
		T      = second;		/* this time to be drawn */
		Z      = ANYTHING;		/* dummy */
		crock_draw();			/* draw hand */
		old_second = second;		/* remember what second */
	   }
	   refresh_screen();			/* [306] refresh screen	*/
	   zleep();				/* sleep a second */
#ifdef	HASUSERX
	   if (user_x()){
		doquit();			/* user input, quit	*/
		begin();			/* returned, reinitialize */
	   }
#endif
	} /* end for */
/* NOTREACHED */
}
