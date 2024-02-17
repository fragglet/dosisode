@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del *.o
	del *.c
	del %isode_orig%\dsap\x500as\if_tables.*
	del %isode_orig%\dsap\x500as\if-types.*
	del %isode_orig%\dsap\x500as\thorn_tables.*
	del %isode_orig%\dsap\x500as\thorn-types.*
	del %isode_orig%\dsap\x500as\af_tables.*
	del %isode_orig%\dsap\x500as\af-types.*
	del %isode_orig%\dsap\x500as\do_tables.*
	del %isode_orig%\dsap\x500as\do-types.*
	del %isode_orig%\dsap\x500as\das_tables.*
	del %isode_orig%\dsap\x500as\das-types.*
	del %isode_orig%\dsap\x500as\quipu_tables.*
	del %isode_orig%\dsap\x500as\quipu-types.*
	del %isode_orig%\dsap\x500as\sa_tables.*
	del %isode_orig%\dsap\x500as\sa-types.*
	del %isode_orig%\dsap\x500as\nrs_tables.*
	del %isode_orig%\dsap\x500as\nrs-types.*
	del %isode_orig%\dsap\x500as\*.ph
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.h
	del *.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	set dir=dsap\x500as
	if exist %isode_orig%\dsap\x500as\if_tables.c goto miss1
		cd %isode_orig%\dsap\x500as
		%isode%\pepsy\pepsy -i if-cdefs.h -A -m if.py
		copy ..\..\pepsy\if.ph >nul:
		%isode%\pepsy\pepsy -i if-cdefs.h -A -m th.py
		copy ..\..\pepsy\thorn.ph >nul:
		%isode%\pepsy\pepsy -i af-cdefs.h -A -m af.py
		copy ..\..\pepsy\af.ph >nul:
		%isode%\pepsy\pepsy -i do-cdefs.h -A -m do.py
		copy ..\..\pepsy\do.ph >nul:
		%isode%\pepsy\pepsy -i das-cdefs.h -A -m das.py
		copy ..\..\pepsy\das.ph >nul:
		%isode%\pepsy\pepsy -i qu-cdefs.h -A -m qu.py
		copy ..\..\pepsy\qu.ph >nul:
		%isode%\pepsy\pepsy -i if-cdefs.h -A -m sa.py
		copy ..\..\pepsy\sa.ph >nul:
		%isode%\pepsy\pepsy -i nrs-cdefs.h -A -m nrs.py
		copy ..\..\pepsy\nrs.ph >nul:
		cd %isode%\dsap\x500as
:miss1
	set defines=5
	call %isode%\utils\h if-types
	call %isode%\utils\h af-types
	call %isode%\utils\h do-types
	call %isode%\utils\h das-types
	call %isode%\utils\h quipu-types
	call %isode%\utils\h sa-types
	call %isode%\utils\h thorn-types
	call %isode%\utils\h nrs-types
	copy if-types.h ..\..\h\quipu >nul:
	copy af-types.h ..\..\h\quipu >nul:
	copy do-types.h ..\..\h\quipu >nul:
	copy das-types.h ..\..\h\quipu >nul:
	copy quipu-types.h ..\..\h\quipu >nul:
	copy sa-types.h ..\..\h\quipu >nul:
	copy thorn-types.h ..\..\h\quipu >nul:
	copy nrs-types.h ..\..\h\quipu >nul:
	call %isode%\utils\h if-cdefs
	call %isode%\utils\h af-cdefs
	call %isode%\utils\h das-cdefs
	call %isode%\utils\h do-cdefs
	call %isode%\utils\h nrs-cdefs
	call %isode%\utils\h qu-cdefs
	call %isode%\utils\cc if_tables
	call %isode%\utils\cc thorn_tables
	call %isode%\utils\cc af_tables
	call %isode%\utils\cc do_tables
	call %isode%\utils\cc das_tables
	call %isode%\utils\cc quipu_tables
	call %isode%\utils\cc sa_tables
	call %isode%\utils\cc nrs_tables
	call %isode%\utils\cc asn_ext
	set defines=0
	goto end
:bad_param
	echo unknown option %1
:end
