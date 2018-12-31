#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>	

/*
The prefetcher is activated only on misses and it is not active on a cache hit. If the prefetched block is already in the cache, it does not issue a memory read. With respect to cache replacement policies, if the prefetched block hits in the cache, the line replacement policy status should not be updated. Otherwise, it is treated similar to a block that missed the cache.
*/

void PreFetching(unsigned long long Tagg,int x,unsigned long long Setter,int Associativity) {

int Size = Associativity;
for(int m=0;m< Size;m=m + 1) {
int k = 0;
if(Cache[Setter][m].ValidBit==k) {
MemoryRead += 1;
//x +=1;
number += 1;
int z = 1;
Cache[Setter][m].ValidBit=z;
Cache[Setter][m].Policy=number;
Cache[Setter][m].SetIndex=Tagg;
return;
} else {
unsigned long long compare = Cache[Setter][m].SetIndex;
if(compare==Tagg) {
return;
//exit(0);
}
int H = Size - 1;
if(m==H) {
//x +=1; 
MemoryRead += 1;
int Q=0;
for(int n=0;n< Size;n=n + 1) {
unsigned long long Policy1 = Cache[Setter][Q].Policy;
unsigned long long Policy2 = Cache[Setter][n].Policy;
if(Policy1 >= Policy2) {
Q=n;
}	
}
int z = 1;
Cache[Setter][Q].SetIndex=Tagg;
Cache[Setter][Q].ValidBit=z;
number += 1;
//x +=1;
Cache[Setter][Q].Policy=number;
return;
}
}
}
return;
}


