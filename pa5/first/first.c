#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*
GLOBAL VARIABLES
*/
#define MAX 1000

char *lines[MAX];
int numLines = 0;
	
/*
Dynamic arrays for input and output variables
We will create them dynamically as per the count mentioned
in circuit file
*/
int *inputVars;
int *outputVars;

/*
Array to store temporary variables.
Note that it is array of pointers, we will dynamically
create whatever number of tempVars we need
*/
int *tempVars[MAX];

// to Count number of input and output variables
int numInputVars, numOutputVars;



/*
Helper Methods for Main
*/

//Converting Argument from character to integer.
unsigned long long ChartoInt (char* A) {

unsigned long long X = 1;
unsigned long long Y = 0;
int Size = strlen(A);
//for(int m = Size; m>=0, m++);
for(int m = Size -1 ; m >= 0 ; m=m-1) {
Y = Y + ((int)A[m] - 48)* X;
unsigned long long C = X * 10;
X = C;
}
return Y;
}

char *myStrDup(const char *s) {
size_t size = strlen(s) + 1;
char *p = malloc(size);
if (p != NULL) {
memcpy(p, s, size);
}
return p;
}

/*
This method parses an identifier like IN1, IN2, OUT1, temp1 etc..
and return their index on basis 0.
like 1 for temp2
*/
int getIndexFromIdentifier(char *str) {
int i=0;
while(!isdigit(str[i])) {
i++;
}
// index is based on 0
return ChartoInt(str+i) - 1;
}

// method to check if a string starts with other string
int startsWith(char *str, char *search) {
return (strstr(str, search) == str);
}

// Check if the variable has already been created
int isVariableDefined(char *var) {
// both IN and OUT variables are already defined.
if(startsWith(var, "OUT") || startsWith(var, "IN")) {
return 1;
}

// If it is a temporary variable, it may need to be created
if(startsWith(var, "temp")) {
// variable is of temp type.
int index = getIndexFromIdentifier(var);
return (tempVars[index] != NULL);
} else {
// variable is constant bit 1 or 0
return 1;
}	
}

// convert decimal number to gray code 
int decimalToGrey(int n) {
return n ^ (n >> 1); 
} 

// convert gray code to decimal number 
int greyToDecimal(int n) { 
int inv = 0; 
// Taking xor until n becomes zero 
for (; n; n = n >> 1) 
inv ^= n; 
return inv; 
} 

// helper method to see the sorte lines.. not necessary in this program
void printLines() {
int i;
for(i=0; i<numLines; i++) {
printf("%s\n", lines[i]);		
}	
}

/*
This method takes an identifier string and returns its value
If string is like temp1 => it means we read value from temp variables on index 0
If string is a bit like 1 or 0, we directly return its value.
 */
int readIdentifierValue(char *identifier) {
if(startsWith(identifier, "temp")) {
return *tempVars[getIndexFromIdentifier(identifier)];
} else if(startsWith(identifier, "IN")) {
return inputVars[getIndexFromIdentifier(identifier)];
} else if(startsWith(identifier, "OUT")) {
return outputVars[getIndexFromIdentifier(identifier)];
} else {
// input is a 1 or 0 bit
return ChartoInt(identifier);
}
}

/*
Similar to above method, based on identifier type, this method
writes the value to memory location.
*/
void writeIdentifierValue(char *identifier, int value) {
if(startsWith(identifier, "temp")) {
*tempVars[getIndexFromIdentifier(identifier)] = value;
} else if(startsWith(identifier, "IN")) {
inputVars[getIndexFromIdentifier(identifier)] = value;
} else if(startsWith(identifier, "OUT")) {
outputVars[getIndexFromIdentifier(identifier)] = value;
}
}

/*
This function decodes the input array, and based on index
returns the value. Index 0 means A'B'. Index 1 means A'B and 
so on.
 */
int decode(int *inputs, int size, int index) {

// index is binary till now, chane that to grey code
index = decimalToGrey(index);
int result = 1;
int current = size - 1;
do {
int bit = index % 2;
index = index/2;
if(bit == 0) {
result = result && (!inputs[current]);
} else {
result = result && inputs[current];
}
current--;
} while(current >= 0);
return result;
}


// this method deletes a line from line array
void deleteLine(int x) {

char *s = lines[x];
lines[x] = lines[--numLines];
free(s);
}

// this method swaps the lines in the line array
void swapLines(int x, int y) {
	
char *s = lines[x];
lines[x] = lines[y];
lines[y] = s;
}

/*
This method checks to see if the line can be processed keeping in mind the 
required input variables. If input variables are not yet created, then this
line can not be processed yet.
Like => AND temp1 temp2 OUT1
If temp1 or temp2 is still not created then this method returns 0.
*/
int canLineBeProcessed(char *str) {

// create a duplicate string, because strtok distorts the original string
char *l = myStrDup(str);
	
// if this is a NOT statement line
if(startsWith(l, "NOT")) {
strtok(l, " ");
char *var1 = strtok(NULL, " ");
char *var2 = strtok(NULL, " ");
		
// var1 should be defined
if(isVariableDefined(var1)) {
if(!isVariableDefined(var2)) {
// if temp output is not defined
tempVars[getIndexFromIdentifier(var2)] = calloc(1, sizeof(int));
*tempVars[getIndexFromIdentifier(var2)] = 0;
}
free(l);
return 1;
}
}
	
// if this is a AND, NAND, OR, NOR, XOR statement line
else if(startsWith(l, "AND") || startsWith(l, "OR") || startsWith(l, "NAND") || startsWith(l, "NOR") || startsWith(l, "XOR")) {
strtok(l, " ");
char *var1 = strtok(NULL, " ");
char *var2 = strtok(NULL, " ");
char *var3 = strtok(NULL, " ");
		
// var1 should be defined
if(isVariableDefined(var1) && isVariableDefined(var2)) {
if(!isVariableDefined(var3)) {
// if temp output is not defined
tempVars[getIndexFromIdentifier(var3)] = calloc(1, sizeof(int));
*tempVars[getIndexFromIdentifier(var3)] = 0;
}
free(l);
return 1;
}
}
	
// if this is a DECODER statement line
else if(startsWith(l, "DECODER")) {
strtok(l, " ");
char *count = strtok(NULL, " ");
		
int inputDefined = 1;
int i;
for(i=0; i<ChartoInt(count); i++) {
char *inputVar = strtok(NULL, " ");
inputDefined = inputDefined && isVariableDefined(inputVar);
}
	
// If all the input variables are defined, then check to see if output
// variables are defined. If not defined, created them
if(inputDefined) {
for(i=0; i<pow(2, ChartoInt(count)); i++) {
char *outputVar = strtok(NULL, " ");
if(!isVariableDefined(outputVar)) {
tempVars[getIndexFromIdentifier(outputVar)] = calloc(1, sizeof(int));
*tempVars[getIndexFromIdentifier(outputVar)] = 0;
}
}
free(l);
return 1;
}
}
	
// if this is a MUX statement line
else if(startsWith(l, "MULTIPLEXER")) {
strtok(l, " ");
char *count = strtok(NULL, " ");
int inputDefined = 1;
int i;
		
// ignore n input bits
for(i=0; i<ChartoInt(count); i++) {
char *inputVar = strtok(NULL, " ");
inputDefined = inputDefined && isVariableDefined(inputVar);
}
for(i=0; i<log2(ChartoInt(count)); i++) {
char *inputVar = strtok(NULL, " ");
inputDefined = inputDefined && isVariableDefined(inputVar);
}
		
// If all the input variables are defined, then check to see if output
// variables is defined. If not defined, created that.
if(inputDefined) {
				
char *outputVar = strtok(NULL, " ");
if(!isVariableDefined(outputVar)) {
// if temp output is not defined
tempVars[getIndexFromIdentifier(outputVar)] = calloc(1, sizeof(int));
*tempVars[getIndexFromIdentifier(outputVar)] = 0;
}
free(l);
return 1;
}
}
free(l);
return 0;
}



/*
This method checks the lines read from file and creates the required 
number of input variables dynamically.
it also deletes this line from lines array.
*/
void processInputIdentifiersLine() {

int i;
for(i=0; i<numLines; i++) {
		
// this line starts with input variables
if(startsWith(lines[i], "INPUTVAR")) {
strtok(lines[i], " ");
char *count = strtok(NULL, " ");
numInputVars = ChartoInt(count);
inputVars = calloc(numInputVars, sizeof(int));
deleteLine(i);
return;
}	
}	
}

/*
This method checks the lines read from file and creates the required 
number of output variables dynamically.
it also deletes this line from lines array.
*/
void processOutputIdentifiersLine() {

int i;
for(i=0; i<numLines; i++) {
		
// this line starts with output variables
if(startsWith(lines[i], "OUTPUTVAR")) {
strtok(lines[i], " ");
char *count = strtok(NULL, " ");
			
numOutputVars = ChartoInt(count);
outputVars = calloc(numOutputVars, sizeof(int));
deleteLine(i);
return;
}	
}	
}


/*
this method takes a line as the input and processes it using the 
existing inputVars and tempVars.. it writes the output values to the 
resultant variables.
*/
void processInputFileLine(char *line) {
	
// create a duplicate string, because strtok distorts the string
char *l = myStrDup(line);
if(startsWith(l, "NOT")) {
strtok(l, " ");
char *var1 = strtok(NULL, " ");
char *var2 = strtok(NULL, " ");
int value = readIdentifierValue(var1);
writeIdentifierValue(var2, !value);
} 
	
else if(startsWith(l, "AND") || startsWith(l, "OR") || startsWith(l, "NAND") || startsWith(l, "NOR") || startsWith(l, "XOR")) {
char *cmd = strtok(l, " ");
char *var1 = strtok(NULL, " ");
char *var2 = strtok(NULL, " ");
char *var3 = strtok(NULL, " ");
		
int val1 = readIdentifierValue(var1);
int val2 = readIdentifierValue(var2);
		
if(strcmp(cmd, "AND") == 0) {
writeIdentifierValue(var3, val1 && val2);
} else if(strcmp(cmd, "NAND") == 0) {
writeIdentifierValue(var3, !(val1 && val2));
} else if(strcmp(cmd, "OR") == 0) {
writeIdentifierValue(var3, val1 || val2);
} else if(strcmp(cmd, "NOR") == 0) {
writeIdentifierValue(var3, !(val1 || val2));
} else if(strcmp(cmd, "XOR") == 0) {
writeIdentifierValue(var3, (!val1 && val2) || (!val2 && val1));
}
}
	
else if(startsWith(l, "DECODER")) {
strtok(l, " ");
char *count = strtok(NULL, " ");
		
int size = ChartoInt(count);
int inputs[size];		
int i;
for(i=0; i<size; i++) {
char *inputVar = strtok(NULL, " ");
inputs[i] = readIdentifierValue(inputVar);
}		
		
for(i=0; i<pow(2, size); i++) {
char *outputVar = strtok(NULL, " ");
writeIdentifierValue(outputVar, decode(inputs, size, i));
}
}
else if(startsWith(l, "MULTIPLEXER")) {
strtok(l, " ");
char *count = strtok(NULL, " ");
		
int size = ChartoInt(count);
int inputs[size];		
int i;
for(i=0; i<size; i++) {
char *inputVar = strtok(NULL, " ");
inputs[i] = readIdentifierValue(inputVar);
}
int control = 0;
for(i=0; i<log2(size); i++) {
char *inputVar = strtok(NULL, " ");
control = 2*control + readIdentifierValue(inputVar);
}
		
control = greyToDecimal(control);
char *outputVar = strtok(NULL, " ");
writeIdentifierValue(outputVar, inputs[control]);
}
free(l);
}

/*
This method basically sorts the line read from input file,
so that the lines can be processed one by one in order and 
they create the required input and output variables.
*/
void rearrangeLines() {

int linesProcessed = 0, i;
while(linesProcessed != numLines) {
		
// At any time, in the line array, linesProcessed is the number of lines
// for which order has already been determined.
for(i=linesProcessed; i<numLines; i++) {
if(canLineBeProcessed(lines[i])) {		
// if this line can be processed, move it to sorted segment
swapLines(i, linesProcessed);
linesProcessed++;
break;
}			
}
}	
}

/*
PUBLIC METHODS
*/


/*
This method reads the circuit file and then one by one create a lines array
It also, generates the required input, output and temp identifiers.
*/
void readFile(char *fileName) {

FILE * fp;
fp = fopen(fileName, "r");
if (fp == NULL) {
printf("unable to open the input file\n");
exit(EXIT_FAILURE);
}
	
char line[1000];
while (fgets(line, 1000, fp) != NULL) {
lines[numLines] = myStrDup(line);
int l = strlen(lines[numLines]);
if(lines[numLines][l-1] == '\n') {
lines[numLines][l-1] = '\0';
}
numLines++;
}
fclose(fp);
	
// Process input and output lines and rearrange other lines
// so that they are sorted to be processed.
	
// Create necessary input and output variables
processInputIdentifiersLine();
processOutputIdentifiersLine();
	
// rearrange remaining lines
rearrangeLines();
}

/*
This method frees the memory which has been allocated in the code.
*/
void cleanMemory() {
free(inputVars);
free(outputVars);
	
int i;
for(i=0; i<numLines; i++) {
free(lines[i]);
}
for(i=0; i<MAX; i++) {
if(tempVars[i] != NULL) {
free(tempVars[i]);
}
}
}

/*
This method assumes that the inputVars have already been filled 
with 0s and 1s combination... this method will process data from
input to temp and outputVars, then this method prints the value
of input and output variables on screen.
*/
void processCurrentCombination() {
	
int j;
for(j=0; j<numLines; j++) {
processInputFileLine(lines[j]);		
}
for(j=0; j<numInputVars; j++) {
printf("%d ", inputVars[j]);
}
for(j=0; j<numOutputVars; j++) {
printf("%d ", outputVars[j]);
}
printf("\n");
}

/*
This method puts various combinations of 0s and 1s into the input
variables and then call to processes one combination at a time.
*/
void createVariousInputCombinations() {
	
int processed = 0;
	
// start processing first combination
processCurrentCombination();
processed++;
	
do {
// in gray code, 
// which bit to change.. depends upon the current processed index.
// find the rightmost 1 index in the number and flip it.
unsigned int index = numInputVars - 1;
int x = processed;
while(x != 0) {
if(x % 2 == 1) {
break;
}
x = x/2;
index--;
}
		
inputVars[index] = !inputVars[index];
processCurrentCombination();
processed++;
			
} while(processed != pow(2, numInputVars));
}


/*
Main method to start execution.
*/

int main(int argc, char *argv[]) {
	
// check for error condition
if(argc != 2) {
printf("The program must be run by one parameter only.\n");
printf("Usage: ./first <filename>\n");
return EXIT_FAILURE; 
}
// read circuit file lines and sort them
readFile(argv[1]);
// Create truth table and print output
createVariousInputCombinations();
// free allocated memory
cleanMemory();
exit(EXIT_SUCCESS);
}

