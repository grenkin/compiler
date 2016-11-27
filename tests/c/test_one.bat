@echo off
call make_one %1
%1.exe > output.txt
fc %1.ans output.txt >> LOG.TXT
%1_noopt.exe > output.txt
fc %1.ans output.txt >> LOG_NOOPT.TXT
del %1.exe
del %1_noopt.exe