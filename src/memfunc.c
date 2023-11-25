#include "memfunc.h"
#include "stdarg.h"

// GCC and Clang reserve the right to generate calls to the following
// 4 functions even if they are not directly called.
// Implement them as the C specification mandates.
// DO NOT remove or rename these functions, or stuff will eventually break!
// They CAN be moved to a different .c file.
 
void *memcpy(void *dest, const void *src, size_t n) {
    uint8_t *pdest = (uint8_t *)dest;
    const uint8_t *psrc = (const uint8_t *)src;
 
    for (size_t i = 0; i < n; i++) {
        pdest[i] = psrc[i];
    }
 
    return dest;
}
 
void *memset(void *s, int c, size_t n) {
    uint8_t *p = (uint8_t *)s;
 
    for (size_t i = 0; i < n; i++) {
        p[i] = (uint8_t)c;
    }
 
    return s;
}
 
void *memmove(void *dest, const void *src, size_t n) {
    uint8_t *pdest = (uint8_t *)dest;
    const uint8_t *psrc = (const uint8_t *)src;
 
    if (src > dest) {
        for (size_t i = 0; i < n; i++) {
            pdest[i] = psrc[i];
        }
    } else if (src < dest) {
        for (size_t i = n; i > 0; i--) {
            pdest[i-1] = psrc[i-1];
        }
    }
 
    return dest;
}
 
int memcmp(const void *s1, const void *s2, size_t n) {
    const uint8_t *p1 = (const uint8_t *)s1;
    const uint8_t *p2 = (const uint8_t *)s2;
 
    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }
 
    return 0;
}


void reverse_it(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
        char the_epic = str[start];
        str[start] = str[end];
        str[end] = the_epic;
        end--;
        start++;
    }
}
char intstringoutput[64];
const char *to_string(uint64_t value)
{
    memset(intstringoutput, 0, sizeof(intstringoutput));
    int i = 0;
    uint64_t tmp = value;
    if (tmp == 0)
    {
        intstringoutput[i++] = '0';
        intstringoutput[i] = '\0';
        return intstringoutput;
    }
    while (tmp != 0)
    {
        int remind = tmp % 10;
        intstringoutput[i++] = remind + '0';
        tmp = tmp / 10;
    }

    intstringoutput[i] = '\0';

    reverse_it(intstringoutput, i);

    return intstringoutput;
}
char hexTo_StringOutput[64];
const char* to_hstring(uint64_t value){
    uint64_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 8 * 2 - 1;
    for (uint8_t i = 0; i < size; i++){
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexTo_StringOutput[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        hexTo_StringOutput[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    hexTo_StringOutput[size + 1] = 0;
    return hexTo_StringOutput;
}

int strlen(const char *msg)
{
    int l = 0;
    while (msg[l] != '\0')
    {
        l += 1;
    }
    return l;
}
// i stole from lyre this function lol
int strncmp(const char *s1, const char *s2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        char c1 = s1[i], c2 = s2[i];
        if (c1 != c2) {
            return c1 - c2;
        }
        if (!c1) {
            return 0;
        }
    }

    return 0;
}
