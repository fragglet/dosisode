@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del *.o
	del *.c
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	del *.h
	del *.o
	goto end
:check_null
if not "%1." == "." goto bad_param
	set dir=dsap\net
	set defines=5
	call %isode%\utils\cc bind1
	call %isode%\utils\cc bind2
	call %isode%\utils\cc dsapcontexts
	call %isode%\utils\cc unbind1
	call %isode%\utils\cc unbind2
	call %isode%\utils\cc dsapwait
	call %isode%\utils\cc dsapinvoke
	call %isode%\utils\cc dsapresult
	call %isode%\utils\cc dsaperror
	call %isode%\utils\cc dsapreject
	call %isode%\utils\cc dsapabort
	call %isode%\utils\cc dsaprovider
	call %isode%\utils\cc dsaplose
	call %isode%\utils\cc dapwait
	call %isode%\utils\cc dapbind
	call %isode%\utils\cc dapunbind
	call %isode%\utils\cc dapabandon
	call %isode%\utils\cc dapaddent
	call %isode%\utils\cc dapcompare
	call %isode%\utils\cc dapinvoke
	call %isode%\utils\cc daplist
	call %isode%\utils\cc dapmodent
	call %isode%\utils\cc dapmodrdn
	call %isode%\utils\cc dapread
	call %isode%\utils\cc daprement
	call %isode%\utils\cc dapsearch
	call %isode%\utils\cc daplose
	call %isode%\utils\cc daprovider
	call %isode%\utils\cc ds_types
	call %isode%\utils\cc plog
	set defines=0
	goto end
:bad_param
	echo unknown option %1
:end
