@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del *.o
	del *.c
	del *.a
	del %isode_orig%\ftam\ftam_tables.*
	del %isode_orig%\ftam\ftam-types.*
	del %isode_orig%\ftam\fadu_tables.*
	del %isode_orig%\ftam\fadu-types.*
	del %isode_orig%\ftam\cont_tables.*
	del %isode_orig%\ftam\cont-types.*
	del %isode_orig%\ftam\*.ph
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.h
	del *.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	set dir=ftam
	if exist %isode_orig%\ftam\ftam_tables.c goto miss1
		cd %isode_orig%\ftam
		%isode%\pepsy\pepsy -A -f -h -m cont.py
		copy ..\pepsy\cont.ph >nul:
		%isode%\pepsy\pepsy -A -f -h -m fadu.py
		copy ..\pepsy\fadu.ph >nul:
		%isode%\pepsy\pepsy -A -f -h -m ftam.py
		cd %isode%\ftam
:miss1
	set defines=5
	call %isode%\utils\h cont-types
	call %isode%\utils\h fadu-types
	call %isode%\utils\h ftam-types
	copy cont-types.h %isode%\h\cont-types.h >nul:
	copy fadu-types.h %isode%\h\fadu-types.h >nul:
	copy ftam-types.h %isode%\h\ftam-types.h >nul:
	call %isode%\utils\cc cont_tables
	call %isode%\utils\cc fadu_tables
	call %isode%\utils\cc ftam_tables
	call %isode%\utils\cc ftamabort
	call %isode%\utils\cc access1
	call %isode%\utils\cc access2
	call %isode%\utils\cc ftamacl
	call %isode%\utils\cc ftamattr
	call %isode%\utils\cc ftambits
	call %isode%\utils\cc ftambulk
	call %isode%\utils\cc bulk1
	call %isode%\utils\cc bulk2
	call %isode%\utils\cc ftamchrg
	call %isode%\utils\cc ftamconctl
	call %isode%\utils\cc ftamdiag
	call %isode%\utils\cc ftamdocument
	call %isode%\utils\cc ftamerror
	call %isode%\utils\cc ftamfaduid
	call %isode%\utils\cc ftamfdf
	call %isode%\utils\cc group1
	call %isode%\utils\cc group2
	call %isode%\utils\cc ftaminitiate
	call %isode%\utils\cc ftamlose
	call %isode%\utils\cc ftampass
	call %isode%\utils\cc ftamprovider
	call %isode%\utils\cc release1
	call %isode%\utils\cc release2
	call %isode%\utils\cc ftamrespond
	call %isode%\utils\cc ftamselect
	call %isode%\utils\cc ftamshare
	call %isode%\utils\cc ftamtrace
	set defines=0
	ar r temp.a @ftam.lnk >nul:
	copy temp.a libftam.a >nul:
	ar rs libftam.a
	del temp.a
	goto end
:bad_param
	echo unknown option %1
:end
