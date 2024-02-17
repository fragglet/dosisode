@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del *.o
	del *.c
	del *.a
	del pepy.exe
	del posy.exe
	del %isode_orig%\pepy\upepy-*.*
	del %isode_orig%\pepy\vpepy-*.*
	del %isode_orig%\pepy\*.ph
	del %isode_orig%\pepy\univ-types.h
	del %isode_orig%\pepy\univ-types.c
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.h
	del *.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	set dir=pepy
	set defines=2
	call %isode%\utils\h pepy
	call %isode%\utils\cc pepy
	call %isode%\utils\cc pepyvrsn
	call %isode%\utils\cc pepy_do
	call %isode%\utils\cc pepy_undo
	copy lex.c_new lex.c >nul:
	call %isode%\utils\cc yacc
	del lex.c
	call %isode%\utils\cc pepy_misc
	gcc -o pepy -L../psap -L../compat -L../unix/lib @pepy.lnk
	strip pepy
	copy /b %ISODE%\utils\stub.exe+pepy pepy.exe >nul:
	del pepy
	call %isode%\utils\cc posy
	gcc -o posy -L../psap -L../compat -L../unix/lib @posy.lnk
	strip posy
	copy /b %ISODE%\utils\stub.exe+posy posy.exe >nul:
	del posy
	if exist %isode_orig%\pepy\upepy-01.c goto miss1
		cd %isode_orig%\pepy
		%isode%\pepy\posy -f -h -m -o UNIV-types.py ../pepsy/UNIV.py
		%isode%\pepy\pepy -a PY_advise -m -A -b UPEPY ../pepsy/UNIV.py
		%isode%\pepy\pepy UNIV-types.py
		%isode%\pepy\pepy -a PY_advise -m -b VPEPY UNIV-types.py
		%isode%\pepy\pepy -a PY_advise -m testdebug.py
		cd %isode%\pepy
:miss1
	call %isode%\utils\h univ-types
	call %isode%\utils\cc upepy-01
	call %isode%\utils\cc upepy-02
	call %isode%\utils\cc upepy-03
	call %isode%\utils\cc upepy-04
	call %isode%\utils\cc upepy-05
	call %isode%\utils\cc upepy-06
	call %isode%\utils\cc upepy-07
	call %isode%\utils\cc upepy-08
	call %isode%\utils\cc upepy-09
	call %isode%\utils\cc upepy-10
	call %isode%\utils\cc upepy-11
	call %isode%\utils\cc upepy-12
	call %isode%\utils\cc upepy-13
	call %isode%\utils\cc upepy-14
	call %isode%\utils\cc upepy-15
	call %isode%\utils\cc upepy-16
	call %isode%\utils\cc upepy-17
	call %isode%\utils\cc upepy-18
	call %isode%\utils\cc upepy-19
	call %isode%\utils\cc upepy-20
	call %isode%\utils\cc upepy-21
	call %isode%\utils\cc upepy-22
	call %isode%\utils\cc upepy-23
	call %isode%\utils\cc upepy-24
	call %isode%\utils\cc upepy-25
	call %isode%\utils\cc upepy-26
	call %isode%\utils\cc upepy-27
	call %isode%\utils\cc upepy-28
	call %isode%\utils\cc upepy-29
	call %isode%\utils\cc upepy-30
	call %isode%\utils\cc upepy-31
	call %isode%\utils\cc upepy-32
	call %isode%\utils\cc upepy-33
	call %isode%\utils\cc upepy-34
	call %isode%\utils\cc upepy-35
	call %isode%\utils\cc upepy-36
	call %isode%\utils\cc upepy-37
	call %isode%\utils\cc upepy-38
	call %isode%\utils\cc upepy-39
	call %isode%\utils\cc upepy-40
	call %isode%\utils\cc upepy-41
	call %isode%\utils\cc upepy-42
	call %isode%\utils\cc upepy-43
	call %isode%\utils\cc upepy-44
	call %isode%\utils\cc upepy-45
	call %isode%\utils\cc upepy-46
	call %isode%\utils\cc upepy-47
	call %isode%\utils\cc upepy-48
	call %isode%\utils\cc upepy-49
	call %isode%\utils\cc upepy-50
	call %isode%\utils\cc upepy-51
	call %isode%\utils\cc upepy-52
	call %isode%\utils\cc vpepy-01
	call %isode%\utils\cc vpepy-02
	call %isode%\utils\cc vpepy-03
	call %isode%\utils\cc vpepy-04
	call %isode%\utils\cc vpepy-05
	call %isode%\utils\cc vpepy-06
	call %isode%\utils\cc vpepy-07
	call %isode%\utils\cc vpepy-08
	call %isode%\utils\cc vpepy-09
	call %isode%\utils\cc vpepy-10
	call %isode%\utils\cc vpepy-11
	call %isode%\utils\cc vpepy-12
	call %isode%\utils\cc vpepy-13
	call %isode%\utils\cc vpepy-14
	call %isode%\utils\cc vpepy-15
	call %isode%\utils\cc vpepy-16
	call %isode%\utils\cc vpepy-17
	call %isode%\utils\cc vpepy-18
	call %isode%\utils\cc vpepy-19
	call %isode%\utils\cc vpepy-20
	call %isode%\utils\cc vpepy-21
	call %isode%\utils\cc vpepy-22
	call %isode%\utils\cc vpepy-23
	call %isode%\utils\cc vpepy-24
	call %isode%\utils\cc vpepy-25
	call %isode%\utils\cc vpepy-26
	call %isode%\utils\cc vpepy-27
	call %isode%\utils\cc vpepy-28
	call %isode%\utils\cc vpepy-29
	call %isode%\utils\cc vpepy-30
	call %isode%\utils\cc vpepy-31
	call %isode%\utils\cc vpepy-32
	call %isode%\utils\cc vpepy-33
	call %isode%\utils\cc vpepy-34
	call %isode%\utils\cc vpepy-35
	call %isode%\utils\cc py_pp
	call %isode%\utils\cc testdebug
	call %isode%\utils\cc pepyvrsn
	set defines=0
	ar r temp.a @lpepy.lnk >nul:
	copy temp.a libpepy.a >nul:
	ar rs libpepy.a
	del temp.a
	goto end
:bad_param
	echo unknown option %1
:end
