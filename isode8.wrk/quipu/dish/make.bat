@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del *.o
	del *.c
	del *.a
	del dish.exe
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.h
	del *.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	set dir=quipu\dish
	set defines=5
	call %isode%\utils\cc dish
	call %isode%\utils\cc add
	call %isode%\utils\cc bind
	call %isode%\utils\cc compare
	call %isode%\utils\cc delete
	call %isode%\utils\cc dishlib
	call %isode%\utils\cc dishhelp
	call %isode%\utils\cc edit
	call %isode%\utils\cc filteritem
	call %isode%\utils\cc fred
	call %isode%\utils\cc get_ava
	call %isode%\utils\cc get_filter
	call %isode%\utils\cc list
	call %isode%\utils\cc modify
	call %isode%\utils\cc modifyrdn
	call %isode%\utils\cc move
	call %isode%\utils\cc read
	call %isode%\utils\cc search
	call %isode%\utils\cc showattr
	call %isode%\utils\cc showentry
	call %isode%\utils\cc showname
	call %isode%\utils\cc user
	call %isode%\utils\cc pipe
	call %isode%\utils\cc dishvrsn
	gcc -o dish @dish.lnk
	strip dish
	copy /b %ISODE%\utils\stub.exe+dish dish.exe >nul:
	del dish
	goto end
:bad_param
	echo unknown option %1
:end
