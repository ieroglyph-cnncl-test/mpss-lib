cd .. && mkdir build 
cd build
cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_CONFIGURATION_TYPE=Release .. 
cmake --build . --config=Release -j9

cd Release/bin
test_mpsslib.exe

pause
