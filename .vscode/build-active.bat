@echo off
call "C:\Program Files\Microsoft Visual Studio\18\Community\Common7\Tools\VsDevCmd.bat" -arch=x64 -host_arch=x64
if errorlevel 1 exit /b %errorlevel%

cl.exe /std:c++20 /Zi /EHsc /nologo /Fe:"%~dpn1.exe" "%~f1"
