#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>	
#include "struct.h"
#include "prefetch.h"
#include "declaration.h"

/*
Main Data Structure = 2-Dimensional Array.

Helping Methods for main function.
All the required methods for :-
Fetching, reading, writing, bit transformation, char to int, finding log and check for empty block.
*/

//Converting Argument from character to integer.
unsigned long long ChartoInt (char* A) {

unsigned long long X = 1;
unsigned long long Y = 0;
int Size = strlen(A);
//for(int m = Size; m>=0, m++);
for(int m = Size -1 ; m >= 0 ; m=m-1) {
Y = Y + ((int)A[m] - 48)* X;
unsigned long long C = X * 10;
X = C;
}
return Y;
}

/*
unsigned long long ChartoInt (char* A, char* B) {

unsigned long long X = 1;
unsigned long long Y = 0;
int Size = strlen(A);
int n = Size-1;
//for(int m = n; m>0, m--);
for(int m = n ; m >= 0 ; m=m-1) {
Y = Y + ((int)A[m] - 24)* X;
unsigned long long C = (X * 10) / 2;
X = C;
}
return Y;
}
*/

// Creating A Cache. (filling it up)
CacheMemory** Creator(int SIndex,int x,int Associativity)  {

struct CacheMemory** Alloc = (CacheMemory**)malloc(SIndex*sizeof(CacheMemory*));
Cache = Alloc;
int Size = SIndex;
for(int a=0;a< Size;a=a+1) {
struct CacheMemory* Alloc1 = (CacheMemory*)malloc((Associativity)*sizeof(CacheMemory));
Cache[a]= Alloc1;
}
//nested loops for checking empty.
for(int a=0;a< Size;a=a+1) {
int Size1 = Associativity;
for(int b=0;b< Size1;b=b+1) {
int z = 1;
Cache[a][b].ValidBit=z-1;
}
}
struct CacheMemory **Answer = Cache;
return Answer;
}


// Transforming Bits for Blockoffset and Tagg.
int BitTransformation(int x) {

int Answer;
//Answer = 1 >> x; //Shifting Bits.
Answer = 1 << x; //Shifting Bits.

return Answer;
}

// Transforming Bits for Blockoffset and Tagg.
unsigned long long Transformation(unsigned long long x, int y) {

int Answer;
//Answer = x << y; //Shifting Bits.
Answer = x >> y; //Shifting Bits.

return Answer; 
}

void CheckifEmpty(int SIndex,int x,int Associativity) {

int Size = SIndex;
int Size1 = Associativity;
int z = 1;
for(int a=0;a< Size;a=a+1) {
for(int b=0;b< Size1;b=b+1) {
Cache[a][b].SetIndex=z-1;
Cache[a][b].ValidBit=z-1;
Cache[a][b].Policy=z-1;
//Cache[b][a].SetIndex=z-1;
//Cache[b][a].ValidBit=z-1;
//Cache[b][a].Policy=z-1;
}
}
CacheMiss=z-1;
CacheHit=z-1;
//DirtyBit = z-1;
MemoryRead=z-1;
//SetIndex = z-1;
MemoryWrite=z-1;
number=z;
}

//Finding Log with specific base.
int Logger(int x, int base) { 

//int A = log(x);
//int B = log(base);
return log(x) / log(base); 
}

//Divider
int DivisionCalc (int x, int y) {
int a = x;
int b =y;
int c = a/b;
return c;
}

/* 
Using FIFO POLICY.
*/

//Reading Cache.
void Read(unsigned long long Tagg, int x,unsigned long long Setter,int Associativity) {

int Size = Associativity;
for(int m=0;m< Size;m=m+1) {
int k = 0;
if(Cache[Setter][m].ValidBit==k) {
CacheMiss = Increment(CacheMiss);
MemoryRead = Increment(MemoryRead);
number = number + 1;
int z = 1;
//Cache[Setter][m-1].ValidBit=T;	
//Cache[Setter][m-1].Policy=number;
//Cache[Setter][m-1].SetIndex=Tagg;
Cache[Setter][m].ValidBit=z;
Cache[Setter][m].SetIndex=Tagg;
Cache[Setter][m].Policy=number;
return;
} else {
//x = x -1;
unsigned long long compare = Cache[Setter][m].SetIndex;
if(compare==Tagg) {
CacheHit = Increment(CacheHit);
return;
}
int H = Associativity-1;
if(m==H) {
CacheMiss = Increment(CacheMiss);
//x++;
MemoryRead = Increment(MemoryRead);
int Q = 0;
for(int n=0;n< Size;n=n+1) {
unsigned long long Policy1 = Cache[Setter][Q].Policy;
unsigned long long Policy2 = Cache[Setter][n].Policy;
if(Policy1 >= Policy2) {
Q=n;
}	
}
int z = 1;
Cache[Setter][Q].ValidBit=z;
Cache[Setter][Q].SetIndex=Tagg;
number = number + 1;
Cache[Setter][Q].Policy=number;
return;
}
}
}
return;
}	

// Writing Cache.
void Write(unsigned long long Tagg,int x,unsigned long long Setter,int Associativity) {

int Size = Associativity;
for(int m=0;m< Size;m=m+1) {
int k = 0;
if(Cache[Setter][m].ValidBit==k) {
//CacheHit = Increment(CacheHit);
CacheMiss = Increment(CacheMiss);
MemoryRead = Increment(MemoryRead);
MemoryWrite = Increment(MemoryWrite);
number = number + 1;
int z = 1;
//Cache[Setter][m-1].ValidBit=T;	
//Cache[Setter][m-1].Policy=number;
//Cache[Setter][m-1].SetIndex=Tagg;
Cache[Setter][m].ValidBit=z;
Cache[Setter][m].SetIndex=Tagg;
Cache[Setter][m].Policy=number;
return;
} else {
unsigned long long compare = Cache[Setter][m].SetIndex;
if(compare==Tagg) {
CacheHit = Increment(CacheHit);
MemoryWrite = Increment(MemoryWrite);
return;
}
int H = Associativity-1;
if(m==H) {
//CacheHit = Increment(CacheHit);
CacheMiss = Increment(CacheMiss);
MemoryRead = Increment(MemoryRead);
MemoryWrite = Increment(MemoryWrite);
int Q=0;
for(int n=0;n< Size;n=n+1) {
unsigned long long Policy1 = Cache[Setter][Q].Policy;
unsigned long long Policy2 = Cache[Setter][n].Policy;
if(Policy1 >= Policy2) {
Q=n;
}	
}
int z = 1;
Cache[Setter][Q].ValidBit=z;
Cache[Setter][Q].SetIndex=Tagg;
number = number + 1;
Cache[Setter][Q].Policy=number;
return;
}
}
}
return;
}


void Fetcher1(unsigned long long Tagg,unsigned long long Setter,int Associativity,int x,unsigned long long TaggA,unsigned long long SetterA) {
	
int Size = Associativity;
for(int m=0;m< Size;m=m+1) {
int z = 0;
if(Cache[Setter][m].ValidBit==z) {
//CacheHit = Increment(CacheHit);
CacheMiss = Increment(CacheMiss);
MemoryRead = Increment(MemoryRead);
//MemoryWrite = Increment(MemoryWrite);
//x += 1;
number += 1;
int T =1; 
//Cache[Setter][m-1].ValidBit=T;	
//Cache[Setter][m-1].Policy=number;
//Cache[Setter][m-1].SetIndex=Tagg;
Cache[Setter][m].ValidBit=T;	
Cache[Setter][m].Policy=number;
Cache[Setter][m].SetIndex=Tagg;
PreFetching(TaggA,5,SetterA,Associativity);
return;
} else {
unsigned long long compare = Cache[Setter][m].SetIndex;
if(compare==Tagg) {
CacheHit += 1;
return;
}
int H = Associativity-1;
if(m==H) {
//x += 1;
//CacheHit = Increment(CacheHit);
CacheMiss = Increment(CacheMiss);
MemoryRead = Increment(MemoryRead);
//MemoryWrite = Increment(MemoryWrite);
int Q=0;
for(int n=0;n<Size;n=n+1) {
unsigned long long Policy1 = Cache[Setter][Q].Policy;
unsigned long long Policy2 = Cache[Setter][n].Policy;
if(Policy1 >= Policy2) {
Q=n;
}	
}
int T = 1;
Cache[Setter][Q].ValidBit=T;
Cache[Setter][Q].SetIndex=Tagg;
number += 1;
Cache[Setter][Q].Policy=number;
PreFetching(TaggA,5,SetterA,Associativity);
return;
}
}
}
return;
}


void Fetcher2(unsigned long long Tagg,unsigned long long Setter,int Associativity,int x,unsigned long long TaggA,unsigned long long SetterA) {

int Size = Associativity;
for(int m=0;m< Size;m=m+1) {
int z = 0;
if(Cache[Setter][m].ValidBit==z) {
//CacheHit = Increment(CacheHit);
CacheMiss = Increment(CacheMiss);
MemoryRead = Increment(MemoryRead);
MemoryWrite = Increment(MemoryWrite);
number += 1;
int T = 1;
//Cache[Setter][m-1].ValidBit=T;	
//Cache[Setter][m-1].Policy=number;
//Cache[Setter][m-1].SetIndex=Tagg;
Cache[Setter][m].ValidBit=T;
Cache[Setter][m].Policy=number;
Cache[Setter][m].SetIndex=Tagg;
PreFetching(TaggA,5,SetterA,Associativity);
return;
} else {
unsigned long long compare = Cache[Setter][m].SetIndex;
if(compare==Tagg) {
CacheHit = Increment(CacheHit);
//CacheMiss = Increment(CacheMiss);
//MemoryRead = Increment(MemoryRead);
MemoryWrite = Increment(MemoryWrite);
return;
}
int H = Associativity-1;
if(m==H) {
//CacheHit = Increment(CacheHit);
CacheMiss = Increment(CacheMiss);
MemoryRead = Increment(MemoryRead);
MemoryWrite = Increment(MemoryWrite);
int Q=0;
for(int n=0;n<Size;n=n+1) {
unsigned long long Policy1 = Cache[Setter][Q].Policy;
unsigned long long Policy2 = Cache[Setter][n].Policy;
if(Policy1 >= Policy2) {
Q=n;
}	
}
int N = 1;
Cache[Setter][Q].ValidBit=N;
Cache[Setter][Q].SetIndex=Tagg;
number += 1;
Cache[Setter][Q].Policy=number;
PreFetching(TaggA,5,SetterA,Associativity);
return;
}
}
}
return;
}

//Method to Print cache in specific format for both with-prefetch and no-prefetch.
void PrintCache(int MemoryRead,int MemoryWrite,int CacheHit,int CacheMiss) {

int A = MemoryRead;
int B = MemoryWrite;
int C = CacheHit;
int D = CacheMiss;
printf("Memory reads: %d\n",A);
printf("Memory writes: %d\n",B);
printf("Cache hits: %d\n",C);
printf("Cache misses: %d\n",D);

}  

/*
Using LRU (Least Recently Used) POLICY for Extra Credit.
Just Adding the count for number in all methods to count least used set.
*/

//Read Cache for LRU POLICY.
void Reader1(unsigned long long Tagg,int x,unsigned long long Setter,int Associativity) {

int Size = Associativity;
for(int m=0;m< Size;m=m+1) {
if(Cache[Setter][m].ValidBit==0) {
//x += 1;
//CacheHit = Increment(CacheHit);
CacheMiss = Increment(CacheMiss);
MemoryRead = Increment(MemoryRead);
//MemoryWrite = Increment(MemoryWrite);
number = number + 1;
int z = 1;
//Cache[Setter][m-1].ValidBit=T;	
//Cache[Setter][m-1].Policy=number;
//Cache[Setter][m-1].SetIndex=Tagg;
Cache[Setter][m].ValidBit=z;
Cache[Setter][m].Policy=number;
Cache[Setter][m].SetIndex=Tagg;
return;
} else {
//x = x -1;
unsigned long long compare = Cache[Setter][m].SetIndex;
if(compare==Tagg) {
CacheHit = Increment(CacheHit);
number = number + 1;
Cache[Setter][m].Policy=number;
return;
}
int H = Associativity-1;
if(m==H) {
//CacheHit = Increment(CacheHit);
CacheMiss = Increment(CacheMiss);
MemoryRead = Increment(MemoryRead);
//MemoryWrite = Increment(MemoryWrite);
int Q = 0;
for(int n=0;n< Size;n=n+1) {
unsigned long long Policy1 = Cache[Setter][Q].Policy;
unsigned long long Policy2 = Cache[Setter][n].Policy;
if(Policy1 >= Policy2) {
Q=n;
}	
}
int z = 1;
Cache[Setter][Q].ValidBit=z;
Cache[Setter][Q].SetIndex=Tagg;
number = number + 1;
Cache[Setter][Q].Policy=number;
return;
}
}
}
return;
}

//Write Cache for LRU POLICY.
void Writer1(unsigned long long Tagg,int x,unsigned long long Setter,int Associativity) {

int Size = Associativity;
for(int m=0;m< Size;m=m+1) {
if(Cache[Setter][m].ValidBit==0) {
//CacheHit = Increment(CacheHit);
CacheMiss = Increment(CacheMiss);
MemoryRead = Increment(MemoryRead);
MemoryWrite = Increment(MemoryWrite);
number = number + 1;
int z = 1;
//Cache[Setter][m-1].ValidBit=T;	
//Cache[Setter][m-1].Policy=number;
//Cache[Setter][m-1].SetIndex=Tagg;
Cache[Setter][m].ValidBit=z;
Cache[Setter][m].SetIndex=Tagg;
Cache[Setter][m].Policy=number;
return;
} else {
unsigned long long compare = Cache[Setter][m].SetIndex;
if(compare==Tagg) {
CacheHit = Increment(CacheHit);
//CacheMiss = Increment(CacheMiss);
//MemoryRead = Increment(MemoryRead);
MemoryWrite = Increment(MemoryWrite);
number++;
Cache[Setter][m].Policy=number;
return;
}
int H = Associativity-1;
if(m==H) {
//CacheHit = Increment(CacheHit);
CacheMiss = Increment(CacheMiss);
MemoryRead = Increment(MemoryRead);
MemoryWrite = Increment(MemoryWrite);
int Q=0;
for(int n=0;n< Size;n=n+1) {
unsigned long long Policy1 = Cache[Setter][Q].Policy;
unsigned long long Policy2 = Cache[Setter][n].Policy;
if(Policy1 >= Policy2) {
Q=n;
}	
}
int z = 1;
Cache[Setter][Q].ValidBit=z;
Cache[Setter][Q].SetIndex=Tagg;
number = number + 1;
Cache[Setter][Q].Policy=number;
return;
}
}
}
return;
}



void Fetcher3(unsigned long long Tagg,unsigned long long Setter,int Associativity,int x,unsigned long long TaggA,unsigned long long SetterA) {
	
int Size = Associativity;
for(int m=0;m< Size;m=m+1) {
int z = 0;
if(Cache[Setter][m].ValidBit==z) {
//x += 1;
//CacheHit = Increment(CacheHit);
CacheMiss = Increment(CacheMiss);
MemoryRead = Increment(MemoryRead);
//MemoryWrite = Increment(MemoryWrite);
number += 1;
int T =1;
//Cache[Setter][m-1].ValidBit=T;	
//Cache[Setter][m-1].Policy=number;
//Cache[Setter][m-1].SetIndex=Tagg;
Cache[Setter][m].ValidBit=T;
Cache[Setter][m].Policy=number;
Cache[Setter][m].SetIndex=Tagg;
PreFetching(TaggA,5,SetterA,Associativity);
return;
} else {
unsigned long long compare = Cache[Setter][m].SetIndex;
if(compare==Tagg) {
//x += 1;
CacheHit = Increment(CacheHit);
//CacheMiss = Increment(CacheMiss);
//MemoryRead = Increment(MemoryRead);
//MemoryWrite = Increment(MemoryWrite);
number += 1;
Cache[Setter][m].Policy=number;
return;
}

int H = Associativity-1;
if(m==H) {
//CacheHit = Increment(CacheHit);
CacheMiss = Increment(CacheMiss);
MemoryRead = Increment(MemoryRead);
//MemoryWrite = Increment(MemoryWrite);
int Q=0;
for(int n=0;n<Size;n=n+1) {
unsigned long long Policy1 = Cache[Setter][Q].Policy;
unsigned long long Policy2 = Cache[Setter][n].Policy;
if(Policy1 >= Policy2) {
Q=n;
}	
}
int T = 1;
Cache[Setter][Q].ValidBit=T;
Cache[Setter][Q].SetIndex=Tagg;
number += 1;
Cache[Setter][Q].Policy=number;
PreFetching(TaggA,5,SetterA,Associativity);
return;
}
}
}
return;
}
	
void Fetcher4(unsigned long long Tagg,unsigned long long Setter,int Associativity,int x,unsigned long long TaggA,unsigned long long SetterA) {
	
int Size = Associativity;
for(int m=0;m< Size;m=m+1) {
int z = 0;
if(Cache[Setter][m].ValidBit==z) {
//CacheHit = Increment(CacheHit);
CacheMiss = Increment(CacheMiss);
MemoryRead = Increment(MemoryRead);
MemoryWrite = Increment(MemoryWrite);
number += 1;
int T = 1;
//Cache[Setter][m-1].ValidBit=T;	
//Cache[Setter][m-1].Policy=number;
//Cache[Setter][m-1].SetIndex=Tagg;
Cache[Setter][m].ValidBit=T;
Cache[Setter][m].Policy=number;
Cache[Setter][m].SetIndex=Tagg;
PreFetching(TaggA,5,SetterA,Associativity);
return;
} else {
unsigned long long compare = Cache[Setter][m].SetIndex;
if(compare==Tagg) {
CacheHit = Increment(CacheHit);
//CacheMiss = Increment(CacheMiss);
//MemoryRead = Increment(MemoryRead);
MemoryWrite = Increment(MemoryWrite);
number += 1;
Cache[Setter][m].Policy=number; 
return;
}

int H = Associativity-1;
if(m==H) {
//CacheHit = Increment(CacheHit);
CacheMiss = Increment(CacheMiss);
MemoryRead = Increment(MemoryRead);
MemoryWrite = Increment(MemoryWrite);
int Q=0;
for(int n=0;n<Size;n=n+1) {
unsigned long long Policy1 = Cache[Setter][Q].Policy;
unsigned long long Policy2 = Cache[Setter][n].Policy;
if(Policy1 >= Policy2) {
Q=n;
}	
}
int N = 1;
Cache[Setter][Q].ValidBit=N;
Cache[Setter][Q].SetIndex=Tagg;
number += 1;
Cache[Setter][Q].Policy=number;
PreFetching(TaggA,5,SetterA,Associativity);
return;
}
}
}
return;
}

//Increment.
int Increment(int x) {

int a = x;
//int b = x = x + 1;
int b = a +=1;
return b;
}

