@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del *.o
	del *.c
	del *.a
	del %isode_orig%\psap2\ps_tables.*
	del %isode_orig%\psap2\*.ph
	del %isode_orig%\psap2\ps-types.*
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.h
	del *.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	set dir=psap2
	if exist %isode_orig%\psap2\ps_tables.c goto miss1
		cd %isode_orig%\psap2
		%isode%\pepsy\pepsy -A -f -h -m ps.py
		cd %isode%\psap2
:miss1
	set defines=5
	call %isode%\utils\h  ps-types
	call %isode%\utils\cc ps_tables
	call %isode%\utils\cc psap2error
	call %isode%\utils\cc psapabort
	call %isode%\utils\cc psapactivity
	call %isode%\utils\cc psapexec
	call %isode%\utils\cc psapinitiate
	call %isode%\utils\cc psaplose
	call %isode%\utils\cc major1 psapmajor1
	call %isode%\utils\cc major2 psapmajor2
	call %isode%\utils\cc minor1 psapminor1
	call %isode%\utils\cc minor2 psapminor2
	call %isode%\utils\cc release1 psaprelease1
	call %isode%\utils\cc release2 psaprelease2
	call %isode%\utils\cc psapreport
	call %isode%\utils\cc psaprespond
	call %isode%\utils\cc resync1 psapresync1
	call %isode%\utils\cc resync2 psapresync2
	call %isode%\utils\cc psaprovider
	call %isode%\utils\cc psapselect
	call %isode%\utils\cc psaptoken
	call %isode%\utils\cc psap2vrsn
	set defines=0
	ar r temp.a @psap2.lnk >nul:
	copy temp.a libpsap2.a >nul:
	ar rs libpsap2.a
	del temp.a
	goto end
:bad_param
	echo unknown option %1
:end
