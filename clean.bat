@echo off
echo clean up...
if "%1" == "/all" (
    rd /s /q x64
    del /s *.chm
)
if exist libraries\UniDumpLibrary.lib del libraries\UniDumpLibrary.lib
if exist x64\Release del /s /q x64\Release
if exist x64 del /s x64\*.pdb
if exist x64 del /s x64\*.map
if exist x64 del /s x64\*.ilk
for /F  %%d in ('dir /b /AD') do if exist %%d\x64 rd /s /q %%d\x64
for /F  %%d in ('dir /b /AD') do if exist %%d\doxygen.tmp rd /s /q %%d\doxygen.tmp
