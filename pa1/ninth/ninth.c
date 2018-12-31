#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct NodeN {
int V;
struct NodeN *leftChild;
struct NodeN *rightChild;
} NodeN;

extern int temp;
struct NodeN *Creator(int V);
int Add(struct NodeN **Top, int V);
struct NodeN *Adder(struct NodeN **Top, int V, int Lvl);
int Remove(struct NodeN **Top, int V);
struct NodeN *Remover(struct NodeN *Top, int V);
int Finder(struct NodeN *Top, int V,int Lvl);
int temp;

struct NodeN *Creator(int V) {
struct NodeN *NodeN = (struct NodeN*) malloc(sizeof(struct NodeN));
NodeN->V = V;
NodeN->leftChild = NULL;
NodeN->rightChild = NULL;
return NodeN;
}

int Add(struct NodeN **Top, int V) {
temp = 0;
Adder(Top,V,0);
return temp;
}

struct NodeN * Adder(struct NodeN **Top, int V, int Lvl) {
temp = Lvl;
if (*Top == NULL) {
*Top = Creator(V);
return *Top;
}
if (V < (*Top)->V) {
(*Top)->leftChild = Adder (&(*Top)->leftChild,V,Lvl+1);	
}
else if (V > (*Top)->V) {
(*Top)->rightChild = Adder (&(*Top)->rightChild, V, Lvl+1);
} else {
temp = -1;
}
return *Top;
}

int Remove(struct NodeN **Top, int V) {
if (*Top == NULL) {
return 0;
}
if (Finder(*Top,V,0) == -1) {
return 0;
}
*Top = Remover(*Top,V);
return 1;
}

struct NodeN * Remover(struct NodeN *Top, int V) {
if (Top == NULL) {
return NULL;
}
if (V < Top->V) {
Top->leftChild = Remover (Top->leftChild,V);
}
else if (V > Top->V) {
Top->rightChild = Remover (Top->rightChild,V);
} else {
struct NodeN *MrightChild;
if (Top->leftChild == NULL) {
return Top->rightChild;
}
if (Top->rightChild == NULL) {
return Top->leftChild;
}
MrightChild = Top->rightChild;
while (MrightChild->leftChild != NULL) {
MrightChild = MrightChild->leftChild;
}
Top->V = MrightChild->V;
Top->rightChild = Remover(Top->rightChild,MrightChild->V);	
}
return Top;
}

void HELPER(struct NodeN **M, struct NodeN *Top, int I) {
if (Top != NULL) {
if (Top->V != I) {
Add(M,Top->V);
}
HELPER (M,Top->leftChild,I);
HELPER (M,Top->rightChild,I);
}
}

int Finder(struct NodeN *Top, int V,int Lvl) {
int leftChild;
int rightChild;
Lvl += 1;
if (Top == NULL) {
return -1;
}
if (Top->V == V) {
return Lvl;
}
leftChild = Finder(Top->leftChild,V,Lvl);
if (leftChild != -1) {
return leftChild;
}
rightChild = Finder(Top->rightChild,V,Lvl);
if (rightChild != -1) {
return rightChild;
}
return -1;
}

int main (int argc, char **argv) {
FILE *file;
char character[1000];
struct NodeN *Top = NULL;	
if (argc < 2) {
printf("error\n");
return 0;
}
file = fopen(argv[1],"r");
if (file == NULL) {
printf("error\n");
return 0;
}
while (fgets(character,sizeof(character),file)) {
char *letter = strtok(character,"\t");
int number = atoi(strtok(NULL,"\t"));
if (strcmp(letter,"i") == 0) {
int Lvl = Add(&Top,number);
if (Lvl < 0) {
printf("duplicate\n");
} else {
printf("inserted %d\n",(Lvl+1));
}	
}
else if (strcmp(letter,"s") == 0) {
int LEVEL = Finder(Top,number,0);
if (LEVEL == -1) {
printf("absent\n");
} else {
printf("present %d\n",LEVEL);
}
}
else if (strcmp(letter,"d") == 0) {
int success = Remove(&Top,number);
printf("%s\n",(success == 1 ? "success" : "fail"));
} else {
printf("error\n");
return 0;
}
}
printf("\n");
return 0;	
}
