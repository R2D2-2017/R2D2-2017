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

extern "C" int strcmp(const char *str1, const char *str2) {
    unsigned int i = 0;
    while (1)
    {
        if (str1[i] == '\x00' || str2[i] == '\x00') {
            if (str1[i] == str2[i]) {
                return 0;
            }
            if (str1[i] == '\x00') {
                return -1;
            } else {
                return 1;
            }
        }

        if (str1[i] != str2[i]) {
            if (str1[i] < str2[i]) {
                return -1;
            } else {
                return 1;
            }
        }

        ++i;
    }
}

extern "C" int strncmp(const char *str1, const char *str2, size_t num) {
    unsigned int i = 0;
    while (i < num)
    {
        if (str1[i] == '\x00' || str2[i] == '\x00') {
            if (str1[i] == str2[i]) {
                return 0;
            }
            if (str1[i] == '\x00') {
                return -1;
            } else {
                return 1;
            }
        }

        if (str1[i] != str2[i]) {
            if (str1[i] < str2[i]) {
                return -1;
            } else {
                return 1;
            }
        }

        ++i;
    }
    return 0;
}



extern "C" size_t strlen(const char *string) {
    size_t result = 0;
    while (string[result])
    {
        ++result;
    }
    return result;
}

extern "C" char *strncpy(char* destination, const char *source, size_t num) {
    unsigned int i = 0;
    while (source[i] != '\x00' && i < num)
    {
        destination[i] = source[i];
        ++i;
    }
    destination[i] = '\x00';
    return destination;
}


extern "C" char *strncat ( char *destination, const char *source, size_t num ) {
    size_t destinationEnd = strlen(destination);
    size_t i = 0;
    while(i < num){
        destination[i + destinationEnd] =  source[i];
        ++i;
    }
    destination[i + destinationEnd] = '\x00';
    return destination;
}

extern "C" char *strchr ( char *str, int character ){
    size_t i = 0;
    while (str[i])
    {
        if(str[i] == character){
            return str + i;
        }
        ++i;
    }
    return 0;
}

// }}}

// Needed for virtual destructors.
// See https://stackoverflow.com/a/31686672/1577347
void operator delete(void *p, size_t x) throw() { /*while (true);*/ }
void operator delete(void *p)           throw() { /*while (true);*/ }
