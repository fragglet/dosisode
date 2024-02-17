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
	set dir=ssap
	set defines=0
	call %isode%\utils\cc ssaprovider
	call %isode%\utils\cc ssaperror
	call %isode%\utils\cc str2spkt
	call %isode%\utils\cc text2spkt
	call %isode%\utils\cc tsdu2spkt
	call %isode%\utils\cc ssapexec
	call %isode%\utils\cc ssaprespond
	call %isode%\utils\cc ssapinitiate
	call %isode%\utils\cc ssapexpd
	call %isode%\utils\cc ssaptyped
	call %isode%\utils\cc capd1 ssapcapd1
	call %isode%\utils\cc capd2 ssapcapd2
	call %isode%\utils\cc ssaptoken
	call %isode%\utils\cc ssapactivity
	call %isode%\utils\cc major1 ssapmajor1
	call %isode%\utils\cc major2 ssapmajor2
	call %isode%\utils\cc minor1 ssapminor1
	call %isode%\utils\cc minor2 ssapminor2
	call %isode%\utils\cc resync1 ssapresync1
	call %isode%\utils\cc resync2 ssapresync2
	call %isode%\utils\cc ssapabort
	call %isode%\utils\cc ssapreport
	call %isode%\utils\cc release1 ssaprelease1
	call %isode%\utils\cc release2 ssaprelease2
	call %isode%\utils\cc ssapwrite
	call %isode%\utils\cc ssapactchk
	call %isode%\utils\cc ssapselect
	call %isode%\utils\cc ssaplose
	call %isode%\utils\cc ssapvrsn
	ar r temp.a @ssap.lnk >nul:
	copy temp.a libssap.a >nul:
	ar rs libssap.a
	del temp.a
	goto end
:bad_param
	echo unknown option %1
:end
