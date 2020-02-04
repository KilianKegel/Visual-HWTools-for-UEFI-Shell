@echo off
echo clean up...

if exist x64 del /s x64\*.pdb
if exist x64 del /s x64\*.map
if exist x64 del /s x64\*.ilk
for /F  %%d in ('dir /b /AD') do if exist %%d\x64 rd /s /q %%d\x64
for /F  %%d in ('dir /b /AD') do if exist %%d\doxygen.tmp rd /s /q %%d\doxygen.tmp
