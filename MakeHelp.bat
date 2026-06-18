@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by VINCENT.HPJ. >"hlp\Vincent.hm"
echo. >>"hlp\Vincent.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\Vincent.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\Vincent.hm"
echo. >>"hlp\Vincent.hm"
echo // Prompts (IDP_*) >>"hlp\Vincent.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\Vincent.hm"
echo. >>"hlp\Vincent.hm"
echo // Resources (IDR_*) >>"hlp\Vincent.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\Vincent.hm"
echo. >>"hlp\Vincent.hm"
echo // Dialogs (IDD_*) >>"hlp\Vincent.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Vincent.hm"
echo. >>"hlp\Vincent.hm"
echo // Frame Controls (IDW_*) >>"hlp\Vincent.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\Vincent.hm"
REM -- Make help for Project VINCENT


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\Vincent.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\Vincent.hlp" goto :Error
if not exist "hlp\Vincent.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\Vincent.hlp" Debug
if exist Debug\nul copy "hlp\Vincent.cnt" Debug
if exist Release\nul copy "hlp\Vincent.hlp" Release
if exist Release\nul copy "hlp\Vincent.cnt" Release
echo.
goto :done

:Error
echo hlp\Vincent.hpj(1) : error: Problem encountered creating help file

:done
echo.
