# WASM-Intro

A scratchpad of stuff in WebAssembly. All examples are written for simplicity, not good code style nor performance. Please do not use anything here in important stuff.

Much of the toolchain is based on [yurydelendik's "Using WebAssembly in LLVM" gist](https://gist.github.com/yurydelendik/4eeff8248aeb14ce763e).

## Build environment

Run `make build` and `make install` in `tools`. This builds LLVM, clang, binaryen and WABT with correct stuff for WebAssembly compiling.

## Examples

Build by running `make` in each directory. Test using python3 by running `make serve` and browsing to localhost:8000.

To build intermediate results from the C -> WASM compilation, try `make main.s` and `make main.wat`

### Add

Simple function export example. Adds two numbers together and prints to console

### Import/Export

Same as Add, now with an added step of delegating the addition back to JavaScript.

### Memory

Poking an exported linear memory from JS and C.

### Strings

Manipulating JS strings in C.

### Malloc

Implementing a simple toy dynamic memory allocation scheme.

### Animation

Some canvas functions imported to WASM, shows bouncing particles.

### WebGL

Wraps a portion of WebGL API for importing to WASM, draws a moving triangle.

### Pong

Wraps a little more of WebGL API for importing to WASM, plays Pong.
