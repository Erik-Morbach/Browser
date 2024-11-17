cmake -S . -B build
cd build
cmake --build .
cp compile_commands.json ../
cd ..
