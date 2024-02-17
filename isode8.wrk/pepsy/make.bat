@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del *.o
	del *.c
	del *.a
	del pepsy.exe
	del %isode_orig%\pepsy\univ_*.*
	del %isode_orig%\pepsy\*.ph
	del %isode_orig%\pepsy\univ-*.*
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.h
	del *.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	set dir=pepsy
	set defines=1
	call %isode%\utils\h pepsydefs
	call %isode%\utils\h pass2
	call %isode%\utils\h mine
	call %isode%\utils\h sym
	call %isode%\utils\cc pepsy
	call %isode%\utils\cc pepsyvrsn
	copy lex.c_new lex.c >nul:
	call %isode%\utils\cc pepsy-yacc
	del lex.c
	call %isode%\utils\cc pepsy_misc
	call %isode%\utils\cc pass2
	call %isode%\utils\cc etabs
	call %isode%\utils\cc dtabs
	call %isode%\utils\cc ptabs
	call %isode%\utils\cc dfns
	call %isode%\utils\cc mod
	gcc -o pepsy -L../psap -L../compat -L../unix/lib @pepsy.lnk
	strip pepsy
	copy /b %ISODE%\utils\stub.exe+pepsy pepsy.exe >nul:
	del pepsy
	if exist %isode_orig%\pepsy\UNIV_tables.c goto miss1
		cd %isode_orig%\pepsy
		%isode%\pepsy\pepsy -A -f -h -m UNIV.py
		cd %isode%\pepsy
:miss1
	call %isode%\utils\h univ-types
	copy univ-types.h %isode%\h\univ-types.h >nul:
	call %isode%\utils\h pepsy-driver
	set defines=1
	call %isode%\utils\cc univ_tables
	call %isode%\utils\cc enc
	call %isode%\utils\cc dec
	call %isode%\utils\cc fre
	call %isode%\utils\cc prnt
	call %isode%\utils\cc util
	call %isode%\utils\cc vprint
	call %isode%\utils\cc pepsy_str
	call %isode%\utils\cc py_advise
	set defines=0
	ar r temp.a @lpepsy.lnk >nul:
	copy temp.a libpepsy.a >nul:
	ar rs libpepsy.a
	del temp.a
	goto end
:bad_param
	echo unknown option %1
:end
