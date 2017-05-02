# wasm-intro/webgl

A trivial example of:

- Defining a WASM function in C
- Wrapping WebGL API for calling from WASM
- Animation through onAnimationFrame -> WASM -> Canvas API
- Loading a WASM module, providing external functions and calling a WASM function from JavaScript and vice versa

The page loads the WASM module and calls it each animation frame to draw a moving triangle on a canvas using WebGL.

