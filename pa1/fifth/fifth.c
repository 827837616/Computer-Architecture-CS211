#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
	
if (argc < 2) {
printf("error");
return 0;
}

FILE *FILE;
char C [700];
FILE = fopen(argv[1],"r");

if (FILE == NULL){
printf("error/n");
return 0;
}

fscanf(FILE,"%s\n",C);
char * Power = strtok(C,"\n");
int A = 0; 
int B = 0;
int D = 0;
int E=0;
int F=0;
int G=0;
int H=0;
int MatrixSquare = atoi(Power);
int A_Matrix [(MatrixSquare)*(MatrixSquare)];
int MATRIX [MatrixSquare][MatrixSquare];

while (fscanf(FILE, "%s", C)!=EOF){
int number = atoi(C);
A_Matrix[A] = number;
A=A+1;
}

for (A = 0; A < sizeof(A_Matrix)/sizeof(A_Matrix[0]); A++){
int Checker1 = A_Matrix[A];
for (B = A+1; B < sizeof(A_Matrix)/sizeof(A_Matrix[0]); B++){
int Checker2 = A_Matrix[B];
if (Checker1 == Checker2){
printf("not-magic");
return 0;
}
}
}


for (A = 0; A < MatrixSquare; A++){
for (B = 0; B < MatrixSquare; B++){
MATRIX[A][B] = A_Matrix[D];
D=D+1;
}
} 
int Checker = 0;
for (A = 0; A < MatrixSquare; A++) {
Checker += MATRIX[0][A];
}


for (A = 0; A < MatrixSquare; A++){
for(B = 0; B < MatrixSquare; B++){
E += MATRIX[A][B];
F += MATRIX[B][A];
if (A == B){
G+= MATRIX[A][B];
}
if (A+B == MatrixSquare-1){
H+= MATRIX[A][B];
}
}
if (F != Checker || E != Checker){
printf("not-magic");
return 0;
}
E = 0;
F = 0;
}	
if (H!= Checker || G!= Checker){
printf("not-magic");
return 0;
}
printf("magic");
return 0;
}



	
