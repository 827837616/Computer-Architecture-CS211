#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

int Array[100];
int size=0;
int i;
FILE *file;

file = fopen(argv[1], "r");
fscanf(file,"%d", &size);

for(i = 0; i < size; i++) {
fscanf(file, "%d", &Array[i]);
}

fclose(file);

//Sorting Begins.

int temp, j, k;
int num1 = 0, num2 = 0;
int Even = 0;
int Arr[size];

for (j = 0; j < size; j++) {
if(Array[j] % 2 == 0)
Even++;
}

num2 = Even;

for (j = 0; j < size; j++) {
for (k = 0; k < (size - j - 1); k++) {
if (Array[k] > Array[k + 1]) {

temp = Array[k];
Array[k] = Array[k + 1];
Array[k + 1] = temp;

}
}
}

for(j = 0; j < size; j++) {
if(Array[j] % 2 == 0) {

Arr[num1] = Array[j];
num1++;
} else {
Arr[num2] = Array[j];
num2++;
}
}

for(j = 0; j < size; j++) {
Array[j] = Arr[j];
}

for(i = 0; i < size; i++) {
printf("%d	", Array[i]);
}

fclose(file);
return 0;
}

