#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
This is the program to predict house price in the area.
*/

//Transpose 
double** MatrixTranspose(double**MatrixA,int Rows,int Columns);
double** MatrixTranspose(double**MatrixA,int Rows,int Columns) {
int i;
int j;
double** Answer=(double**)malloc(Columns*sizeof(double*));
for(i=0;i<Columns;i++) {
Answer[i]=(double*)malloc(Rows*sizeof(double));
}
for(i=0;i<Columns;i++) {
for(j=0;j<Rows;j++) {
Answer[i][j]=MatrixA[j][i];
}
}
return Answer;
}

double** RREF1(double** Temp, int i, int j, int Rows,int Columns);
double** RREF2(double** Temp, int i, int j, int Rows, int Columns);
double** RREF3(double** Temp, int i, int j, int Rows, int Columns);
double** RREF4(double** matrix1, double** matrix2, int R1, int R2, int C1, int C2);

//Inverse
double** MatrixInverse(double ** MatrixA, int Rows, int Columns);
double** MatrixInverse(double ** MatrixA, int Rows, int Columns) {
int i;
int j;
int AA;
double** Answer=(double**)malloc(Rows*sizeof(double*));
for(i=0;i<Rows;i++) {
Answer[i]=(double*)malloc((Columns*2)*sizeof(double));
}
for(i=0;i<Rows;i++) {
for(j=0;j<Columns;j++) {
Answer[i][j]=MatrixA[i][j];
}
}
for(i=0;i<Rows;i++) {
for(j=Columns;j<(Columns*2);j++) {
if(j-Columns==i) {
Answer[i][j]=1;
} else  {
Answer[i][j]=0;
}
}
}
for(i=0;i<Rows;i++) {
for(j=0;j<Columns;j++) {
if(i==j) {
Answer=RREF1(Answer,i,j,Rows,Columns*2);
for(AA=i+1;AA<Rows;AA++) {
Answer=RREF2(Answer,AA,j,Rows,Columns*2);
}
}
}
}
for(i=Rows-1;i>=0;i--) {
for(j=Columns-1;j>=0;j--) {
if(i!=j&&Answer[i][j]!=0) {
Answer=RREF3(Answer,i,j,Rows,Columns*2);
}
}
}
double** LastAnswer=(double**)malloc(Rows*sizeof(double*));
for(i=0;i<Rows;i++) {
LastAnswer[i]=(double*)malloc((Columns)*sizeof(double));
}
for(i=0;i<Rows;i++) {
for(j=0;j<Columns;j++) {
LastAnswer[i][j]=Answer[i][j+Columns];
}
}
return LastAnswer;
}

//Helper
double** Change(double** TestFile, double** H,int Rows,int Columns);
double** Change(double** TestFile, double** H,int Rows,int Columns) {
int x;
int y;
double N=0;
double** LastAnswer=(double**)malloc(Rows*sizeof(double*));
for(x=0;x<Rows;x++) {
LastAnswer[x]=(double*)malloc(1*sizeof(double));
}
for(x=0;x<Rows;x++) {
N=H[0][0];
for(y=0;y<Columns;y++) {
N=N+(TestFile[x][y]*H[y+1][0]);
}
LastAnswer[x][0]=N;
printf("%0.0lf\n", LastAnswer[x][0]);
}
return LastAnswer;
}

//Output1
void Print1(double* MatrixA,int rownum) {
int i;
for(i=0;i<rownum;i++) {
printf("%lf\t",MatrixA[i]);
}
printf("\n");
}

//Output2
void Print2(double** MatrixA,int rownum,int comnum);
void Print2(double** MatrixA,int rownum,int comnum) {
int i; 
int j;
for(i=0;i<rownum;i++) {
for(j=0;j<comnum;j++) {
printf("%lf\t",MatrixA[i][j]);
}
printf("\n");
}
}

//Gaussian Elimination Step 1
double** RREF1(double** Temp, int i, int j, int Rows, int Columns) {
double** MatrixA=(double**)malloc(Rows*sizeof(double*));
int x;
int y;
for(x=0;x<Rows;x++) {
MatrixA[x]=(double*)malloc((Columns)*sizeof(double));
}
for(x=0;x<Rows;x++) {
for(y=0;y<Columns;y++) {
MatrixA[x][y]=Temp[x][y];
}
}
double Value;
int AA,AAA;
if(MatrixA[i][j]==1) {
return MatrixA;
} else if(MatrixA[i][j]==0) {
for(AA=1;AA<Rows;AA++) {
if(MatrixA[AA][j]!=0) {
for(AAA=0;AAA<Columns;AAA++) {
MatrixA[i][AAA]=MatrixA[i][AAA]+MatrixA[AA][AAA];
}
return MatrixA;
}
}
printf("error");
return MatrixA;
} else  {
Value=MatrixA[i][j];
for(AA=0;AA<Columns;AA++) {
MatrixA[i][AA]=MatrixA[i][AA]/Value;
}
return MatrixA;
}
printf("error");
return MatrixA;
}

//Gaussian Elimination Step 2
double** RREF2(double** Temp, int i, int j,int Rows,int Columns) {
if(Temp[i][j]==0) {
return Temp;
}
double** MatrixA=(double**)malloc(Rows*sizeof(double*));
int x;
int y;
for(x=0;x<Rows;x++) {
MatrixA[x]=(double*)malloc((Columns)*sizeof(double));
}
for(x=0;x<Rows;x++) {
for(y=0;y<Columns;y++) {
MatrixA[x][y]=Temp[x][y];
}
}
double Value=MatrixA[i][j];
for(y=0;y<Columns;y++) {
MatrixA[i][y]=MatrixA[i][y]/Value;
}
int AA;
for(AA=0;AA<Columns;AA++) {
MatrixA[i][AA]=MatrixA[i][AA]-MatrixA[j][AA];
}
return MatrixA;
}

//Gaussian Elimination Step 3
double** RREF3(double** Temp, int i, int j,int Rows,int Columns) {
if(Temp[i][j]==0) {
return Temp;
}
double** MatrixA=(double**)malloc(Rows*sizeof(double*));
int x;
int y;
for(x=0;x<Rows;x++) {
MatrixA[x]=(double*)malloc((Columns)*sizeof(double));
}
for(x=0;x<Rows;x++) {
for(y=0;y<Columns;y++) {
MatrixA[x][y]=Temp[x][y];
}
}
double Value=MatrixA[i][j];
int AA;
for(AA=0;AA<Columns;AA++) {
MatrixA[i][AA]=MatrixA[i][AA]-(MatrixA[j][AA]*Value);
}
return MatrixA;
}

//Gaussian Elimination Step 4
double** RREF4(double** matrix1, double** matrix2,int R1,int R2,int C1, int C2) {
double** Answer=(double**)malloc(R1*sizeof(double*));
int x;
int i;
int j;
int AA;
double N=0;
for(x=0;x<R1;x++) {
Answer[x]=(double*)malloc((C2)*sizeof(double));
}
for(i=0; i<R1;i++) {
for(j=0; j<C2;j++) {
for(AA=0; AA<R2;AA++) {
N=N+matrix1[i][AA]*matrix2[AA][j];
}
Answer[i][j]=N;
N=0;
}
}
return Answer;
}

//Output for final price.
double** AnswerSolver(double** MatrixA,double ** Y,int Rows, int Columns);
double** AnswerSolver(double** MatrixA,double ** Y,int Rows, int Columns) {
int x;
double** V=(double**)malloc(Columns*sizeof(double*));
for(x=0;x<Columns;x++) {
V[x]=(double*)malloc((Rows)*sizeof(double));
}
double** InverseA=(double**)malloc(Columns*sizeof(double*));
for(x=0;x<Columns;x++) {
InverseA[x]=(double*)malloc((Columns)*sizeof(double));
}
double** VV=(double**)malloc(Columns*sizeof(double*));
for(x=0;x<Columns;x++) {
VV[x]=(double*)malloc((Columns)*sizeof(double));
}
double** AnswerA=(double**)malloc(Columns*sizeof(double*));
for(x=0;x<Columns;x++) {
AnswerA[x]=(double*)malloc(Rows*sizeof(double));
 }
double** AnswerF=(double**)malloc(Columns*sizeof(double*));
for(x=0;x<Columns;x++) {
AnswerF[x]=(double*)malloc(1*sizeof(double));
}
V=MatrixTranspose(MatrixA,Rows,Columns);
VV=RREF4(V,MatrixA,Columns,Rows,Rows,Columns);
InverseA=MatrixInverse(VV,Columns,Columns);
AnswerA=RREF4(InverseA,V,Columns,Columns,Columns,Rows);
AnswerF=RREF4(AnswerA,Y,Columns,Rows,Rows,1);
return AnswerF;
}

//Main Method.
int main(int argc, char** argv) {
FILE* TrainingFile;
FILE* TestFile;
TrainingFile=fopen(argv[1],"r");
TestFile=fopen(argv[2],"r");
int x;
int i;
int j;
int A;
int B; 
int C;
fscanf(TrainingFile,"%d\n",&A);
fscanf(TrainingFile,"%d\n",&B);
fscanf(TestFile,"%d\n",&C);
double** MatrixT=(double**)malloc(B*sizeof(double*));
for(i=0;i<B;i++) {
MatrixT[i]=(double*)malloc((A+1)*sizeof(double));
}
double** TestMatrix=(double**)malloc(C*sizeof(double*));
for(i=0;i<C;i++) {
TestMatrix[i]=(double*)malloc((A)*sizeof(double));
}
double** Y=(double**)malloc(B*sizeof(double*));
for(i=0;i<B;i++) {
Y[i]=(double*)malloc(1*sizeof(double));
}
double** LastAnswer=(double**)malloc((A+1)*sizeof(double*));
for(x=0;x<=A;x++) {
LastAnswer[x]=(double*)malloc(1*sizeof(double));
}
double** AnswerF=(double**)malloc(C*sizeof(double*));
for(x=0;x<C;x++) {
AnswerF[x]=(double*)malloc(1*sizeof(double));
}
for(i=0;i<B;i++) {
for(j=1;j<=A;j++) {
fscanf(TrainingFile,"%lf%*[,]",&MatrixT[i][j]);
}
fscanf(TrainingFile,"%lf",&Y[i][0]);
fscanf(TrainingFile,"\n");
}
for(i=0;i<B;i++) {
MatrixT[i][0]=1;
}
for(i=0;i<C;i++) {
for(j=0;j<A;j++) {
fscanf(TestFile,"%lf%*[,]",&TestMatrix[i][j]);
}
fscanf(TestFile,"\n");
}
LastAnswer=AnswerSolver(MatrixT,Y,B,A+1);
AnswerF=Change(TestMatrix,LastAnswer,C,A);
free(AnswerF);
free(Y);
free(MatrixT);
free(TestMatrix);
free(LastAnswer);
return 0;
}


