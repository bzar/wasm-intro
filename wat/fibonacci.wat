(module
  (import "env" "printInt" (func $printInt (param i32)))
  (import "env" "print" (func $print (param i32 i32)))

  (memory $memory 1)
  (data (i32.const 0) "\n")
  (data (i32.const 1) " ")

  (func $endl
    (call $print (i32.const 0) (i32.const 1)))
  (func $space
    (call $print (i32.const 1) (i32.const 1)))

  (func $fibonacci (param $a i32) (param $b i32) (param $n i32) (result i32)
    (if (i32.eqz (get_local $n)) (return (get_local $a)))
    (call $printInt (get_local $b))
    (set_local $a (i32.add (get_local $a) (get_local $b)))
    (call $space)
    (call $fibonacci (get_local $b) (get_local $a) (i32.sub (get_local $n) (i32.const 1)))
  )

  (func $main
    (call $fibonacci (i32.const 0) (i32.const 1) (i32.const 9))
    (call $endl)
    drop)

  (export "main" (func $main))
  (export "memory" (memory $memory))
)

