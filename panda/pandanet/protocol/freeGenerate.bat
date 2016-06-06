@echo ------generating protocol------
@echo off
set /p var=请输入文件名:
echo you cin :%var%
protoc --proto_path=./ --cpp_out=./ %var%

set /p var2=按任意键结束
@echo on
@echo ------    successful     ------
