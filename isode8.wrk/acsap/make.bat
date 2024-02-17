@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del *.o
	del *.c
	del *.a
	del %isode_orig%\acsap\acs_tables.*
	del %isode_orig%\acsap\acs-types.*
	del %isode_orig%\acsap\acsold_tables.*
	del %isode_orig%\acsap\acsold-types.*
	del %isode_orig%\acsap\dse_tables.*
	del %isode_orig%\acsap\dse-types.*
	del %isode_orig%\acsap\dase_tables.*
	del %isode_orig%\acsap\dase-types.*
	del %isode_orig%\acsap\*.ph
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.h
	del *.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	set dir=acsap
	if exist %isode_orig%\acsap\acs_tables.c goto miss1
		cd %isode_orig%\acsap
		%isode%\pepsy\pepsy -A -f -h -m acs.py
		%isode%\pepsy\pepsy -A -f -h -m acsold.py
		%isode%\pepsy\pepsy -A -f -h -m dse.py
		%isode%\pepsy\pepsy -A -f -h -m dase.py
		%isode%\utils\string_replace oacs-types.h t decode_ parse_
		del oacs-types.h
		ren t oacs-types.h
		cd %isode%\acsap
:miss1
	set defines=5
	call %isode%\utils\h acs-types
	call %isode%\utils\h oacs-types
	call %isode%\utils\h dse-types
	call %isode%\utils\h dase-types
	copy acs-types.h %isode%\h\acs-types.h
	copy oacs-types.h %isode%\h\oacs-types.h
	call %isode%\utils\cc acs_tables
	call %isode%\utils\cc oacs_tables
	call %isode%\utils\cc dse_tables
	call %isode%\utils\cc dase_tables
	call %isode%\utils\cc abort1 acsapabort1
	call %isode%\utils\cc abort2 acsapabort2
	call %isode%\utils\cc acsapaddr
	call %isode%\utils\cc acsapblock
	call %isode%\utils\cc acsapdse
	call %isode%\utils\cc acsaperror
	call %isode%\utils\cc acsapfindpci
	call %isode%\utils\cc acsapinitiat
	call %isode%\utils\cc acsaplose
	call %isode%\utils\cc releas1 acsapreleas1
	call %isode%\utils\cc releas2 acsapreleas2
	call %isode%\utils\cc releas3 acsapreleas3
	call %isode%\utils\cc acsaprespond
	call %isode%\utils\cc acsaprovider
	call %isode%\utils\cc acsapstub
	call %isode%\utils\cc server1 acserver1
	call %isode%\utils\cc server2 acserver2
	call %isode%\utils\cc aetseq
	call %isode%\utils\cc is2paddr
	call %isode%\utils\cc is2saddr
	call %isode%\utils\cc is2taddr
	call %isode%\utils\cc isoalias
	call %isode%\utils\cc isoentity
	call %isode%\utils\cc oid2aei
	call %isode%\utils\cc sprintaei
	call %isode%\utils\cc aetdase
	call %isode%\utils\cc dse-c
	call %isode%\utils\cc acsapvrsn
	set defines=0
	ar r temp.a @acsap.lnk >nul:
	copy temp.a libacsap.a >nul:
	ar rs libacsap.a
	del temp.a
	goto end
:bad_param
	echo unknown option %1
:end
