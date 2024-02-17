set old_file=%1
set new_file=%1_new
set orig_file=%isode_orig%\%dir%\%old_file%
if exist %new_file% set orig_file=%new_file%
copy %orig_file% %2 >nul:
