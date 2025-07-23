# Build Instructions

To compile manually, do:

```
c++ -isystem /usr/include/x86_64-linux-gnu/mpich -std=gnu++11 -o main.cpp.o -c main.cpp
c++ main.cpp.o -o simplempi /usr/lib/x86_64-linux-gnu/libmpichcxx.so /usr/lib/x86_64-linux-gnu/libmpich.so
```

To compile with cmake, do the following.
The `-DCMAKE_EXPORT_COMPILE_COMMANDS` option is necessary for the LSP to properly track dependencies.

```
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build build
```
