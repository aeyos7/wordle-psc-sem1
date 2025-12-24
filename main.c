#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_ATTEMPTS 6
#define WORD_LENGTH 5

// ANSI Color Codes
#define COLOR_GREEN  "\033[0;32m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_RESET  "\033[0m"

void to_uppercase(char str[]) {
    for (int i = 0; str[i]; i++) str[i] = toupper(str[i]);
}

int main() {
    char words[50][6] = {
        "APPLE", "BEACH", "BRAIN", "BREAD", "BRUSH", "CHAIR", "CHEST", "CHORD", "CLICK", "CLOCK",
        "CLOUD", "DANCE", "DIARY", "DRINK", "DRIVE", "EARTH", "FEAST", "FIELD", "FRUIT", "GLASS",
        "GRAPE", "GREEN", "GHOST", "HEART", "HOUSE", "JUICE", "LIGHT", "LEMON", "MELON", "MONEY",
        "MUSIC", "NIGHT", "OCEAN", "PARTY", "PIANO", "PILOT", "PLANE", "PHONE", "PIZZA", "PLANT",
        "RADIO", "RIVER", "ROBOT", "SHIRT", "SHOES", "SMILE", "SNAKE", "SPACE", "SPOON", "STORM"
    };

    srand(time(NULL));
    char *targetWord = words[rand() % 50];
    char guess[10];
    int attempts = 0;
    int won = 0;

    printf("--- Welcome to " COLOR_GREEN "C-WORDLE" COLOR_RESET " ---\n");

    while (attempts < MAX_ATTEMPTS) {
        printf("\nAttempt %d/%d. Enter guess: ", attempts + 1, MAX_ATTEMPTS);
        scanf("%s", guess);
        to_uppercase(guess);

        if (strlen(guess) != WORD_LENGTH) {
            printf("Please enter a 5-letter word.\n");
            continue;
        }

        int targetUsed[5] = {0, 0, 0, 0, 0};
        int guessStatus[5] = {0, 0, 0, 0, 0}; // 2 = Green, 1 = Yellow, 0 = Gray

        // First Pass: Check for Greens (Correct spot)
        for (int i = 0; i < WORD_LENGTH; i++) {
            if (guess[i] == targetWord[i]) {
                guessStatus[i] = 2;
                targetUsed[i] = 1;
            }
        }

        // Second Pass: Check for Yellows (Wrong spot)
        for (int i = 0; i < WORD_LENGTH; i++) {
            if (guessStatus[i] == 0) { // If not already green
                for (int j = 0; j < WORD_LENGTH; j++) {
                    if (!targetUsed[j] && guess[i] == targetWord[j]) {
                        guessStatus[i] = 1;
                        targetUsed[j] = 1;
                        break;
                    }
                }
            }
        }

        // Print colored output
        printf("Result: ");
        for (int i = 0; i < WORD_LENGTH; i++) {
            if (guessStatus[i] == 2) {
                printf(COLOR_GREEN "%c " COLOR_RESET, guess[i]);
            } else if (guessStatus[i] == 1) {
                printf(COLOR_YELLOW "%c " COLOR_RESET, guess[i]);
            } else {
                printf("%c ", guess[i]);
            }
        }
        printf("\n");

        if (strcmp(guess, targetWord) == 0) {
            won = 1;
            break;
        }
        attempts++;
    }

    if (won) {
        printf("\n" COLOR_GREEN "Splendid! You got it." COLOR_RESET "\n");
    } else {
        printf("\nOut of tries! The word was: " COLOR_GREEN "%s" COLOR_RESET "\n", targetWord);
    }

    return 0;
}
