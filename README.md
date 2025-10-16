# C++ QR code generator

This is a simple program to create and render QR codes in an GTK3 window, using provided text.

## Dependencies

The following are required to build and run the program:
- Any C compiler
- CMake
- GTK3
- Package Config

## Building and Running

To build:
```bash
mkdir -p build
cd build
cmake ..
make -j$(nproc)
```

To run with some text:
```bash
./qr-gen "https://example.com"
```

Then a window should open with a QR code containing the string
