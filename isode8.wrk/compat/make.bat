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
	set dir=compat
	set defines=0
	call %isode%\utils\cc asprintf
rem	call %isode%\utils\cc camtec
	call %isode%\utils\cc explode
	call %isode%\utils\cc general
	call %isode%\utils\cc implode
	call %isode%\utils\cc internet
	call %isode%\utils\cc isoaddrs
	call %isode%\utils\cc isofiles
	call %isode%\utils\cc isohost
	call %isode%\utils\cc isoservent
	call %isode%\utils\cc logger
	call %isode%\utils\cc na2norm
	call %isode%\utils\cc na2str
	call %isode%\utils\cc sel2str
	call %isode%\utils\cc select
	call %isode%\utils\cc serror
	call %isode%\utils\cc servbyname
	call %isode%\utils\cc servbyport
	call %isode%\utils\cc servbysel
	call %isode%\utils\cc signals
	call %isode%\utils\cc sprintb
	call %isode%\utils\cc str2elem
	call %isode%\utils\cc str2sel
	call %isode%\utils\cc str2taddr
	call %isode%\utils\cc str2vec
	call %isode%\utils\cc sunlink
	call %isode%\utils\cc taddr2str
	call %isode%\utils\cc tailor
	call %isode%\utils\cc ubcx25
	call %isode%\utils\cc dgram
	call %isode%\utils\cc x25addr
	call %isode%\utils\cc saddr2str
	call %isode%\utils\cc str2saddr
	call %isode%\utils\cc baduser
	call %isode%\utils\cc getpassword
	call %isode%\utils\cc chrcnv
	call %isode%\utils\cc cmd_srch
	call %isode%\utils\cc lexequ
	call %isode%\utils\cc lexnequ
	call %isode%\utils\cc log_tai
	call %isode%\utils\cc nochrcnv
	call %isode%\utils\cc rcmd_srch
	call %isode%\utils\cc smalloc
	call %isode%\utils\cc sstr2arg
rem	call %isode%\utils\cc strdup
	call %isode%\utils\cc pa2str
	call %isode%\utils\cc putenv
	call %isode%\utils\cc chkpassword
	call %isode%\utils\cc norm2na
	call %isode%\utils\cc compatvrsn
	call %isode%\utils\cc bcd2char
	call %isode%\utils\cc ccurx25
	call %isode%\utils\cc char2bcd
	call %isode%\utils\cc internet_tli
	call %isode%\utils\cc isonsapsnpa
	call %isode%\utils\cc nsapcmp
	ar r temp.a @compat.lnk >nul:
	copy temp.a libcompat.a >nul:
	ar rs libcompat.a
	del temp.a
	goto end
:bad_param
	echo unknown option %1
:end
