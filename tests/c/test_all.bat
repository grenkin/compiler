del LOG.TXT
del LOG_NOOPT.TXT

for %%i in (01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38) do call test_one.bat 01_int\%%i
for %%i in (01 02 03 04 05 06 07 08 09 10 11) do call test_one.bat 02_float\%%i
for %%i in (01 02 03 04 05) do call test_one.bat 03_ar\%%i
for %%i in (01 02 03) do call test_one.bat 04_big\%%i
for %%i in (01 02 03 04 05) do call test_one.bat 05_st\%%i
for %%i in (01 02) do call test_one.bat 06_ar\%%i
for %%i in (01) do call test_one.bat 07_ar_st\%%i
for %%i in (01 02 03 04 05) do call test_one.bat 08_ptr\%%i
for %%i in (01 02 03 04 05 06 07) do call test_one.bat 09_stat\%%i
for %%i in (01 02 03) do (
  ..\..\vcproj\Debug\compiler.exe "..\..\tests\c\10_err\%%i.c" > output.txt
  fc 10_err\%%i.ans output.txt >> LOG.TXT
)
for %%i in (01 02 03 04 05) do call test_one.bat 11_wa\%%i
call test_opt.bat

del output.txt