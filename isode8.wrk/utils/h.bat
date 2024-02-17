rem @echo off
set h_file=%1.h
set new_file=%1.h_n
set orig_file=%isode_orig%\%dir%\%h_file%
if exist %new_file% set orig_file=%new_file%
%isode%\utils\cmpftime %h_file% %orig_file%
if not errorlevel 2 goto end
echo pass1 %orig_file% %h_file%
%isode%\utils\pass1 %orig_file% %h_file%
:end
