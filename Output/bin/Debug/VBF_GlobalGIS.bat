@echo off
rem ��ǰ�̷�
::echo %~d0

rem ��ǰ�̷���·��
::echo %~dp0

rem ��ǰ�̷���·���Ķ��ļ�����ʽ
::echo %~sdp0

rem ��ǰ������ȫ·��
::echo %~f0

rem ��ǰCMDĬ��Ŀ¼
::echo %cd%

rem ���boost::log��Qt��zlib����������·��
::set PATH=%cd%\zlib\1.2.11\win32;%cd%\Qt\4.8.6\win32;%cd%\boost\win32;%PATH%
set PATH=..\3rdParty_vs2010_x86;%PATH%
start VBF_GlobalGIS.exe