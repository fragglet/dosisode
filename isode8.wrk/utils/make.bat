@echo off
if not "%1." == "clean." goto check_tidy
	del *.o
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	goto end
:check_null
if not "%1." == "." goto bad_param
	gcc -o pass1 pass1.c
	copy /b %ISODE%\utils\stub.exe+pass1 pass1.exe >nul:
	del pass1
	gcc -o string_replace string_replace.c
	copy /b %ISODE%\utils\stub.exe+string_replace string_replace.exe >nul:
	del string_replace
	goto end
:bad_param
	echo unknown option %1
:end
