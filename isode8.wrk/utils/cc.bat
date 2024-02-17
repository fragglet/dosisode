set c_file=%1.c
set new_file=%1.c_n
set orig_file=%isode_orig%\%dir%\%c_file%
set obj_file=%1.o
rem set debug=-g
set debug=
if exist %new_file% set orig_file=%new_file%
%isode%\utils\cmpftime %obj_file% %orig_file%
if not errorlevel 2 goto end
%isode%\utils\pass1 %orig_file% %c_file%
if "%defines%." == "1." goto 1
if "%defines%." == "2." goto 2
if "%defines%." == "3." goto 3
if "%defines%." == "4." goto 4
if "%defines%." == "5." goto 5
echo gcc %debug% -c -DDEBUG %c_file%
gcc %debug% -c -DDEBUG @%isodei%/utils/I %c_file%
goto x
:1
echo gcc %debug% -c -DPEPYPATH -DPEPSYPATH=\"%isoded%/pepsy\" -DDEBUG %c_file%
gcc %debug% -c -DPEPYPATH -DPEPSYPATH=\"%isoded%/pepsy\" -DDEBUG @%isodei%/utils/I %c_file%
goto x
:2
echo gcc %debug% -c -DPEPYPATH=\"%isoded%/pepy\" -DDEBUG %c_file%
gcc %debug% -c -DPEPYPATH=\"%isoded%/pepy\" -DDEBUG @%isodei%/utils/I %c_file%
goto x
:3
echo gcc %debug% -c -DDEBUG -DPEPSY_VERSION=2 %c_file%
gcc %debug% -c -DDEBUG -DPEPSY_VERSION=2 @%isodei%/utils/I %c_file%
goto x
:4
echo gcc %debug% -c -DINVOKER -DPEPYPATH=\"%isoded%/pepy\" -DDEBUG %c_file%
gcc %debug% -c -DINVOKER -DPEPYPATH=\"%isoded%/pepy\" -DDEBUG @%isodei%/utils/I %c_file%
goto x
:5
echo gcc %debug% -c -DPEPYPATH -DDEBUG %c_file%
gcc %debug% -c -DPEPYPATH -DDEBUG @%isodei%/utils/I %c_file%
goto x
:x
del %c_file%
:end
