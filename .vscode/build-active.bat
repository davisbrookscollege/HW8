@echo off
setlocal

set "ROOT=%~dp0.."
set "BUILD_DIR=%ROOT%\build"

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

call "C:\Program Files\Microsoft Visual Studio\18\Community\Common7\Tools\VsDevCmd.bat" -arch=x64 -host_arch=x64
if errorlevel 1 exit /b %errorlevel%

cl.exe /std:c++20 /Zi /EHsc /nologo /I"%ROOT%\Header Files" /Fe:"%BUILD_DIR%\HW8.exe" /Fo"%BUILD_DIR%\\" /Fd"%BUILD_DIR%\vc143.pdb" "%ROOT%\main.cpp" "%ROOT%\Source Files\Gate.cpp" "%ROOT%\Source Files\Wire.cpp" "%ROOT%\Source Files\Event.cpp"
