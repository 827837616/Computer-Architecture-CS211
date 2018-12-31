#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/*
Struct Declarations.
*/

typedef struct CacheMemory{
unsigned long long SetIndex;
int ValidBit;
//int BlockOffset;
//unsigned long long LRU;
//unsigned long long FIFO;
unsigned long long Policy;
}CacheMemory;

/*
Declaration of all the global variables
*/

int CacheMiss;
int CacheHit;
//int Read;
//int Write;
struct CacheMemory** Cache;
unsigned long long number;
int MemoryWrite;
int MemoryRead;
//int DirtyBit;
//int TempBit;
