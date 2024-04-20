#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hangman.h"
#include <string.h>


int get_word(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}

int is_word_guessed(const char secret[], const char letters_guessed[]) {
    int flag;
    for(int i = 0; i < strlen(secret); i++) {
        flag = 0;
        for(int j = 0; j < strlen(letters_guessed); j++) {
            if(secret[i] == letters_guessed[j]) {
                flag = 1;
                break;
            }
        }
        if(flag == 0) {
            return 0;
        }
    }
    return 1;
}

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]) {
    for(int i = 0; i < strlen(secret); i++) {
        guessed_word[i] = '_';
        for(int j = 0; j < strlen(letters_guessed); j++) {
            if(secret[i] == letters_guessed[j]) {
                guessed_word[i] = secret[i];
            }
        }
    }
}

void get_available_letters(const char letters_guessed[], char available_letters[]) {
    int flag;
    int index = 0;
    char alp[30] = "abcdefghijklmnopqrstuvwxyz";
    for(int i = 0; i < strlen(alp); i++) {
        flag = 0;
        for(int j = 0; j < strlen(letters_guessed); j++) {
            if(alp[i] == letters_guessed[j]) {
                flag = 1;
                break;
            }
        }
        if(flag == 0) {
            available_letters[index] = alp[i];
            index++;
        }
    }
}



void hangman(const char secret[]) {
    int secretLen = strlen(secret);
    int attempts = 8;
    char available_letters[30] = "";
    char letters_quessed[100] = "";
    int letters_guest_index = 0;
    char count_word[100] = "";
    int isflag = 0;
    char garbage[30] = "";
    int garbageindex = 0;
    char guessed_word[30] = "";
    // char garbageletter[30] = "";

    // int chair = 0;
    int numalph = 26;
    // int status = 0;

    // char full_word[30] = "";

    // char tempLetters[30] = "";
    printf("%s\n\n", secret);
    
        printf("Welcome to the game, Hangman!\n");    
        printf("I am thinking of a word that is %d letters long.\n", secretLen);
        printf("-------------\n");
    while(attempts != 0) {
        printf("You have %d guesses left.\n", attempts);
        for(int i = numalph; i > numalph - i; i--) {
            available_letters[i] = '\0';
        }
        get_available_letters(letters_quessed, available_letters);
        printf("Available letters: %s\n", available_letters);
        printf("Please guess a letter: ");
        char temp[30] = "";
        fgets(temp, 30, stdin);

        // garbage[garbageindex] = temp[0];
        // garbageindex++;
        if(strlen(temp) - 1 == 1) {
            //  its a char
            if(temp[0] >= 97 && temp[0] <= 122) {
                letters_quessed[letters_guest_index] = temp[0];
                letters_guest_index++;
            } else if(temp[0] >= 65 && temp[0] <= 90) {
                letters_quessed[letters_guest_index] = temp[0] + 32;
            } else {
                printf("Oops! '%c' is not a valid letter: ", temp[0]);
                get_guessed_word(secret, letters_quessed, guessed_word);
                for(int i = 0; i < strlen(guessed_word); i++) {
                    printf("%c ", guessed_word[i]);
                }
                printf("\n");
            }
        } else if (strlen(temp) - 1 > 1) {
            //  string
            if(strlen(temp) - 1 == secretLen) {
                int issimilar = 1;
                for(int i = 0; i < secretLen; i++) {
                    if(secret[i] != temp[i]) {
                        issimilar = 0;
                        printf("Sorry, bad guess. The word was %s.\n", secret);
                        break;
                    }
                }
                if(issimilar == 1) {
                    printf("Congratulations, you won!\n");
                }                
            } else {
                printf("Sorry, bad guess. The word was %s.\n", secret);
            }
            break;
        }
        
        int flag = 0;
        for(int i = 0; i < secretLen; i++) {
            if(secret[i] == temp[0]) {
                flag = 1;
            }
        }
        if(flag == 1) { //  if match
            letters_quessed[letters_guest_index] = temp[0];
            letters_guest_index++;
            get_guessed_word(secret, letters_quessed, guessed_word);
            printf("Good guess: ");
            for(int i = 0; i < strlen(guessed_word); i++) {
                printf("%c ", guessed_word[i]);
                }
            printf("\n");
            get_available_letters(letters_quessed, available_letters);
        } else {    // if not match
            attempts--;
            get_guessed_word(secret, letters_quessed, count_word);

            if(temp[0] >= 97 && temp[0] <= 122) {
                printf("Oops! That letter is not in my word: ");
                for(int i = 0; i < strlen(guessed_word); i++) {
                    printf("%c ", guessed_word[i]);
                } 
                printf("\n");
            }

            for(int i = 0; i < strlen(garbage); i++) {
                if(garbage[i] == temp[0]) {
                    isflag = 1;
                }
            }
            if(isflag == 1) {
                attempts++;
            }
        }
        garbage[garbageindex] = temp[0];
        garbageindex++;
        flag = 0;
        isflag = 0;
        
        printf("----------\n");

        int guess = is_word_guessed(secret, letters_quessed);
        if(guess != 0) {
            printf("Congratulations, you won!\n");
            break;
        }
        if(attempts == 0) {
            printf("Sorry, you ran out of guesses. The word was %s.\n", secret);
            break;
        }
    }
}
