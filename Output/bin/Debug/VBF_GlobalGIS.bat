@echo off
rem 当前盘符
::echo %~d0

rem 当前盘符和路径
::echo %~dp0

rem 当前盘符和路径的短文件名格式
::echo %~sdp0

rem 当前批处理全路径
::echo %~f0

rem 当前CMD默认目录
::echo %cd%

rem 添加boost::log、Qt、zlib依赖库所在路径
::set PATH=%cd%\zlib\1.2.11\win32;%cd%\Qt\4.8.6\win32;%cd%\boost\win32;%PATH%
set PATH=..\3rdParty_vs2010_x86;%PATH%
start VBF_GlobalGIS.exe