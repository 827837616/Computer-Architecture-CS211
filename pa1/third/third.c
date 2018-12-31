#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
typedef struct NodeN{
int Value;
struct NodeN* After;
} NodeN;
 
NodeN *Hash[10000];
 
int main(int argc, char ** argv) {

if(argc != 2) {
printf("error\n");
return 0;
}

char C[999];
FILE *file;
file = fopen(argv[1],"r");

if(file) {
while (fscanf(file, "%s", C)!=EOF) {
if(strcmp(C, "i") == 0) {
fscanf(file, "%s", C);
int A = atoi(C);
int B = A%10000;
if (B < 0){
B = B*-1;
}

NodeN* Add = Hash[B];
if(Hash[B] == NULL) {
NodeN*T = (NodeN*)malloc(sizeof(NodeN));
T-> Value = A;
T-> After = NULL;
Hash[B] = T;
printf("inserted\n");
} else {
int X = 0;
Add = Hash[B];
if(A == Add->Value) {
printf("duplicate\n");
} else {
while(Add->After != NULL && X == 0) {
if(A == Add->Value){
printf("duplicate\n");
X = 1;
}
Add = Add->After;
}

if(X == 0) {
NodeN* After = (NodeN*)malloc(sizeof(NodeN));
After->Value = A;
After->After = NULL;
Add->After = After;
printf("inserted\n");
}
}
}
} else {
fscanf(file, "%s", C);
int A = atoi(C);
int B = A % 10000;
if (B < 0){
B = B * -1;
}
NodeN*Find = Hash[B];
int X = 0;
while(Find != NULL) {
if(A == Find->Value) {
X = 1;
printf("present\n");
break;
}
Find = Find->After;
}
if(X == 0) {
printf("absent\n");
}
}
}
} else {
puts("error\n");
return 1;
}
int i = 0;
for(; i < 10000; i++) {
NodeN* Removed = Hash[i];
while(Removed) {
NodeN* PTR = Removed->After;
free(Removed);
Removed = PTR;
}
}
return 0;
}
