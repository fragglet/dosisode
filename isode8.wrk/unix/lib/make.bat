@echo off
if not "%1." == "clean." goto check_tidy
	del *.o
	del *.a
	del dns\*.o
	del dns\*.a
	del cur\*.o
	del cur\*.a
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.o
	del dns\*.o
	del dns\*.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	call cc socket
	call cc unix2dos
	call cc ntohs
	call cc writev
	call cc get
	call cc file_extra
	call cc inet
	call cc exec
	call cc fiddle
	call cc ecvt
	call cc signal
	call cc time
	call cc popen
	call cc tgetent
	cd dns
	call ..\cc res_comp
	call ..\cc res_debug
	call ..\cc res_init
	call ..\cc res_mkquery
	call ..\cc res_query
	call ..\cc res_send
	call ..\cc gethostnamadr
	call ..\cc netbyaddr
	call ..\cc netbyname
	call ..\cc getnetent
	call ..\cc getproto
	call ..\cc protoent
	call ..\cc protoname
	call ..\cc servbyname
	call ..\cc servbyport
	call ..\cc getservent
	call ..\cc herror
	call ..\cc sethostent
	cd ..
	cd cur
	call ..\cc attrib
	call ..\cc beep
	call ..\cc border
	call ..\cc boxes
	call ..\cc charadd
	call ..\cc chardel
	call ..\cc charget
	call ..\cc charins
	call ..\cc charpick
	call ..\cc clrtobot
	call ..\cc clrtoeol
	call ..\cc endwin
	call ..\cc initscr
	call ..\cc linedel
	call ..\cc lineins
	call ..\cc longname
	call ..\cc move
	call ..\cc mvcursor
	call ..\cc newwin
	call ..\cc options
	call ..\cc overlay
	call ..\cc refresh
	call ..\cc scrreg
	call ..\cc setmode
	call ..\cc setterm
	call ..\cc stradd
	call ..\cc strget
	call ..\cc tabsize
	call ..\cc termmisc
	call ..\cc unctrl
	call ..\cc update
	call ..\cc winclear
	call ..\cc windel
	call ..\cc winerase
	call ..\cc winmove
	call ..\cc winscrol
	call ..\cc wintouch
	call ..\cc cursesio
	call ..\cc wprintw
	call ..\cc getch
	cd ..
	echo Creating library..
	ar r temp.a @unix.lnk >nul:
	copy temp.a libunix.a >nul:
	ar rs libunix.a
	del temp.a
	goto end
:bad_param
	echo unknown option %1
:end
