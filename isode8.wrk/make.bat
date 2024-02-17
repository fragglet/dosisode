echo unix\lib
cd unix\lib
call make %1
cd ..
echo h
cd ..\h
call make %1
echo compat
cd ..\compat
call make %1
echo dirent
cd ..\dirent
call make %1
echo tsap
cd ..\tsap
call make %1
echo ssap
cd ..\ssap
call make %1
echo psap
cd ..\psap
call make %1
echo pepsy
cd ..\pepsy
call make %1
echo pepy
cd ..\pepy
call make %1
echo psap2
cd ..\psap2
call make %1
echo acsap
cd ..\acsap
call make %1
echo rtsap
cd ..\rtsap
call make %1
echo rosap
cd ..\rosap
call make %1
echo ronot
cd ..\ronot
call make %1
echo rosy
cd ..\rosy
call make %1
echo ftam
cd ..\ftam
call make %1
echo ftam2
cd ..\ftam2
call make %1
echo dsap
cd ..\dsap
call make %1
rem echo quipu
rem cd ..\quipu
rem call make %1
echo quipu\dish
cd ..\quipu\dish
call make %1
cd ..
echo others\quipu\uips\de
cd ..\others\quipu\uips\de
call make %1
cd ..\..\..
echo others\quipu\uips\sd
cd ..\others\quipu\uips\sd
call make %1
cd ..\..\..
echo imisc
cd ..\imisc
call make %1
echo support
cd ..\support
call make %1
cd ..
