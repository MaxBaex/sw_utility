@echo off
rem -------------------------------------------------------------------
rem Batch-File fuer das Versionshochaehlen
rem -------------------------------------------------------------------
rem %1 SetVersion.sh Parameter
cd
.\date "+%%H:%%M:%%S"
sh SetVersion.sh %*
rem pause
rem -------------------------------------------------------------------
rem End of File