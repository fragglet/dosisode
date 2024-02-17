@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del *.o
	del *.c
	del *.a
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.h
	del *.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	set dir=tsap
	set defines=0
	call %isode%\utils\cc fd2tpkt
	call %isode%\utils\cc str2tpkt
	call %isode%\utils\cc text2tpkt
	call %isode%\utils\cc tp0ts
	call %isode%\utils\cc ts2bsd
	call %isode%\utils\cc ts2sunlink
	call %isode%\utils\cc ts2tcp
	call %isode%\utils\cc ts2x25
	call %isode%\utils\cc tsaperror
	call %isode%\utils\cc tsapinitiate
	call %isode%\utils\cc tsaplose
	call %isode%\utils\cc tsaprespond
	call %isode%\utils\cc tsaprovider
	call %isode%\utils\cc tsapstate
	call %isode%\utils\cc tsaplisten
	call %isode%\utils\cc tsapmgmt
	call %isode%\utils\cc tsapmisc
	call %isode%\utils\cc tsapvrsn
	call %isode%\utils\cc ts2xti
	ar r temp.a @tsap.lnk >nul:
	copy temp.a libtsap.a >nul:
	ar rs libtsap.a
	del temp.a
	goto end
:bad_param
	echo unknown option %1
:end
