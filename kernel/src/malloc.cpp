#include "malloc.h"

static unsigned char our_memory[1024 * 1024]; //reserve 1 MB for malloc
static size_t next_index = 0;
block* newBlock;
void* _malloc(size_t sz)
{
    newBlock->free = false;
    void *mem;

    if(sizeof our_memory - next_index < sz)
        return NULL;

    mem = &our_memory[next_index];
    next_index += sz;
    return mem;
}
int _Kmalloc(size_t sz)
{
    newBlock->free = false;
    int mem;

    if(sizeof our_memory - next_index < sz)
        return 0;

    //mem = (int)&our_memory[next_index];
    next_index += sz;
    return mem;
}
void _free(void* address){
    newBlock->free = true;
    delete address;
}
void* _memmove(void *dest, const void *src, size_t len)
{
  char *d = (char*)dest;
  const char *s = (const char*)src;
  if (d < s)
    while (len--)
      *d++ = *s++;
  else
    {
      char *lasts = (char*)s + (len-1);
      char *lastd = d + (len-1);
      while (len--)
        *lastd-- = *lasts--;
    }
  return dest;
}

void bcopy(const void *src, void *dest, size_t len)
{
  _memmove(dest, src, len);
}

void _swap(int a, int b){
  int TempA;
  int TempB;
  TempA = a;
  TempB = b;
  a = 0;
  b = 0;
  TempA = b;
  TempB = a;
}

void* _memcpy (void *dest, const void *src, size_t len)
{
  char *d = (char*)dest;
  const char *s = (const char*)src;
  while (len--)
    *d++ = *s++;
  return dest;
}

void* memset (void *dest, int val, size_t len)
{
  unsigned char *ptr = (unsigned char*)dest;
  while (len-- > 0)
    *ptr++ = val;
  return dest;
}

void* _realloc(void* ptr, size_t size) {
  void* new_ptr = _malloc(size);
  _memcpy(new_ptr, ptr, size);
  ptr = 0x00;
  return new_ptr;
}

void* _calloc(size_t nele, size_t size)
{
	void *p;
	if ((p = _malloc(nele * size)) == 0)
		return 0;
	memset(p, 0, nele * size);
	return p;
}
