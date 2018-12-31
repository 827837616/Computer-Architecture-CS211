#include <stdio.h>
#include <stdlib.h>

struct NodeN {
int Value;
struct NodeN* next;
};

struct NodeN* Insert(struct NodeN* Top, int A);

struct NodeN* Insert(struct NodeN* Top, int A) {
struct NodeN* Size = (struct NodeN*) malloc(sizeof(struct NodeN));
struct NodeN* Present = Top;
struct NodeN* Before = NULL;
Size->Value = A;
Size->next = NULL;

while(Present != NULL) {
if(A < Present->Value)
break;
else if(A == Present->Value) 
return Top;
Before = Present;
Present = Present->next;
}

Size->next = Present;
if(Before != NULL) {
Before->next = Size;
} else {
Top = Size;
}
return Top;
}

struct NodeN* Remove(struct NodeN* Top, int A);

struct NodeN* Remove(struct NodeN* Top, int A) {
struct NodeN* Before = NULL;
struct NodeN* Present = Top;

while(Present != NULL){
if(A < Present->Value)
return Top;
else if(A == Present->Value)
break;
Before = Present;
Present = Present->next;
}

if(Present == NULL) 
return Top;
if(Before == NULL) 
Top = Present->next;
else
Before->next = Present->next;
free(Present);
return Top;
}

void Traverse(struct NodeN* Top);

void Traverse(struct NodeN* Top) {
struct NodeN* Present = Top;

if(Top != NULL){
printf("%d", Present->Value);
Present = Present->next;

while(Present != NULL){
printf("\t%d", Present->Value);
Present = Present->next;
}
}
printf("\n");
}


int Height(struct NodeN* Top);

int Height(struct NodeN* Top) {
struct NodeN* Present = Top;
int X = 0;

while(Present != NULL) {
X++;
Present = Present->next;
}
return X;
}


int main(int argc, char* argv[]) {

FILE *file;
struct NodeN* Top = NULL;
int A;
char C;

file = fopen(argv[1], "r");
if(file == NULL) {
printf("error\n");
return 1;
}

fscanf(file, "%c %d", &C, &A);

while(!feof(file)) {
if(C == 'i')
Top = Insert(Top, A);
else if(C == 'd')
Top = Remove(Top, A);
fscanf(file, "%c %d", &C, &A);
}

fclose(file);
printf("%d\n",Height(Top));
Traverse(Top);
return 0;
}

