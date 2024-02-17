@echo off
if not "%1." == "clean." goto check_tidy
	del *.h
	del quipu\*.h
	goto end
:check_tidy
if not "%1." == "tidy." goto check_null
	goto end
:check_null
if not "%1." == "." goto bad_param
	set dir=h
	call %isode%\utils\h acpkt
	call %isode%\utils\h acsap
	call %isode%\utils\h cmd_srch
	call %isode%\utils\h config
	call %isode%\utils\h dgram
	call %isode%\utils\h usr_dirent
	call %isode%\utils\h sys_dirent
	call %isode%\utils\h sys_file
	call %isode%\utils\h fpkt
	call %isode%\utils\h ftam
	call %isode%\utils\h general
	call %isode%\utils\h internet
	call %isode%\utils\h isoaddrs
	call %isode%\utils\h isoservent
	call %isode%\utils\h logger
	call %isode%\utils\h manifest
	call %isode%\utils\h mpkt
	call %isode%\utils\h pepdefs
	call %isode%\utils\h pepsy
	call %isode%\utils\h ppkt
	call %isode%\utils\h psap
	call %isode%\utils\h psap2
	call %isode%\utils\h ropkt
	call %isode%\utils\h ronot
	call %isode%\utils\h rosap
	call %isode%\utils\h rosy
	call %isode%\utils\h rtpkt
	call %isode%\utils\h rtsap
	call %isode%\utils\h spkt
	call %isode%\utils\h ssap
	call %isode%\utils\h tailor
	call %isode%\utils\h tp4
	call %isode%\utils\h tpkt
	call %isode%\utils\h tsap
	call %isode%\utils\h x25
	call %isode%\utils\h demsa
	call %isode%\utils\h demsb
	call %isode%\utils\h osisec-stub
	call %isode%\utils\h quipu\abandon
	call %isode%\utils\h quipu\add
	call %isode%\utils\h quipu\af-cdefs
	call %isode%\utils\h quipu\attr
	call %isode%\utils\h quipu\attrvalue
	call %isode%\utils\h quipu\authen
	call %isode%\utils\h quipu\bind
	call %isode%\utils\h quipu\common
	call %isode%\utils\h quipu\commonarg
	call %isode%\utils\h quipu\compare
	call %isode%\utils\h quipu\config
	call %isode%\utils\h quipu\connection
	call %isode%\utils\h quipu\dap
	call %isode%\utils\h quipu\dap2
	call %isode%\utils\h quipu\das-cdefs
	call %isode%\utils\h quipu\do-cdefs
	call %isode%\utils\h quipu\dsap
	call %isode%\utils\h quipu\dsargument
	call %isode%\utils\h quipu\dsp
	call %isode%\utils\h quipu\ds_error
	call %isode%\utils\h quipu\ds_search
	call %isode%\utils\h quipu\dua
	call %isode%\utils\h quipu\entry
	call %isode%\utils\h quipu\if-cdefs
	call %isode%\utils\h quipu\list
	call %isode%\utils\h quipu\malloc
	call %isode%\utils\h quipu\modify
	call %isode%\utils\h quipu\modifyrdn
	call %isode%\utils\h quipu\name
	call %isode%\utils\h quipu\nrs-cdefs
	call %isode%\utils\h quipu\nrs_info
	call %isode%\utils\h quipu\oid
	call %isode%\utils\h quipu\photo
	call %isode%\utils\h quipu\policy
	call %isode%\utils\h quipu\qu-cdefs
	call %isode%\utils\h quipu\read
	call %isode%\utils\h quipu\remove
	call %isode%\utils\h quipu\sequence
	call %isode%\utils\h quipu\syntaxes
	call %isode%\utils\h quipu\turbo
	call %isode%\utils\h quipu\ufn
	call %isode%\utils\h quipu\util
	goto end
:bad_param
echo unknown option %1
:end
