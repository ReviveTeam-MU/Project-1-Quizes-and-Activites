#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "Revive.h"

u8 letters[26], wordToBeGuessed[20], wordTemplate[20];
u8 *words[wordsCount] =
    {
        "funny", "document", "galaxy", "bee", "education", "extra", "family", "salmon", "employee", "sand",
        "lazy", "game", "fish", "book", "application", "water", "orange", "office", "department", "stress",
        "warm", "animal", "hand", "active", "success", "age", "africa", "approve", "pass", "canada",
        "honey", "diet", "bonus", "weather", "coffee", "session", "horse", "friend", "cheese", "heat",
        "message", "picture", "matrix", "yesterday", "user", "version", "blueberry", "music", "background", "smooth",
        "bike", "car", "taxi", "sea", "cat", "revive", "ball", "cup", "deep", "fly"
    };

void showHangingStage(void)
{
    printf("\n");
    printf("    ********************            \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("  ********************************  \n");
    printf("************************************\n");
    printf("\n");
}

void showHangingHead(void)
{
    printf("\n");
    printf("    ********************            \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **           ************       \n");
    printf("    **         **            **     \n");
    printf("    **        **              **    \n");
    printf("    **       **    **    **    **   \n");
    printf("    **       **                **   \n");
    printf("    **       **                **   \n");
    printf("    **       **     *    *     **   \n");
    printf("    **        **     ****     **    \n");
    printf("    **         **            **     \n");
    printf("    **           ************       \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("  ********************************  \n");
    printf("************************************\n");
    printf("\n");
}

void showHangingBody(void)
{
    printf("\n");
    printf("    ********************            \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **           ************       \n");
    printf("    **         **            **     \n");
    printf("    **        **              **    \n");
    printf("    **       **    **    **    **   \n");
    printf("    **       **                **   \n");
    printf("    **       **                **   \n");
    printf("    **       **     *    *     **   \n");
    printf("    **        **     ****     **    \n");
    printf("    **         **            **     \n");
    printf("    **           ************       \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("  ********************************  \n");
    printf("************************************\n");
    printf("\n");
}

void showHangingArms(void)
{
    printf("\n");
    printf("    ********************            \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **           ************       \n");
    printf("    **         **            **     \n");
    printf("    **        **              **    \n");
    printf("    **       **    **    **    **   \n");
    printf("    **       **                **   \n");
    printf("    **       **                **   \n");
    printf("    **       **     *    *     **   \n");
    printf("    **        **     ****     **    \n");
    printf("    **         **            **     \n");
    printf("    **           ************       \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **              ******          \n");
    printf("    **             ** ** **         \n");
    printf("    **            **  **  **        \n");
    printf("    **           **   **   **       \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("    **                              \n");
    printf("  ********************************  \n");
    printf("************************************\n");
    printf("\n");
}

void showHangingLegs(void)
{
    printf("\n");
    printf("    ********************            \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **           ************       \n");
    printf("    **         **            **     \n");
    printf("    **        **              **    \n");
    printf("    **       **    x     x     **   \n");
    printf("    **       **                **   \n");
    printf("    **       **                **   \n");
    printf("    **       **      ****      **   \n");
    printf("    **        **    *    *    **    \n");
    printf("    **         **            **     \n");
    printf("    **           ************       \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **              ******          \n");
    printf("    **             ** ** **         \n");
    printf("    **            **  **  **        \n");
    printf("    **           **   **   **       \n");
    printf("    **                **            \n");
    printf("    **                **            \n");
    printf("    **               ****           \n");
    printf("    **              **  **          \n");
    printf("    **             **    **         \n");
    printf("    **            **      **        \n");
    printf("    **                              \n");
    printf("  ********************************  \n");
    printf("************************************\n");
    printf("\n");
}

u8 wordGuesser(u8 *wordToBeGuessed, u8 *placeHolder, u8 difficulty)
{
    u8 letterGuess[MAX_SIZE] = "", tries = 4;
    u8 isFirstTurn = true;
    /* While the word is not guessed correctly yet and tries doesn't equal zero */
    while (strcmp(wordToBeGuessed, placeHolder) && (tries > 0))
    {
        u8 oldCharPlaceHolder = 0, newCharPlaceHolder = 0;
        for (u8 i = 0; i < strlen(wordToBeGuessed); i++)
        {
            if(wordToBeGuessed[i] == '_')
            {
                oldCharPlaceHolder++;
            }
        }
        u8 isCharFound = false;
        system("cls");
        switch (tries)
        {
        case 5:
        case 4:
            showHangingStage();
            break;
        case 3:
            showHangingHead();
            break;
        case 2:
            showHangingBody();
            break;
        case 1:
            showHangingArms();
            break;
        default:
            /* Do Nothing */
            break;
        }
        for (u8 i = 0; i < strlen(letters); i++)
        {
            printf("%c ", letters[i]);
        }
        printf("\n");
        for (u8 i = 0; i < strlen(placeHolder); i++)
        {
            printf("%c ", placeHolder[i]);
        }
        if (isFirstTurn)
        {
            srand(time(NULL));
            u8 randomIndex = rand() % strlen(wordToBeGuessed);
            switch (difficulty)
            {
            case Easy:
                tries++;
                letterGuess[0] = wordToBeGuessed[randomIndex];
                break;
            case Medium:
                letterGuess[0] = wordToBeGuessed[randomIndex];
                break;
            case Hard:
                isFirstTurn = false;
                break;
            default:
                /* Do Nothing */
                break;
            }
        }
        else
        {
            printf("\nGuess a Letter: ");
            fgets(letterGuess, MAX_SIZE, stdin);
            letterGuess[strlen(letterGuess) - 1] = '\0';
        }
        if (letterGuess[0] == 0)
        {
            continue;
        }
        else
        {
            /* Do Nothing */
        }
        if ((letterGuess[0] >= 'a' && letterGuess[0] <= 'z'))
        {
            for (u8 i = 0; i < 26; i++)
            {
                if (letters[i] == letterGuess[0])
                {
                    letters[i] = '.';
                    break;
                }
                else
                {
                    /* Do Nothing */
                }
            }
            for (u8 i = 0; i < strlen(wordToBeGuessed); i++)
            {
                if (wordToBeGuessed[i] == letterGuess[0])
                {
                    isCharFound = true;
                    break;
                }
                else
                {
                    /* Do Nothing */
                }
            }
            if (isFirstTurn)
            {
                for (u8 i = 0; i < strlen(wordToBeGuessed); i++)
                {
                    if (wordToBeGuessed[i] == letterGuess[0])
                    {
                        placeHolder[i] = letterGuess[0];
                    }
                    else
                    {
                        /* Do Nothing */
                    }
                }
                isFirstTurn = false;
            }
            else
            {
                if (isCharFound)
                {
                    printf("\nCorrect!\n");
                    for (u8 i = 0; i < strlen(wordToBeGuessed); i++)
                    {
                        if (wordToBeGuessed[i] == letterGuess[0])
                        {
                            placeHolder[i] = letterGuess[0];
                        }
                        else
                        {
                            /* Do Nothing */
                        }
                    }
                }
                else
                {
                    printf("\nWrong!\n");
                    tries--;
                }
            }
        }
        else
        {
            printf("\nWrong Input! Try Again ");
            tries--;
        }
        for (u8 i = 0; i < strlen(wordToBeGuessed); i++)
        {
            if(wordToBeGuessed[i] == '_')
            {
                newCharPlaceHolder++;
            }
        }
        points += (oldCharPlaceHolder - newCharPlaceHolder);
        Sleep(baseDelay);
    }
    if (strcmp(wordToBeGuessed, placeHolder) == 0)
    {
        printf("\nYou Won! Congrats! :)\n");
        printf("\nThe Word Was: %s\n", wordToBeGuessed);
        Sleep(baseDelay);
    }
    else
    {
        system("cls");
        showHangingLegs();
        printf("\nYou Lost...\nBetter Luck Next Time :(\n");
        printf("\nThe Word Was: %s\n", wordToBeGuessed);
        Sleep(baseDelay);
    }
    continueOrNot();
    if (Copy_continue == 1)
    {
        return CONTINUE;
    }
    else
    {
        return EXIT_GAME3;
    }
}

u8 Hangman(void)
{
    u8 game3Choice[MAX_SIZE], Copy_game3Choice = 0;
    while (Copy_game3Choice != 4)
    {
        srand(time(NULL));
        strcpy(wordToBeGuessed, words[rand() % wordsCount]);
        for (u8 i = 0; i < 20; i++)
        {
            wordTemplate[i] = '\0';
        }
        for (u8 i = 0; i < strlen(wordToBeGuessed); i++)
        {
            wordTemplate[i] = '_';
        }
        for (u8 i = 'a'; i <= 'z'; i++)
        {
            letters[i - 'a'] = i;
        }
        system("cls");
        printf("Welcome to Hangman!\n");
        printf("Please Select a game mode:\n");
        printf("--------------------------\n");
        printf("1- Easy\n");
        printf("2- Medium\n");
        printf("3- Hard\n");
        printf("4- Choose Another Game\n");
        printf("--------------------------\n");
        Copy_game3Choice = inputChecker(game3Choice);
        switch (Copy_game3Choice)
        {
        case 1:
            Copy_game3Choice = wordGuesser(wordToBeGuessed, wordTemplate, Easy);
            break;
        case 2:
            Copy_game3Choice = wordGuesser(wordToBeGuessed, wordTemplate, Medium);
            break;
        case 3:
            Copy_game3Choice = wordGuesser(wordToBeGuessed, wordTemplate, Hard);
            break;
        case 4:
            /* Do Nothing */
            break;
        default:
            printf("Please Enter a Valid Option.");
            Sleep(baseDelay);
            break;
        }
    }
    return CONTINUE;
}
