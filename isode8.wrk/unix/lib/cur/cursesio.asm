	TITLE   PCcurses BIOS Control Functions for MicroSoft Assembler
	NAME	CURSESIO
	PAGE	46,132
	;****************************************************************
	;*			 CURSESIO.ASM				*
	;*								*
	;* This file contains 'C' functions for the MicroSoft 'C' com-	*
	;* piler v.4.0, and for Borland Turbo 'C'. It exercises a num-	*
	;* ber of BIOS video calls, and is intended for inclusion in	*
	;* a curses library package.					*
	;*								*
	;* The two files FARNEAR.INC and SMALHUGE.INC each contain one	*
	;* EQUate. These define the module's memory model.		*
	;*								*
	;****************************************************************
	;* This version of curses is based on ncurses, a curses version	* 
	;* originally written by Pavel Curtis at Cornell University.	*
	;* I have made substantial changes to make it run on IBM PC's,	*
	;* and therefore consider myself free to make it public domain.	*
	;*		Bjorn Larsson (...mcvax!enea!infovax!bl)	*
	;****************************************************************
	;* Author: Bjorn Larsson					*
	;* Revised:							*
	;* 1.0:	Release:					870515	*
	;* 1.1:	Bad error in curseskeytst(): JZ -> JNZ!		870911	*
	;* 1.2:	Changed call sequence to some routines, thanks		*
	;*	to S. Creps. Changed segment name in far code		*
	;*	mode, thanks to N.D. Pentcheff:			881002	*
	;* 1.3:	Changes in 'C' modules for checking with		*
	;*	MSC -W3, Turbo'C' -w -w-pro checkes:		881005	*
	;****************************************************************
	;
	INCLUDE	FARNEAR.INC		;DEFINE FAR OR NEAR CALL SEQUENCE
	INCLUDE	SMALHUGE.INC		;DEFINE FAR OR NEAR DATA ACCESS
	;
SYSTEM	EQU	21H			;SYSTEM CALL
BRKCHK	EQU	33H			;BREAK SET/CHECK FUNCTION CODE
	;
	if far_call			;OTHER TEXT NAME IF FAR CALLS
CURSESIO_TEXT	SEGMENT	BYTE PUBLIC 'CODE'
	ASSUME	CS: CURSESIO_TEXT
	else
_TEXT	SEGMENT  BYTE PUBLIC 'CODE'
	ASSUME  CS: _TEXT
	endif
	;
	;****************************************************************
	;* Function entry and exit macros, and parameter fetch macro.	*
	;* Used by all functions.					*
	;****************************************************************
	;
c_entry	MACRO	f_name
	;
	if far_call
&f_name	proc far
	else
&f_name	proc near
	endif
	push	bp
	mov	bp,sp
	push	di
	push	si
	;
	ENDM
	;
c_exit	MACRO	f_name
	;
	pop	si
	pop	di
	pop	bp
	ret
&f_name	endp
	;
	ENDM
	;
g_parm	MACRO	reg,p_num
	if	far_call
	mov	&reg,[bp+&p_num*2+4]
	else
	mov	&reg,[bp+&p_num*2+2]
	endif
	;
	ENDM
	;
	DB	'@(#)cursesio.asm v1.3 - 881005', 0
	;
	PAGE
	;****************************************************************
	;*			_cursescattr				*
	;*								*
	;* void _cursescattr(chr,attr)					*
	;*								*
	;* Writes char 'chr' with attributes 'attr' to the current cur-	*
	;* sor location.						*
	;****************************************************************
	PUBLIC	__cursescattr
	;
	c_entry __cursescattr
	MOV	AH,9
	MOV	BH,0		;USE PAGE 0
	g_parm	AL,1		;GET CHR PARAMETER
	g_parm	BL,2		;GET ATTR PARAMETER
	MOV	CX,1		;PUT 1 CHARACTER
	INT	10H
	c_exit	__cursescattr
	;
	;****************************************************************
	;*			_cursescursor				*
	;*								*
	;* void _cursescursor(row,column)				*
	;*								*
	;* Sets the cursor position in video page 0. 'row' and 'column'	*
	;* are the cursor address. If 'row' is set to 25, no cursor at	*
	;* all is displayed.						*
	;****************************************************************
	PUBLIC	__cursescursor
	;
	c_entry __cursescursor
	MOV	AH,2
	MOV	BH,0		;USE PAGE 0
	g_parm	DH,1		;GET ROW PARAMETER
	g_parm	DL,2		;GET COLUMN PARAMETER
	INT	10H
	c_exit	__cursescursor
	;
	;****************************************************************
	;*			_cursesgcols				*
	;*								*
	;* int _cursesgcols()						*
	;*								*
	;* Return the current number of columns on the screen.		*
	;****************************************************************
	PUBLIC	__cursesgcols
	;
	c_entry	__cursesgcols
	MOV	AH,15
	INT	10H
	MOV	AL,AH
	XOR	AH,AH
	c_exit	__cursesgcols
	;
	;****************************************************************
	;*			_cursesputc				*
	;*								*
	;* void _cursesputc(chr,colour)					*
	;*								*
	;* Output character 'chr' to screen in tty fashion. If a colour	*
	;* mode is active, the character is written with colour		*
	;* 'colour'.							*
	;****************************************************************
	PUBLIC	__cursesputc
	;
	c_entry	__cursesputc
	MOV	AH,14
	g_parm	AL,1		;GET CHR PARAMETER
	g_parm	BL,2		;GET COLOUR PARAMETER
	INT	10H
	c_exit	__cursesputc
	;
	;****************************************************************
	;*			_cursesscroll				*
	;*								*
	;* void _cursesscroll(urow,lcol,lrow,rcol,lines,attr)		*
	;*								*
	;* Scroll a window in the current page up or down. Urow, lcol,	*
	;* lrow,rcol are the window coordinats. lines is the number of	*
	;* lines to scroll. If 0, clears the window, if < 0 scrolls	*
	;* down, > 0 scrolls up. Blanks areas that are left, and sets	*
	;* character attributes to attr. If in a colour graphics mode,	*
	;* fills them with the colour 'attr' instead.			*
	;****************************************************************
	PUBLIC	__cursesscroll
	;
	c_entry	__cursesscroll
	g_parm	AL,5		;GET LINES PARAMETER
	MOV	AH,6
	TEST	AL,80H
	JZ	SHORT CS_1
	;
	MOV	AH,7
	NEG	AL
	;
CS_1:	g_parm	CH,1		;GET UROW PARAMETER
	g_parm	CL,2		;GET LCOL PARAMETER
	g_parm	DH,3		;GET LROW PARAMETER
	g_parm	DL,4		;GET RCOL PARAMETER
	g_parm	BH,6		;GET ATTR PARAMETER
	INT	10H
	c_exit	__cursesscroll
	;
	;****************************************************************
	;*			_cursesgcmode				*
	;*								*
	;* int _cursesgcmode()						*
	;*								*
	;* Return the current cursor type. Bits 8-15 of the return	*
	;* value is the start scan row, and bits 0-7 is the end scan	*
	;* row.								*
	;****************************************************************
	PUBLIC	__cursesgcmode
	;
	c_entry	__cursesgcmode
	MOV	AH,3
	INT	10H
	MOV	AX,CX
	c_exit	__cursesgcmode
	;
	;****************************************************************
	;*			_cursescmode				*
	;*								*
	;* void _cursescmode(startrow,endrow)				*
	;*								*
	;* Sets the cursor type to begin in scan line startrow and end	*
	;* in scan line endrow. Both values should be 0-31.		*
	;****************************************************************
	PUBLIC	__cursescmode
	;
	c_entry __cursescmode
	MOV	AH,1
	g_parm	CH,1		;GET STARTROW PARAMETER
	g_parm	CL,2		;GET ENDROW PARAMETER
	INT	10H
	c_exit	__cursescmode
	;
	;****************************************************************
	;*			 _curseskey				*
	;*								*
	;* int _curseskey()						*
	;*								*
	;* Returns the next key code struck at the keyboard. If the low	*
	;* 8 bits are 0, the upper bits contain the extended character	*
	;* code. If bit 0-7 are non-zero, the upper bits = 0.		*
	;****************************************************************
	PUBLIC	__curseskey
	;
	c_entry __curseskey
	MOV	AH,0
	INT	16H
	CMP	AL,0
	JZ	SHORT EXTKEY
	AND	AX,0FFH
EXTKEY:
	c_exit	__curseskey
	;
	;****************************************************************
	;*			_curseskeytst				*
	;*								*
	;* int _curseskeytst()						*
	;*								*
	;* Returns 1 if a character is available, 0 otherwise.		*
	;****************************************************************
	PUBLIC	__curseskeytst
	;
	c_entry __curseskeytst
	MOV	AH,1
	INT	16H
	JNZ	SHORT TST1
	MOV	AX,0
	JMP	SHORT EXTTST
TST1:	MOV	AX,1
EXTTST:
	c_exit	__curseskeytst
	;
	;****************************************************************
	;*			_cursesgcb				*
	;*								*
	;* int _cursesgcb()						*
	;*								*
	;* Returns 1 if MSDOS BREAK CHECK is on, otherwise 0.		*
	;****************************************************************
	PUBLIC	__cursesgcb
	;
	c_entry __cursesgcb
	MOV	AX,BRKCHK*256+0
	INT	SYSTEM
	XOR	AH,AH
	MOV	AL,DL
	c_exit	__cursesgcb
	;
	;****************************************************************
	;*			_cursesscb				*
	;*								*
	;* void _cursesscb(setting)					*
	;*								*
	;* Sets MSDOS BREAK CHECK according to 'setting'.		*
	;****************************************************************
	PUBLIC	__cursesscb
	;
	c_entry __cursesscb
	MOV	AX,BRKCHK*256+1
	g_parm	DL,1
	AND	DL,DL
	JZ	SHORT SCB1
	MOV	DL,1
SCB1:	INT	SYSTEM
	c_exit	__cursesscb
	;
	if far_call
CURSESIO_TEXT	ENDS
	else
_TEXT	ENDS
	endif
	if1
	%OUT	Pass 1 Completed
	else
	%OUT	Assembly Completed
	endif
	END
