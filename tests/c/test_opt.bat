for %%i in (01 02 03 04 05 06 07 08 09 10 11 12) do (
  ..\..\vcproj\Debug\compiler.exe /noopt "..\..\tests\c\12_opt\%%i.c"
  fc 12_opt\%%i.asm 12_opt\%%i_noopt.asm > 12_opt\%%i.cmp
)