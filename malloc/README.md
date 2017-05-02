# wasm-intro/malloc

A trivial example of:

- Defining a WASM function in C
- Accessing WASM linear memory from both JavaScript and C
- Implementing a simple toy malloc/free/sizeof toolchain to manage dynamic memory allocation
- Loading a WASM module and calling a WASM function from JavaScript

The page loads the WASM module, then allocates WASM linear memory using a custom malloc implementation to store strings, which are then read and printed with the help of msize. Next the middle one is freed using mfree, and its memory block is reused for another smaller string allocation.



