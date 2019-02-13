@echo off
echo clean up...

if exist %~p0x64\Efi64\*.pdb del /s %~p0x64\Efi64\*.pdb
if exist %~p0x64\Efi64\*.map del /s %~p0x64\Efi64\*.map
if exist %~p0x64\Efi64\*.ilk del /s %~p0x64\Efi64\*.ilk

if exist %~p0x64\Win64\*.pdb del /s %~p0x64\Win64\*.pdb
if exist %~p0x64\Win64\*.map del /s %~p0x64\Win64\*.map
if exist %~p0x64\Win64\*.ilk del /s %~p0x64\Win64\*.ilk

if exist %~p0x64\Win64.msft\*.pdb del /s %~p0x64\Win64.msft\*.pdb
if exist %~p0x64\Win64.msft\*.map del /s %~p0x64\Win64.msft\*.map
if exist %~p0x64\Win64.msft\*.ilk del /s %~p0x64\Win64.msft\*.ilk

if exist %~p0Debug rd /s /q %~p0Debug

for /F  %%d in ('dir /b /AD') do if exist %%d\x64 rd /s /q %%d\x64
for /F  %%d in ('dir /b /AD') do if exist %%d\doxygen.tmp rd /s /q %%d\doxygen.tmp
