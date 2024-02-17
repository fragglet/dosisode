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
	set dir=dsap\common
	set defines=5
	call %isode%\utils\h iso3166
	call %isode%\utils\cc acl
	call %isode%\utils\cc attrv
	call %isode%\utils\cc ca
	call %isode%\utils\cc dn_seq
	call %isode%\utils\cc ds_error
	call %isode%\utils\cc dsa_info
	call %isode%\utils\cc entryinfo
	call %isode%\utils\cc filter
	call %isode%\utils\cc oid
	call %isode%\utils\cc oid2
	call %isode%\utils\cc oidseq
	call %isode%\utils\cc oc
	call %isode%\utils\cc parse_error
	call %isode%\utils\cc pe
	call %isode%\utils\cc picture
	call %isode%\utils\cc psap
	call %isode%\utils\cc tree_struct
	call %isode%\utils\cc util
	call %isode%\utils\cc correlate
	call %isode%\utils\cc std_sntx
	call %isode%\utils\cc quipu_sntx
	call %isode%\utils\cc file_print
	call %isode%\utils\cc file_enc
	call %isode%\utils\cc file_cpy
	call %isode%\utils\cc file_str
	call %isode%\utils\cc attrt_cmp
	call %isode%\utils\cc attrt_dec
	call %isode%\utils\cc attrt_new
	call %isode%\utils\cc attrt_cpy
	call %isode%\utils\cc attrt_print
	call %isode%\utils\cc as_cmp
	call %isode%\utils\cc as_cpy
	call %isode%\utils\cc as_del
	call %isode%\utils\cc as_merge
	call %isode%\utils\cc as_new
	call %isode%\utils\cc as_free
	call %isode%\utils\cc as_find
	call %isode%\utils\cc as_print
	call %isode%\utils\cc as_str
	call %isode%\utils\cc avs_cmp
	call %isode%\utils\cc avs_cpy
	call %isode%\utils\cc avs_del
	call %isode%\utils\cc avs_merge
	call %isode%\utils\cc avs_new
	call %isode%\utils\cc avs_free
	call %isode%\utils\cc avs_print
	call %isode%\utils\cc avs_str
	call %isode%\utils\cc dn_cmp
	call %isode%\utils\cc dn_cpy
	call %isode%\utils\cc dn_append
	call %isode%\utils\cc dn_free
	call %isode%\utils\cc dn_print
	call %isode%\utils\cc dn_str
	call %isode%\utils\cc dn_new
	call %isode%\utils\cc rdn_cmp
	call %isode%\utils\cc rdn_cpy
	call %isode%\utils\cc rdn_new
	call %isode%\utils\cc rdn_free
	call %isode%\utils\cc rdn_print
	call %isode%\utils\cc rdn_str
	call %isode%\utils\cc rdn_merge
	call %isode%\utils\cc time
	call %isode%\utils\cc integer
	call %isode%\utils\cc boolean
	call %isode%\utils\cc string
	call %isode%\utils\cc mailbox
	call %isode%\utils\cc fax
	call %isode%\utils\cc post
	call %isode%\utils\cc telex
	call %isode%\utils\cc teletex
	call %isode%\utils\cc pdm
	call %isode%\utils\cc guide
	call %isode%\utils\cc soundex
	call %isode%\utils\cc conf
	call %isode%\utils\cc sys_tai
	call %isode%\utils\cc sys_init
	call %isode%\utils\cc tai_init
	call %isode%\utils\cc tai_args
	call %isode%\utils\cc certificate
	call %isode%\utils\cc cpair
	call %isode%\utils\cc protected
	call %isode%\utils\cc cache
	call %isode%\utils\cc entry
	call %isode%\utils\cc parse
	call %isode%\utils\cc ufn_aet
	call %isode%\utils\cc ufn_parse
	call %isode%\utils\cc aetufn
	call %isode%\utils\cc aetdap
	call %isode%\utils\cc nrs_info
	call %isode%\utils\cc inherit
	call %isode%\utils\cc audio
	call %isode%\utils\cc cstrings
	call %isode%\utils\cc service
	call %isode%\utils\cc security
	call %isode%\utils\cc cilist
	call %isode%\utils\cc policy
	call %isode%\utils\cc ds_ext
	call %isode%\utils\cc ap
	call %isode%\utils\cc turbo_avl
	call %isode%\utils\cc turbo_index
	call %isode%\utils\cc attribute
	call %isode%\utils\cc docstore
	call %isode%\utils\cc qos
	call %isode%\utils\cc dsapvrsn
	call %isode%\utils\cc attr_sntx
	call %isode%\utils\cc authpolicy
	call %isode%\utils\cc dsa_control
	call %isode%\utils\cc osisec-int
	call %isode%\utils\cc photo_build
	call %isode%\utils\cc photo_dec
	call %isode%\utils\cc photo_stub
	call %isode%\utils\cc photo_util
	call %isode%\utils\cc searchacl
	set defines=0
	goto end
:bad_param
	echo unknown option %1
:end
