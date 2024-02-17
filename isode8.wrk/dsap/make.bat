@echo off
if not "%1." == "clean." goto check_tidy
	del *.a
	cd x500as
	call make %1
	cd ..\common
	call make %1
	cd ..\net
	call make %1
	cd ..
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	cd x500as
	call make %1
	cd ..\common
	call make %1
	cd ..\net
	call make %1
	cd ..
	goto end
:check_null
if not "%1." == "." goto bad_param
	cd x500as
	call make %1
	cd ..\common
	call make %1
	cd ..\net
	call make %1
	cd ..
	ar r temp.a @dsap.lnk >nul:
	copy temp.a libdsap.a >nul:
	ar rs libdsap.a
	del temp.a
	goto end
:bad_param
	echo unknown option %1
:end
