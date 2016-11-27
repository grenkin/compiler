@echo off
..\..\vcproj\Debug\compiler.exe /noopt "..\..\tests\c\%1.c"
if exist %1.asm call make_exe %1
if exist %1_noopt.asm call make_exe %1_noopt