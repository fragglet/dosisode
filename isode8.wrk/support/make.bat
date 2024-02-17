@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del *.o
	del *.c
	del isoc.exe
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.h
	del *.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	set defines=5
	set dir=support
	call %isode%\utils\cc isoc
	gcc -o isoc @isoc.lnk
	strip isoc
	copy /b %ISODE%\utils\stub.exe+isoc isoc.exe >nul:
	del isoc
	goto end
:bad_param
	echo unknown option %1
:end
