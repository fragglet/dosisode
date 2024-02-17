@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del *.o
	del *.c
	del *.a
	del sd.exe
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.h
	del *.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	set dir=others\quipu\uips\sd
	set defines=5
	call %isode%\utils\h filt
	call %isode%\utils\h calls
	call %isode%\utils\h sequence
	call %isode%\utils\h widget
	call %isode%\utils\h wdgtdefs
	call %isode%\utils\h symtab
	call %isode%\utils\h y_tab
	call %isode%\utils\cc y_tab
	call %isode%\utils\cc calls
	call %isode%\utils\cc main
	call %isode%\utils\cc widget
	call %isode%\utils\cc help
	call %isode%\utils\cc sequence
	call %isode%\utils\cc filt
	gcc -o sd @sd.lnk
	strip sd
	copy /b %ISODE%\utils\stub.exe+sd sd.exe >nul:
 	del sd
	goto end
:bad_param
	echo unknown option %1
:end
