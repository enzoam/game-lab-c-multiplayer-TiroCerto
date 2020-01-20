REM ===========================================================================
REM = Script para realizar a Exportacao dos Sources por email com senha (gmail)
REM = 1. Configure o ZIP7LOCATION do BackupSources.bat
REM = 2. Configure o Nome do Projeto
REM = 3. Rode o programa com CLICK DUPLO pelo VisualStudio
REM = 4. Sera salvo em ../Backup/<NOMEDOPROJETO>
REM ===========================================================================

set NOMEDOPROJETO=TiroCertoServer
BackupSources.bat %NOMEDOPROJETO%