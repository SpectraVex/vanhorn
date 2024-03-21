@echo off
cls

:: ***********************************************************************
   rem Batch file for compiling Raylib and/or Raygui applications
:: ***********************************************************************

:Initialization
	echo ^> Initializing Variables
	echo ----------------------------
	SET "RAYLIB_DIR=C:\raylib"
	SET "CURRENT_DIR=%cd%"

	SET "INPUT_FILE=%1"
	SET "OUTPUT_FILE=%2"
	SET "INCLUDE_FILES=src\include\raylib.h"

	SET "COMPILER=C:\msys64\mingw64\bin\gcc.exe"
	SET "CFLAGS=%RAYLIB_DIR%\raylib\src\raylib.rc.data -std=c99 -Wall"
	SET "LDFLAGS=-lmsvcrt -lraylib -lopengl32 -lgdi32 -lwinmm -lkernel32 -lshell32 -luser32 -Wl,-subsystem=gui"
	SET "EXTRAFLAGS="

	IF /I "%3"=="Release" SET EXTRAFLAGS=%EXTRAFLAGS% -b

:Main
	echo(
	echo ^> Removing Previous Build
	echo ----------------------------
	IF EXIST "%1.exe" del /F "%1.exe"

	echo(
	echo ^> Compiling Program
	echo ----------------------------
	%COMPILER% -o "%OUTPUT_FILE%" "%INPUT_FILE%" %INCLUDE_FILES% %CFLAGS% %LDFLAGS% %EXTRAFLAGS%
	pause