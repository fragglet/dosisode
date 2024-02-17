@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del *.o
	del *.c
	del *.a
	del %isode_orig%\ronot\ronot_tables.*
	del %isode_orig%\ronot\ronot-types.*
	del %isode_orig%\ronot\*.ph
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.h
	del *.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	set dir=ronot
	if exist %isode_orig%\ronot\ronot_tables.c goto miss1
		cd %isode_orig%\ronot
		%isode%\pepsy\pepsy -A -f -h -m ronot.py
		cd %isode%\ronot
:miss1
	set defines=5
	call %isode%\utils\h ronot-types
	call %isode%\utils\cc ronot_tables
	call %isode%\utils\cc ronotabort
	call %isode%\utils\cc bind1 ronotbind1
	call %isode%\utils\cc bind2 ronotbind2
	call %isode%\utils\cc ronotlose
	call %isode%\utils\cc unbind1 ronotunbind1
	call %isode%\utils\cc unbind2 ronotunbind2
	set defines=0
	ar r temp.a @ronot.lnk >nul:
	copy temp.a libronot.a >nul:
	ar rs libronot.a
	del temp.a
	goto end
:bad_param
	echo unknown option %1
:end
