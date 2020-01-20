REM ===========================================================================
REM = Script para realizar a Exportacao dos Sources por email com senha (gmail)
REM = 1. Configure o ZIP7LOCATION (se nao tiver baixe)
REM = 2. Rode o comando: BackupSources.bat <Nome do Projeto>
REM = 3. Procure pelo arquivo salvo na pasta anterior (../backup/)
REM ===========================================================================

set ZIP7LOCATION="C:\Program Files (x86)\7-Zip\7z.exe"
REM http://www.7-zip.org/download.html

set sProgramName=%1

set hour=%time:~0,2%
if "%hour:~0,1%" == " " set hour=0%hour:~1,1%

set min=%time:~3,2%
if "%min:~0,1%" == " " set min=0%min:~1,1%

set secs=%time:~6,2%
if "%secs:~0,1%" == " " set secs=0%secs:~1,1%

set FileDate=%date:~10,4%%date:~4,2%%date:~7,2%-%hour%%min%%secs%
set BackupFile=../Backup/%sProgramName%_sources_%FileDate%.7z

del %BackupFile%
%ZIP7LOCATION% a -t7z -mhe=on -mx=1 -p1458 %BackupFile% -i@backup_include.txt -xr@backup_exclude.txt