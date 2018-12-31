#include<stdio.h>
#include<stdlib.h>

struct NodeN
{
int Value;
struct NodeN *LeftChild;
struct NodeN *RightChild;
};

void Helper(struct NodeN* Head) {
if(Head==NULL)
return;
Helper(Head->LeftChild);
Head->LeftChild=NULL;
Helper(Head->RightChild);
Head->RightChild=NULL;
free(Head); 
Head=NULL; 
return;
}

void Finder(struct NodeN* Head, int Value, int Height) {
if(Head==NULL) {
printf("absent\n");
return;
}
else if(Head->Value==Value) {
printf("present %d\n", Height + 1);
}
else if(Head->Value < Value) {
Finder(Head->RightChild, Value, Height+1);
} else {
Finder(Head->LeftChild, Value, Height+1);
}
}

struct NodeN* Adder(struct NodeN *Head, int Value, int Height) {
if(Head==NULL) {
Head=(struct NodeN*)malloc(sizeof(struct NodeN));
(*Head).Value=Value;
Head->LeftChild=NULL;
Head->RightChild=NULL;
Height++;
printf("inserted %d\n", Height );
return Head;
}
else if (Head->Value == Value) {
printf("duplicate\n");
return Head;
}
else if(Head->Value < Value) {
(*Head).RightChild = Adder(Head->RightChild, Value, Height+1 );
} else {
(*Head).LeftChild= Adder(Head->LeftChild, Value, Height+1);
}
return Head;
}

int main(int argc, char const *argv[]) {
struct NodeN *Head=NULL;
if(argc<2) {
printf("error\n");
exit(0);
}
FILE *file=fopen(argv[1],"r");
if(file==NULL) {
printf("error\n");
return 0;
}
fseek(file, 0, SEEK_END);
if(ftell(file)==0) {
printf("\n");
return 0;
}
fseek(file, 0, SEEK_SET);
char character; int entry;  
while(!feof(file)) {
fscanf(file, "%c %d\n", &character, &entry);
if(character=='i') {
Head=Adder(Head, entry, 0);
}
else if(character=='s') {
Finder(Head, entry, 0);
} else {
printf("error\n");
exit(0);
}
}
fclose(file);
Helper(Head);
return 0;
}
