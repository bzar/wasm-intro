# wasm-intro/strings

A trivial example of:

- Defining a WASM function in C
- Defining external functions callable from C
- Accessing WASM linear memory from both JavaScript and C
- Using unicode, pointers and lengths to perform opaque string manipulation in C
- Loading a WASM module and calling a WASM function from JavaScript and vice versa

The page loads the WASM module, then manipulates and reads its exported memory using both JavaScript typed arrays and C pointers to transform a logged message into a palindrome.


