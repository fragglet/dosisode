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
	set dir=dirent
	set defines=0
	call %isode%\utils\cc getdents
	call %isode%\utils\cc closedir
	call %isode%\utils\cc opendir
	call %isode%\utils\cc readdir
	call %isode%\utils\cc rewinddir
	call %isode%\utils\cc scandir
	call %isode%\utils\cc seekdir
	call %isode%\utils\cc telldir
	call %isode%\utils\cc getcwd
	call %isode%\utils\cc direntvrsn
	ar r temp.a @dirent.lnk >nul:
	copy temp.a libdirent.a >nul:
	ar rs libdirent.a
	del temp.a
	goto end
:bad_param
	echo unknown option %1
:end
