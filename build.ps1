cmake -S . -B build -G Ninja
cmake --build build/
cp build/compile_commands.json ./

