#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hangman.h"
#include <time.h>

/*
printf("%d\n", is_word_guessed("secret", "aeiou"));
    prints: 0
printf("%d\n", is_word_guessed("hello", "aeihoul"));
    prints: 1
*/


int main() {
    srand(time(NULL));
    char secret[150];
    int result = get_word(secret);

    if(result != 0) {
        printf("Error\n");
        return 1;
    }

    // printf("%s\n", secret);
    
    printf("%d\n", is_word_guessed("hello", "aeihoul"));
    // prints: 1
    printf("%d\n", is_word_guessed("secret", "aeiou"));
    // prints: 0


    char result2[30];
    get_guessed_word("container", "arpstxgoieyu", result2);
    printf("%s\n", result2);
    // result = "_o_tai_er"
    

    return 0;
}
