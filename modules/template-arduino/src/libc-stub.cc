// Pretend that we have a cstdlib to please kvasir-toolchain.
extern "C" void __libc_init_array();
extern "C" void __libc_init_array() { }
