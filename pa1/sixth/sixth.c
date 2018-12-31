#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char **argv) {

char word[100];
int i;
int j;
int k;
char c[1000];
FILE *fptr;

fptr = fopen(argv[1], "r");

for(k=0; k<strlen(word); k++) {
fscanf(fptr,"%s\0", c);
}
fclose(fptr);

//Take each word sepaerated by delimitter
char *token = strtok(c, " ");
  

while (token != NULL) {
       //Copy each token or word into word array
       strcpy(word, token);
       //Check the first letter vowel or not
       //If alphabet print the word and then print yay at the end
       if (word[0] == 'a' || word[0] == 'A' || word[0] == 'e' || word[0] == 'E' || word[0] == 'i' || word[0] == 'I' || word[0] == 'o' || word[0] == 'O' || word[0] == 'u' || word[0] == 'U') {
           for (i = 0; i < strlen(word); i++) {
               printf("%c", word[i]);
           }
           printf("%c", 'y');
           printf("%c", 'a');
           printf("%c ", 'y');
       }
       //Not vowel
       else {
           for (i = 1; i < strlen(word); i++) {
               //Find until vowel the print
               if (word[i] == 'a' || word[i] == 'A' || word[i] == 'e' || word[i] == 'E' || word[i] == 'i' || word[i] == 'I' || word[i] == 'o' || word[i] == 'O' || word[i] == 'u' || word[i] == 'U') {
                  
                   for (j = i; j < strlen(word); j++) {
                       printf("%c", word[j]);
                   }
               }
               //After that print from start
               for (j = 0; j < i; j++) {
                   printf("%c", word[j]);
               }
               //Then add "ay" at the end
               printf("%c", 'a');
               printf("%c ", 'y');
               break;
           }
       }
       //Take each word
       token = strtok(NULL, " ");
   }
   //End of the program
   printf("%s", "\n");
    return 0;
}

