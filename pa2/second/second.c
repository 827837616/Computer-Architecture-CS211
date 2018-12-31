#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// we are taking a 2-D integer array as our Sudoku SudokuGrid.

int SudokuGrid[9][9];

int StartingColumn(int c) {
return c - (c%3);
}
int StartingRow(int r) {
return r - (r%3);
}

//Reading given sudoku to make it ready to solve.
void FillingGrid(FILE *f) {
for(int i=0; i<9; i++) {
for(int j=0; j<9; j++) {
fflush(stdout);
char c;
fscanf(f, "%c ", &c);
if(c == '-') {
SudokuGrid[i][j] = 0;
} else {
SudokuGrid[i][j] = c - '0';
}
}
}
}

//Printing Read Sudoku.
void PrintingGrid() {
for(int i=0; i<9; i++) {
for(int j=0; j<9; j++) {
if(SudokuGrid[i][j] == 0) {
printf("-");
} else {
printf("%d", SudokuGrid[i][j]);
}
if(j != 8) {
printf("\t");
}
}
if(i != 8) {
printf("\n");
}
}
}

//Finding Particular Value in Column.
int Check2(int c, int Value) {
for(int i=0; i < 9; i++) {
if(SudokuGrid[i][c] == Value) {
return 1;
}
}
return 0;
}

//Finding Particular Value in Row.
int Check1(int r, int Value) {
for(int i=0; i < 9; i++) {
if(SudokuGrid[r][i] == Value) {
return 1;
}
}
return 0;
}

//Finding Particular Value in 3by3 SubGrid..
int Check3(int r, int c, int Value) {
r = StartingRow(r);
c = StartingColumn(c);
for(int i=r; i < r+3; i++) {
for(int j=c; j < c+3; j++) {
if(SudokuGrid[i][j] == Value) {
return 1;
}
}
}
return 0;
}

//Check to Remaning Spaces to fill.
int CheckSolve() {
for(int i=0; i<9; i++) {
for(int j=0; j<9; j++) {
if(SudokuGrid[i][j] == 0) {
return 0;
}
}
}
return 1;
}

//Value Filling.
int CheckInsert(int r, int c, int value) {
if(Check1(r, value)) {
return 0;
}
if(Check2(c, value)) {
return 0;
}
if(Check3(r, c, value)) {
return 0;
}
return 1;
}

//Checking and Filling values recursively.
void FillingSudoku(int TempValue) {
for(int i=0; i<9; i++) {
for(int j=0; j<9; j++) {
if(SudokuGrid[i][j] == 0) {
int expectedValue = -1;
for(int value = 1; value <= 9; value++) {
if(!CheckInsert(i, j, value)) {
continue;
}
if(expectedValue == -1) {
expectedValue = value;					
} else {
expectedValue = -1;
break;
}
}
if(expectedValue != -1) {
SudokuGrid[i][j] = expectedValue;					
FillingSudoku(TempValue);	
if((!CheckSolve()) && TempValue) {
SudokuGrid[i][j] = 0;
}
return;
}
}
}
}
if(!TempValue && !CheckSolve()) {
for(int i=0; i<9; i++) {
for(int j=0; j<9; j++) {
if(SudokuGrid[i][j] == 0) {
for(int value = 1; value <= 9; value++) {
if(CheckInsert(i, j, value)) {
SudokuGrid[i][j] = value;
FillingSudoku(1);
if(CheckSolve()) {
return;
} else {
SudokuGrid[i][j] = 0;
}
}
}
}
}
}
}
}

//Checking that same value is not present.
int BackTracking(int r, int c) {
if(SudokuGrid[r][c] == 0) {
return 1;
}
int startRow = StartingRow(r);
int startCol = StartingColumn(c);
for(int i=startRow; i < startRow + 3; i++) {
for(int j=startCol; j<startCol + 3; j++) {
if(i != r && j != c) {
if(SudokuGrid[r][c] != 0 && SudokuGrid[r][c] == SudokuGrid[i][j]) {
return 0;
}
}
}
}
for(int i=0; i < 9; i++) {
if(i != c) {
if(SudokuGrid[r][i] != 0 && SudokuGrid[r][i] == SudokuGrid[r][c]) {
return 0;
}
}
}
for(int i=0; i < 9; i++) {
if(i != r) {
if(SudokuGrid[i][c] != 0 && SudokuGrid[i][c] == SudokuGrid[r][c]) {
return 0;
}
}
}
return 1;
}

//Exit program if same value is found.
int FinalCheck() {
for(int i=0; i<9; i++) {
for(int j=0; j<9; j++) {
if(!BackTracking(i, j)) {
return 0;
}
}
}
return 1;
}

//Main Method.
int main(int argc, char *argv[]) {
if(argc != 2) {
printf("Usage: ./second <filename>\n");
return 1;
}
FILE *file = fopen(argv[1], "r");
if(!file) {
printf("Error opening input file\n");
return 1;
}
FillingGrid(file);
if(!FinalCheck()) {
printf("no-solution");
return 0;
}
FillingSudoku(0);
if(CheckSolve()) {
PrintingGrid();
} else {
PrintingGrid();
printf("no-solution");
}
return 0;
}

