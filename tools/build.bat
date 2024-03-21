@echo off
setlocal EnableDelayedExpansion

:: Check for arguments
if "%~1"=="logless" (
    set "WINDOW_FLAG=-mwindows"
) else (
    set "WINDOW_FLAG="
)

:: --- Directories ---
set "PROJECT_ROOT=D:\Studio\Games\vanhorn\"
set "SRC_DIR=%PROJECT_ROOT%src"
set "OUT_DIR=%PROJECT_ROOT%bin"
set "INCLUDE_DIR=%SRC_DIR%\include"
set "LIB_DIR=%SRC_DIR%\lib"

:: Ensure output directory exists
if not exist "%OUT_DIR%" mkdir "%OUT_DIR%"

:: Close any running instance of vanhorn.exe
taskkill /f /im vanhorn.exe >nul 2>&1

:: --- Build Options ---
set "EXE_NAME=vanhorn.exe"

:: --- Compiler ---
set "CC=gcc"

:: --- Compiler Flags ---
set "STD=-std=c99"
set "OPTIMIZATION=-O3"
set "WARNINGS=-Wall"

:: --- Flags & Libraries ---
set "INCLUDES=-I "%INCLUDE_DIR%""
set "LIB_DIRS=-L "%LIB_DIR%""
set "LIBS=-lraylib -lopengl32 -lgdi32 -lwinmm"

:: Initialize SOURCES variable to empty
set "SOURCES="

:: Automatically find and append all .c files in SRC_DIR to SOURCES and echo each
for /r "%SRC_DIR%" %%f in (*.c) do (
    echo Compiling %%f...
    set "SOURCES=!SOURCES! %%f"
)

:: --- Compile Command ---
%CC% !SOURCES! -o "%OUT_DIR%\%EXE_NAME%" %STD% %OPTIMIZATION% %WARNINGS% %INCLUDES% %LIB_DIRS% %LIBS% %WINDOW_FLAG%
if %errorlevel% == 0 (
    echo Compilation successful.
) else (
    echo Compilation failed.
    pause 
)

:: End of script
endlocal