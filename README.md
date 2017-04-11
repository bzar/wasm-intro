# WASM-Intro

A scratchpad of stuff in WebAssembly

## Build environment

Run `make build` and `make install` in `tools`. This builds LLVM, clang, binaryen and WABT with correct stuff for WebAssembly compiling.

## Examples

Build by running `make` in each directory. Test using python3 by running `make serve` and browsing to localhost:8000.

### Add

Simple function export example. Adds two numbers together and prints to console

### Import/Export

Same as Add, now with an added step of delegating the addition back to JavaScript.

