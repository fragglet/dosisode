@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del *.o
	del *.c
	del *.a
	del imisc.exe
	del %isode_orig%\imisc\imisc_tables.*
	del %isode_orig%\imisc\imisc-types.*
	del %isode_orig%\imisc\imisc-asn.py
	del %isode_orig%\imisc\imisc-ops.c
	del %isode_orig%\imisc\imisc-ops.h
	del %isode_orig%\imisc\imisc-st.c
	del %isode_orig%\imisc\imisc-iops.c
	del %isode_orig%\imisc\*.ph
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.h
	del *.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	set dir=imisc
	if exist %isode_orig%\imisc\imisc_tables.c goto miss1
		cd %isode_orig%\imisc
		%isode%\rosy\rosy -m -pepsy -o IMISC-asn.py imisc.ry
		%isode%\pepsy\pepsy -A -f -h -m imisc-asn.py
		cd %isode%\imisc
:miss1
	if exist %isode_orig%\imisc\imisc-iops.c goto miss2
		cd %isode_orig%\imisc
		copy imisc-ops.c imisc-iops.c >nul:
		cd %isode%\imisc
:miss2
	set defines=2
	call %isode%\utils\h imisc-types
	call %isode%\utils\h imisc-ops
	call %isode%\utils\h ryinitiator
	call %isode%\utils\cc imisc
	call %isode%\utils\cc imisc_tables
	call %isode%\utils\cc ryinitiator
	call %isode%\utils\cc imiscvrsn
	set defines=4
	call %isode%\utils\cc imisc-iops
	gcc -o imisc @imisc.lnk
	strip imisc
	copy /b %ISODE%\utils\stub.exe+imisc imisc.exe >nul:
	del imisc
	goto end
:bad_param
	echo unknown option %1
:end
