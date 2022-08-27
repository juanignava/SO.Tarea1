#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
/**
 * @brief This method reads a txt file and counts the number of consonants that it contains
 * 
 * @return int consonants_count: this is the number of consonants that the file contains
 */
int counter(char file_name[]){

    FILE* ptr;
    char ch;
    int consonants_count = 0;

    // Stores the content of the file.
    ptr = fopen("test1.txt", "r");
 
    if (NULL == ptr) {
        printf("file can't be opened \n");
    }
 
    printf("Inicia conteo de consonantes... \n");
 
    while (!feof(ptr)) {

        // Reads file content char by char
        ch = fgetc(ptr);

        // Converts character to lowercase
        ch = tolower(ch);

        // Checks if the character is a vowel (we need to check this first so the next)
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            printf("%c is a vowel. \n", ch);
        }

        // Checks if the char is a consonant
        else if ((ch >= 'a' && ch <= 'z')) {
            ++ consonants_count;
            printf("%c is a consonant. Incrementing counter...\n", ch);
        }

        // 
        else
            printf("%c is not an alpha character. \n", ch);
    }

    printf("La cantidad de consonantes es: %d\n", consonants_count);
    
    fclose(ptr);
    return consonants_count;

}

int main()
{
    int consonant_count = counter("test1");
    
}