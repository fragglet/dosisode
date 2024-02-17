@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del *.o
	del *.c
	del *.a
	del %isode_orig%\rtsap\rts_tables.*
	del %isode_orig%\rtsap\rts-types.*
	del %isode_orig%\rtsap\*.ph
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.h
	del *.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	set dir=rtsap
	if exist %isode_orig%\rtsap\rts_tables.c goto miss1
		cd %isode_orig%\rtsap
		%isode%\pepsy\pepsy -A -f -h -m rts.py
		cd %isode%\rtsap
:miss1
	set defines=5
	call %isode%\utils\h rts-types
	call %isode%\utils\cc rts_tables
	call %isode%\utils\cc rt2ps
	call %isode%\utils\cc rt2psabort
	call %isode%\utils\cc rt2psinitiat
	call %isode%\utils\cc psrel1 rt2psreleas1
	call %isode%\utils\cc psrel2 rt2psreleas2
	call %isode%\utils\cc rt2psrespond
	call %isode%\utils\cc rt2ss
	call %isode%\utils\cc rt2ssexec
	call %isode%\utils\cc rt2ssinitiat
	call %isode%\utils\cc ssrel1 rt2ssreleas1
	call %isode%\utils\cc ssrel2 rt2ssreleas2
	call %isode%\utils\cc rt2ssrespond
	call %isode%\utils\cc rtsapasync
	call %isode%\utils\cc rtsaperror
	call %isode%\utils\cc rtsapgturn
	call %isode%\utils\cc rtsaplose
	call %isode%\utils\cc rtsappturn
	call %isode%\utils\cc rtsapselect
	call %isode%\utils\cc rtsaptrans
	call %isode%\utils\cc rtsapwait
	call %isode%\utils\cc rtsapvrsn
	set defines=0
	ar r temp.a @rtsap.lnk >nul:
	copy temp.a librtsap.a >nul:
	ar rs librtsap.a
	del temp.a
	goto end
:bad_param
	echo unknown option %1
:end
