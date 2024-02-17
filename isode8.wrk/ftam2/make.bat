@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del *.o
	del *.c
	del *.a
	del ftam.exe
	del ftam
	del %isode_orig%\ftam2\docs_tables.*
	del %isode_orig%\ftam2\docs-types.*
	del %isode_orig%\ftam2\*.ph
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.h
	del *.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	set dir=ftam2
	if exist %isode_orig%\ftam2\docs_tables.c goto miss1
		cd %isode_orig%\ftam2
		copy ..\pepsy\ftam.ph >nul:
		%isode%\pepsy\pepsy -A -f -h -m docs.py
		cd %isode%\ftam2
:miss1
	set defines=5
	call %isode%\utils\h docs-types
	call %isode%\utils\h ftamsbr
	call %isode%\utils\h ftamsystem
	call %isode%\utils\h ftamuser
	call %isode%\utils\cc ftam
	call %isode%\utils\cc ftamuser
	call %isode%\utils\cc ftam-assoc
	call %isode%\utils\cc ftam-dir
	call %isode%\utils\cc ftam-get
	call %isode%\utils\cc ftam-glob
	call %isode%\utils\cc ftam-ls
	call %isode%\utils\cc ftam-mgmt
	call %isode%\utils\cc ftam-put
	call %isode%\utils\cc ftamsbr
	call %isode%\utils\cc docs_tables
	call %isode%\utils\cc ftamvrsn
echo Linking..
	gcc -o ftam @ftam.lnk
	strip ftam
	copy /b %ISODE%\utils\stub.exe+ftam ftam.exe >nul:
	del ftam
	goto end
:bad_param
	echo unknown option %1
:end
