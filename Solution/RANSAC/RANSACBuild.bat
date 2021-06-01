for /f "delims=" %%A in (
'"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -property installationPath'
) do set "VS_PATH=%%A"

echo %VS_PATH%

call "%VS_PATH%\VC\Auxiliary\Build\vcvarsall.bat" x86


set location = "%~dp0"
set pathMSBuild = "%SYSTEMROOT%\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe"

@echo off

call %pathMSBuild%
cd %location%
msbuild.exe "%~dp0RANSAC.sln" /t:clean,build /p:configuration=debug

start "RANSAC" "%~dp0Debug\RANSAC.exe"

pause