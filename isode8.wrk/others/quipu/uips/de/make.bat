@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del *.o
	del *.c
	del *.a
	del de.exe
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.h
	del *.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	set dir=others\quipu\uips\de
	set defines=5
	call %isode%\utils\h bind
	call %isode%\utils\h cnamelist
	call %isode%\utils\h config
	call %isode%\utils\h demanifest
	call %isode%\utils\h filter
	call %isode%\utils\h mapatts
	call %isode%\utils\h mapphone
	call %isode%\utils\h namelist
	call %isode%\utils\h types
	call %isode%\utils\h util
	call %isode%\utils\h destrings
	call %isode%\utils\h query
	call %isode%\utils\cc de
	call %isode%\utils\cc bind
	call %isode%\utils\cc init
	call %isode%\utils\cc util
	call %isode%\utils\cc filter
	call %isode%\utils\cc people
	call %isode%\utils\cc ou
	call %isode%\utils\cc org
	call %isode%\utils\cc country
	call %isode%\utils\cc cname
	call %isode%\utils\cc video
	call %isode%\utils\cc list
	call %isode%\utils\cc atts
	call %isode%\utils\cc pager
	call %isode%\utils\cc mapatt
	call %isode%\utils\cc dehelp
	call %isode%\utils\cc rawinput
	call %isode%\utils\cc mapphone
	gcc -o de @de.lnk
	strip de
	copy /b %ISODE%\utils\stub.exe+de de.exe >nul:
	del de
	goto end
:bad_param
	echo unknown option %1
:end
