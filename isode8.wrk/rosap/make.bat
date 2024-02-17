@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del *.o
	del *.c
	del *.a
	del %isode_orig%\rosap\ros_tables.*
	del %isode_orig%\rosap\ros-types.*
	del %isode_orig%\rosap\*.ph
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.h
	del *.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	set dir=rosap
	if exist %isode_orig%\rosap\ros_tables.c goto miss1
		cd %isode_orig%\rosap
		copy %isode_orig%\pepsy\UNIV.ph UNIV.ph >nul:
		copy %isode_orig%\acsap\OACS.ph OACS.ph >nul:
		%isode%\pepsy\pepsy -A -f -h -m ros.py
		cd %isode%\rosap
:miss1
	set defines=5
	call %isode%\utils\h ros-types
	call %isode%\utils\cc ros_tables
	call %isode%\utils\cc ro2ps
	call %isode%\utils\cc ro2rts
	call %isode%\utils\cc ro2ss
	call %isode%\utils\cc ro2ssexec
	call %isode%\utils\cc ro2ssinitiat
	call %isode%\utils\cc releas1 ro2ssreleas1
	call %isode%\utils\cc releas2 ro2ssreleas2
	call %isode%\utils\cc ro2ssrespond
	call %isode%\utils\cc ro2ssthorn
	call %isode%\utils\cc rosapapdu
	call %isode%\utils\cc rosapasync
	call %isode%\utils\cc rosaperror
	call %isode%\utils\cc rosapinvoke
	call %isode%\utils\cc rosaplose
	call %isode%\utils\cc rosapresult
	call %isode%\utils\cc rosapselect
	call %isode%\utils\cc rosapservice
	call %isode%\utils\cc rosapuerror
	call %isode%\utils\cc rosapureject
	call %isode%\utils\cc rosapwait
	call %isode%\utils\cc rosapintr
	call %isode%\utils\cc rosapvrsn
	set defines=0
	ar r temp.a @rosap.lnk >nul:
	copy temp.a librosap.a >nul:
	ar rs librosap.a
	del temp.a
	goto end
:bad_param
	echo unknown option %1
:end
