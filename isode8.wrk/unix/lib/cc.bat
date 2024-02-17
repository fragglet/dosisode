set c_file=%1.c
set obj_file=%1.o
%isode%\utils\cmpftime %obj_file% %c_file%
if not errorlevel 2 goto end
echo gcc -g -c -I %isodei%/unix/h %c_file%
gcc -g -c -D_PATH_RESCONF=\"%etc%/resolv.conf\" -I %isodei%/unix/h %c_file%
:end
