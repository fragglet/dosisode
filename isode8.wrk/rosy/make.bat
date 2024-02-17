@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del *.o
	del *.c
	del *.a
	del rosy.exe
	del p-*.c_new
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.h
	del *.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	set dir=rosy
	set defines=0
	call %isode%\utils\h rosy-defs
	call %isode%\utils\cc rosy
	call %isode%\utils\cc rosyvrsn
	copy lex.c_new lex.c >nul:
	call %isode%\utils\cc yacc
	del lex.c
	gcc -o rosy -L../psap -L../compat -L../unix/lib @rosy.lnk
	strip rosy
	copy /b %ISODE%\utils\stub.exe+rosy rosy.exe >nul:
	del rosy
	set defines=0
	call %isode%\utils\cc rydiscard
	call %isode%\utils\cc rydispatch
	call %isode%\utils\cc rydsblock
	call %isode%\utils\cc rydserror
	call %isode%\utils\cc rydsresult
	call %isode%\utils\cc rydsurej
	call %isode%\utils\cc ryfind
	call %isode%\utils\cc rygenid
	call %isode%\utils\cc rylose
	call %isode%\utils\cc ryopblock
	call %isode%\utils\cc ryoper
	call %isode%\utils\cc ryopinvoke
	call %isode%\utils\cc rystub
	call %isode%\utils\cc rywait
	call %isode%\utils\cp rydiscard.c p-rydiscard.c_new
	call %isode%\utils\cp rydispatch.c p-rydispatch.c_new
	call %isode%\utils\cp rydsblock.c p-rydsblock.c_new
	call %isode%\utils\cp rydserror.c p-rydserror.c_new
	call %isode%\utils\cp rydsresult.c p-rydsresult.c_new
	call %isode%\utils\cp rydsurej.c p-rydsurej.c_new
	call %isode%\utils\cp ryfind.c p-ryfind.c_new
	call %isode%\utils\cp rygenid.c p-rygenid.c_new
	call %isode%\utils\cp rylose.c p-rylose.c_new
	call %isode%\utils\cp ryopblock.c p-ryopblock.c_new
	call %isode%\utils\cp ryoper.c p-ryoper.c_new
	call %isode%\utils\cp ryopinvoke.c p-ryopinvoke.c_new
	call %isode%\utils\cp rystub.c p-rystub.c_new
	call %isode%\utils\cp rywait.c p-rywait.c_new
	set defines=3
	call %isode%\utils\cc p-rydiscard
	call %isode%\utils\cc p-rydispatch
	call %isode%\utils\cc p-rydsblock
	call %isode%\utils\cc p-rydserror
	call %isode%\utils\cc p-rydsresult
	call %isode%\utils\cc p-rydsurej
	call %isode%\utils\cc p-ryfind
	call %isode%\utils\cc p-rygenid
	call %isode%\utils\cc p-rylose
	call %isode%\utils\cc p-ryopblock
	call %isode%\utils\cc p-ryoper
	call %isode%\utils\cc p-ryopinvoke
	call %isode%\utils\cc p-rystub
	call %isode%\utils\cc p-rywait
	set defines=0
	ar r temp.a @lrosy.lnk >nul:
	copy temp.a librosy.a >nul:
	ar rs librosy.a
	del temp.a
	goto end
:bad_param
	echo unknown option %1
:end
