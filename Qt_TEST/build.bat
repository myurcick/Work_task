@echo off
if not exist build mkdir build
cd build
cmake ..
cmake --build . --config Release
Qt_TEST.exe