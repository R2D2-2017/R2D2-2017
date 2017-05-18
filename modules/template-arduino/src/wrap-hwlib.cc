// Include hwlib """"header only"""" code.
#define HWLIB_ONCE
#include "wrap-hwlib.hh"

// Pretend that we have a C stdlib.
// (required by kvasir-toolchain startup code)
extern "C" void __libc_init_array() { }
