#include <stdio.h>
#include <stddef.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include "BasicRenderer.h"

struct block{
    bool free;
    void _CombineForward();
    void _CombineBackward();
    block* next;
    block* last;
};

void* _malloc(size_t sz);
void _free(void* address);
void* _memmove(void *dest, const void *src, size_t len);
void bcopy(const void *src, void *dest, size_t len);
void _swap(int a, int b);
void* _realloc(void* ptr, size_t size);
void* _calloc(size_t nele, size_t size);
void _free(void* address);
void* memset (void *dest, int val, size_t len);
void* _memcpy (void *dest, const void *src, size_t len);

inline void* operator new(size_t size) {return _malloc(size);}
inline void* operator new[](size_t size){return _malloc(size);}

inline void operator delete(void* p){}