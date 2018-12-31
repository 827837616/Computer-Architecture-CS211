#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
int i = 0;
int j = i+1;	
char C [1000] = "";	
memset(C, '\0', 1000); //using memset(); to allocate memory..
for (i=0; i < argc; i++) {        
int size = strlen(argv[i]);
C[i] = argv[i][size-1]; 
}
int Fsize = strlen(C);
char * A = calloc(Fsize, sizeof(C));    //calloc allocates the requested memory and returns a pointer to it. Same as malloc with little difference.
for (j=1; j < Fsize; j++) {
A[j-1] = C[j];
}
printf("%s\n", A); 
free(A); //freeing the character.
return 0;
}
