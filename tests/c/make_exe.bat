tasm.exe /zi /ml %1.asm %1.obj
tlink.exe /v %1.obj
del %1.obj
del %1.map