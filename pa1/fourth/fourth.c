#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv) {

if (argc != 2) {
printf("error\n");
return 0;
}

int row1, col1, row2, col2;
int i, j, k, Data = 0;

//Statistical Allocation.
int Matrix1[100][100];
int Matrix2[100][100];
int Answer[100][100];

//Opening a File.
FILE *file; 
file = fopen(argv[1], "r");
  
if(file == NULL) {
    printf("error\n");
    return 0;
  }

//Matrix1.
fscanf(file, "%d %d", &row1, &col1);
for(i = 0; i < row1; i++) {
for(j = 0; j < col1; j++) {
fscanf(file, "%d", &Matrix1[i][j]);
}
fscanf(file, "\n");
}

//Matrix2.
fscanf(file, "%d %d", &row2, &col2);
for(i = 0; i < row2; i++) {
for(j = 0; j < col2; j++) {
fscanf(file, "%d", &Matrix2[i][j]);
}
fscanf(file, "\n");
}

fclose(file);

//Check for Bad Matrices.
if (col1 != row2) {
printf("bad-matrices");
return 0;
} 

//Answer.
for(i = 0; i < row1; i++) {
for(j = 0; j < col2; j++) {
for(k = 0; k < row2; k++){
Data = Data + Matrix1[i][k] * Matrix2[k][j];
}

Answer[i][j] = Data;
Data = 0;
}
}

//Traversing
for(i = 0; i < row1; i++){
for(j = 0; j < col2; j++){
printf ("%d\t", Answer[i][j]);
}
printf("\n");
}

return 0;
}
