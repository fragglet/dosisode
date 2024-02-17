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
	set dir=psap
	set defines=0
	call %isode%\utils\cc addr2ref
	call %isode%\utils\cc bit2prim
	call %isode%\utils\cc bitstr2strb
	call %isode%\utils\cc bit_ops
	call %isode%\utils\cc dg2ps
	call %isode%\utils\cc fdx2ps
	call %isode%\utils\cc flag2prim
	call %isode%\utils\cc gtime
	call %isode%\utils\cc int2strb
	call %isode%\utils\cc isobject
	call %isode%\utils\cc num2prim
	call %isode%\utils\cc obj2prim
	call %isode%\utils\cc objectbyname
	call %isode%\utils\cc objbyoid objectbyoid
	call %isode%\utils\cc ode2oid
	call %isode%\utils\cc oid2ode
	call %isode%\utils\cc oid_cmp
	call %isode%\utils\cc oid_cpy
	call %isode%\utils\cc oid_free
	call %isode%\utils\cc pe2pl
	call %isode%\utils\cc pe2ps
	call %isode%\utils\cc pe2ssdu
	call %isode%\utils\cc pe2text
	call %isode%\utils\cc pe2uvec
	call %isode%\utils\cc pe_alloc
	call %isode%\utils\cc pe_cmp
	call %isode%\utils\cc pe_cpy
	call %isode%\utils\cc pe_error
	call %isode%\utils\cc pe_expunge
	call %isode%\utils\cc pe_extract
	call %isode%\utils\cc pe_free
	call %isode%\utils\cc pe_pullup
	call %isode%\utils\cc pl2pe
	call %isode%\utils\cc pl_tables
	call %isode%\utils\cc prim2bit
	call %isode%\utils\cc prim2flag
	call %isode%\utils\cc prim2num
	call %isode%\utils\cc prim2oid
	call %isode%\utils\cc prim2qb
	call %isode%\utils\cc prim2real
	call %isode%\utils\cc prim2set
	call %isode%\utils\cc prim2str
	call %isode%\utils\cc prim2time
	call %isode%\utils\cc ps2pe
	call %isode%\utils\cc ps_alloc
	call %isode%\utils\cc ps_error
	call %isode%\utils\cc ps_flush
	call %isode%\utils\cc ps_free
	call %isode%\utils\cc ps_get_abs
	call %isode%\utils\cc ps_io
	call %isode%\utils\cc ps_prime
	call %isode%\utils\cc qb2pe
	call %isode%\utils\cc qb2prim
	call %isode%\utils\cc qb2str
	call %isode%\utils\cc qbuf2pe
	call %isode%\utils\cc qbuf2ps
	call %isode%\utils\cc qb_free
	call %isode%\utils\cc qb_pullup
	call %isode%\utils\cc seq_add
	call %isode%\utils\cc seq_addon
	call %isode%\utils\cc seq_del
	call %isode%\utils\cc seq_find
	call %isode%\utils\cc set_add
	call %isode%\utils\cc set_addon
	call %isode%\utils\cc set_del
	call %isode%\utils\cc set_find
	call %isode%\utils\cc sprintoid
	call %isode%\utils\cc sprintref
	call %isode%\utils\cc ssdu2pe
	call %isode%\utils\cc std2ps
	call %isode%\utils\cc str2oid
	call %isode%\utils\cc str2pe
	call %isode%\utils\cc str2prim
	call %isode%\utils\cc str2ps
	call %isode%\utils\cc str2qb
	call %isode%\utils\cc strb2bitstr
	call %isode%\utils\cc strb2int
	call %isode%\utils\cc time2prim
	call %isode%\utils\cc time2str
	call %isode%\utils\cc tm2ut
	call %isode%\utils\cc ts2ps
	call %isode%\utils\cc ut2tm
	call %isode%\utils\cc uvec2ps
	call %isode%\utils\cc pe2qb_f
	call %isode%\utils\cc qbuf2pe_f
	call %isode%\utils\cc psapvrsn
	ar r temp.a @psap.lnk >nul:
	copy temp.a libpsap.a >nul:
	ar rs libpsap.a
	del temp.a
	goto end
:bad_param
	echo unknown option %1
:end
