#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "methods.h"

/*
This is a program to stimulate caches.
Main Data Structure 2 D array.
As per the instructions in the pdf.

Notes :-

Interface to execute the program: ./first <cache size><associativity><cache policy><block size><trace file> 

Print error if not same format.

Specific Output :- with-prefetch and no-prefetch.
Memory reads:
Memory writes:
Cache hit:
Cache misses:
*/
	
int main(int argc, char** argv)  {

if(argc != 6) {
printf("error\n");
}

char *Argument1 = argv[1];
char *Argument2 = argv[2];
//char *Argument3 = argv[3];
char *Argument4 = argv[4];
char *Argument5 = argv[5];

int SizeC= ChartoInt(Argument1);
int SizeB= ChartoInt(Argument4);
int SetAs, SIndex, Associativity;
char CharC;
//int s, t, u, v;
unsigned long long Tagg, Setter, TaggA, SetterA;
unsigned long long Location, NLoc, sm;
//unsigned long long BlockAddr;
int Temp1, Temp2;
//long tm;
//long bm;

/* 
if(argv[2][5]=='d') {
FILE* File;
File=fopen(Argument4,"r"); 

if(File == null) {
return;
}
*/

char Alphabet1 = 'f';
if(argv[3][0]== Alphabet1) {
FILE* File;
File=fopen(Argument5,"r");

//if(File == null) {
//return;
//}


char Alphabet2 = 'd';
char Alphabet5 = ':';
if(argv[2][0]== Alphabet2)  {
int z = 1;
Associativity=z;
int Calc = DivisionCalc(SizeC,SizeB);
SIndex=Calc;

}  else if(argv[2][5]!= Alphabet5)  {
int z = 1;
SIndex=z;
int Calc = DivisionCalc(SizeC,SizeB);
Associativity=Calc;
}  else  {
sscanf(Argument2,"assoc:%d",&SetAs);
Associativity=SetAs;
int Calc = DivisionCalc(SizeC,SizeB);
int FCalc = DivisionCalc(Calc,SetAs);
SIndex= FCalc;
} 
//int Log1 = log(SizeB);
//int Log2 = log(SIndex);
int Calc1 = Logger(SizeB,2);
int Calc2 = Logger(SIndex,2);
Temp1=Calc1;
Temp2= Calc2;
int TFinal = Temp1 + Temp2;
unsigned long long R = BitTransformation(Temp2); 
unsigned long long W = (R-1); // Bit Transformation.
sm = W;

//Create New Cache. (Fill up Cache)
Cache=Creator(SIndex,5,Associativity);

int Comp1 = 2;  
//while(fscanf(File, %c %llx", &CharC, &Location)==Comp1) {
while(fscanf(File, "%c %llx", &CharC, &Location)==Comp1)  {
unsigned long long Transform1 = Transformation(Location, Temp1);
unsigned long long W = (Transform1)&sm;
unsigned long long O = Location>> TFinal;
Setter = W;
Tagg=O;

char Alphabet3 = 'R';
char Alphabet4 = 'W';

if(CharC== Alphabet3) {
// Call Read.
//Calling read before write.
Read(Tagg,5,Setter,Associativity);
}  else if(CharC== Alphabet4) {
// Call Write.
Write(Tagg,5,Setter,Associativity);
} 
} 	
fclose(File);

//File=fopen(Argument4,"r"); 
File=fopen(Argument5,"r");

//if(File == null) {
//return;
//}

printf("no-prefetch\n");
PrintCache(MemoryRead,MemoryWrite,CacheHit,CacheMiss);

CheckifEmpty(SIndex,0,Associativity);

int Comp2 = 2;	
//while(fscanf(File, %c %llx", &CharC, &Location)==Comp2) {
while(fscanf(File, "%c %llx", &CharC, &Location)==Comp2) {
unsigned long long Transform2 = Transformation(Location, Temp1);
unsigned long long W = (Transform2)&sm;
unsigned long long O = Location>>TFinal;
Setter= W;
Tagg= O;

NLoc=Location+SizeB;
unsigned long long F = NLoc;
unsigned long long Transformed = Transformation(F, Temp1);
unsigned long long R = (Transformed)&sm;
unsigned long long T = F>>TFinal;
SetterA = R;
TaggA= T;

char Alphabet3 = 'R';
char Alphabet4 = 'W';
if(CharC== Alphabet3) {
//fetch Data.
Fetcher1(Tagg,Setter,Associativity,5,TaggA,SetterA);
} else if(CharC== Alphabet4) {
//fetch Data.
Fetcher2(Tagg,Setter,Associativity,5,TaggA,SetterA);
} 
} 

// Printing Cache.
printf("with-prefetch\n");
PrintCache(MemoryRead,MemoryWrite,CacheHit,CacheMiss);

}  else if(argv[3][0]=='l') {
	
FILE* File;
File=fopen(Argument5,"r");

//if(File == null) {
//return;
//}

char Alphabet6 = 'd';
char Alphabet7 = ':';
if(argv[2][0]== Alphabet6) {
int z = 1;
Associativity=z;
int Calc = DivisionCalc(SizeC,SizeB);
SIndex= Calc;

} else if(argv[2][5]!= Alphabet7) {
int z = 1;
SIndex=z;
int Calc = DivisionCalc(SizeC,SizeB);
Associativity= Calc;
} else {
sscanf(Argument2,"assoc:%d",&SetAs);
Associativity=SetAs;
int Calc = DivisionCalc(SizeC,SizeB);
int FCalc = DivisionCalc(Calc,SetAs);
SIndex = FCalc;
} 

int Calc1 = Logger(SizeB,2);
int Calc2 = Logger(SIndex,2);
Temp1=Calc1;
Temp2= Calc2;
int TFinal = Temp1 + Temp2;
unsigned long long R = BitTransformation(Temp2); 
unsigned long long W = (R-1); // Bit Transformation.
sm = W;

//Create New Cache. (Fill up Cache)
Cache=Creator(SIndex,5,Associativity);

int Comp1 = 2;
//while(fscanf(File, %c %llx", &CharC, &Location)==Comp1) {
while(fscanf(File, "%c %llx", &CharC, &Location)==Comp1)  {
unsigned long long Transform1 = Transformation(Location, Temp1);
unsigned long long W = (Transform1)&sm;
unsigned long long O = Location>>TFinal;
Setter = W;
Tagg=O;

char Alphabet3 = 'R';
char Alphabet4 = 'W';
if(CharC== Alphabet3) {
// Call Read.
//Calling read before write.
Reader1(Tagg,5,Setter,Associativity);
}  else if(CharC== Alphabet4) {
// Call Write.
Writer1(Tagg,5,Setter,Associativity);
} 
} 
fclose(File);


File=fopen(Argument5,"r");

//if(File == null) {
//return;
//}

//Print Cache.
printf("no-prefetch\n");
PrintCache(MemoryRead,MemoryWrite,CacheHit,CacheMiss);

//Check for Empty.
CheckifEmpty(SIndex,0,Associativity);

int Comp2 = 2;
//while(fscanf(File, %c %llx", &CharC, &Location)==Comp2) {
while(fscanf(File, "%c %llx", &CharC, &Location)==Comp2) {
unsigned long long Transform2 = Transformation(Location, Temp1);
unsigned long long W = (Transform2)&sm;
unsigned long long O = Location>>TFinal;
Setter = W;
Tagg=O;

NLoc=Location+SizeB;
unsigned long long F = NLoc;
unsigned long long Transformed = Transformation(F, Temp1);
unsigned long long R = (Transformed)&sm;
unsigned long long T = F>>TFinal;
SetterA = R;
TaggA= T;

char Alphabet3 = 'R';
char Alphabet4 = 'W';
if(CharC== Alphabet3) {
//fetch Data.
Fetcher3(Tagg,Setter,Associativity,5,TaggA,SetterA);
} else if(CharC== Alphabet4) {
//fetch Data.
Fetcher4(Tagg,Setter,Associativity,5,TaggA,SetterA);
} 
} 

//Cache Print
printf("with-prefetch\n");
PrintCache(MemoryRead,MemoryWrite,CacheHit,CacheMiss);

} else {
printf("error\n");
exit(0);
//printf("no Policy available to stimulate current Cache.");
//printf("check the format of input and output.")
//return;
} 
//free(MemoryRead);
//free(MemoryWrite);
//free(CacheHit);
//free(CacheMiss);
return 0;
}
