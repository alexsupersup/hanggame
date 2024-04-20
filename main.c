#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hangman.h"

int main() {
    srand(time(NULL));

    char secret[100];

    int result = get_word(secret);
    if(result != 0) {
        printf("Error\n");
        return 1;
    }

    // printf("%s\n", secret);


    // // 1
    
    // printf("%d\n", is_word_guessed("secret", "aeiou"));
    // // prints: 0
    // printf("%d\n", is_word_guessed("hello", "aeihoul"));
    // // prints: 1


    // // 2

    // char test[30];

    // get_guessed_word("container", "arpstxgoieyu", test);
    // // result = "_o_tai_er"
    // printf("%s\n", test);


    // // 3

    // char testLetters[30];
    // get_available_letters("arpstxgoieyu", testLetters);
    // // result = "bcdfhjklmnqvwz"
    // printf("%s\n", testLetters);

    // printf("\n\n\n");
    // // 4

    hangman(secret);


    return 0;
}