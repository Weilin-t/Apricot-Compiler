@ECHO OFF
setlocal enabledelayedexpansion
cd ..
set SOLUTIONDIR=%cd%

COLOR 0E

powershell write-host -fore White ------------------------------------------------------------------------------------------------------
powershell write-host -fore White  DEPENDENCIES FILE UPDATER FOR MELON COMPILER
powershell write-host -fore White ------------------------------------------------------------------------------------------------------

REM =============================================== ASSIMP ===============================================
:ASSIMP

powershell write-host -fore White ------------------------------------------------------------------------------------------------------
powershell write-host -fore White  ASSIMP - MESH LOADER LIBRARY
powershell write-host -fore White ------------------------------------------------------------------------------------------------------

rmdir "dependencies/assimp" /S /Q
git clone https://github.com/assimp/assimp.git "dependencies/assimp"
if %ERRORLEVEL% GEQ 1 goto :ERROR

cd dependencies/assimp
if %ERRORLEVEL% GEQ 1 goto :ERROR

cmake CMakeLists.txt -G "Visual Studio 16 2019" -S . -B ./BINARIES/Win32
if %ERRORLEVEL% GEQ 1 goto :ERROR

cmake --build ./BINARIES/Win32 --config debug
if %ERRORLEVEL% GEQ 1 goto :ERROR

cd /d %SOLUTIONDIR%
if %ERRORLEVEL% GEQ 1 goto :ERROR

powershell write-host -fore White ------------------------------------------------------------------------------------------------------
powershell write-host -fore White  ASSIMP UPDATE DONE!
powershell write-host -fore White ------------------------------------------------------------------------------------------------------
REM =============================================== ASSIMP ===============================================

REM =============================================== GLM ===============================================
:GLM

powershell write-host -fore White ------------------------------------------------------------------------------------------------------
powershell write-host -fore White  GLM - MATH HELPER LIBRARY
powershell write-host -fore White ------------------------------------------------------------------------------------------------------

rmdir "dependencies/glm" /S /Q

git clone https://github.com/g-truc/glm.git "dependencies/glm"
if %ERRORLEVEL% GEQ 1 goto :ERROR

cd /d %SOLUTIONDIR%
if %ERRORLEVEL% GEQ 1 goto :ERROR

powershell write-host -fore White ------------------------------------------------------------------------------------------------------
powershell write-host -fore White  GLM UPDATE DONE!
powershell write-host -fore White ------------------------------------------------------------------------------------------------------
REM =============================================== GLM ===============================================

goto :PAUSE

REM =========================================== ERROR HANDLING ===========================================
:ERROR
powershell write-host -fore Red ------------------------------------------------------------------------------------------------------
powershell write-host -fore Red  ERROR
powershell write-host -fore Red ------------------------------------------------------------------------------------------------------
REM =========================================== ERROR HANDLING ===========================================

REM =============================================== PAUSE ================================================
:PAUSE
rem if no one give us any parameters then we will pause it at the end, else we are assuming that another batch file called us
if %1.==. pause
REM =============================================== PAUSE ================================================