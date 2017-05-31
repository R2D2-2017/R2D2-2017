/**
 * \file
 * \brief     Libc stub code
 * \author    Chris Smeele
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
// Pretend that we have a cstdlib to please kvasir-toolchain.
extern "C" void __libc_init_array();
extern "C" void __libc_init_array() { }

// Required by MuStore. {{{

// Whoops... we can't get size_t from cstdlib.
using size_t = unsigned int;

extern "C" void *memset(void *m, int v, size_t size) {
    char *p = static_cast<char*>(m);
    for (; size; --size)
        *(p++) = v;
    return m;
}

extern "C" void *memcpy(void *dst, const void *src, size_t size) {
          char *dstp = static_cast<char*>(dst);
    const char *srcp = static_cast<const char*>(src);

    for (size_t i = 0; i < size; ++i)
        dstp[i] = srcp[i];

    return dst;
}

// }}}

// Needed for virtual destructors.
// See https://stackoverflow.com/a/31686672/1577347
void operator delete(void *p, size_t x) throw() { /*while (true);*/ }
void operator delete(void *p)           throw() { /*while (true);*/ }
