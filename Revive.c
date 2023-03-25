/**
 * @file Revive.c
 * @author Mohammed Ali (mo7ali47@gmail.com)
 * @brief This Is A Small Project For Our Team's Booth In Mansoura University Faculty Of Engineering Infront Of The Specific Programs building.
 * The Program Is Basically Three Different Games And A Cool Animation For A Spinning Donut (I Stole It From The Internet LOL).
 * The First Program Is A Quiz In Either Math, Medicine Or Random Facts, The Second Is A Tic Tac Toe Game And The Third Is A Hangman Game.
 * The Program Also Takes Some User Data Which Is Saved In A .csv File And Also Stores The Score He Gained From Playing The Games.
 * Each User Has 3 Minutes To Earn As Many Points As Possible. Good Luck And Hope You Like It :).
 * @version 1.0
 * @date 2022-10-24
 * 
 * @copyright Revive Team (c) 2022
 * 
 */
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Revive.h"

u8 points = 0;

int main(void) {
    Revive();
    u8  gameChoice[MAX_SIZE], Copy_gameChoice = 0;
    while (Copy_gameChoice != 5) {
        system("cls");
        printf("Please Select One Of The Following Games:\n");
        printf("-----------------------------------------\n");
        printf("1- Biomedical Quiz\n");
        printf("2- Tic Tac Toe (X O)\n");
        printf("3- Hangman (Word Guesser)\n");
        printf("4- Doughnut\n");
        printf("5- Quit\n");
        printf("-----------------------------------------\n");
        Copy_gameChoice = inputChecker(gameChoice);
        switch (Copy_gameChoice) {
            case 1:
                Copy_gameChoice = BMEQuiz();
                break;
            case 2:
                Copy_gameChoice = TicTacToe();
                break;
            case 3:
                Copy_gameChoice = Hangman();
                break;
            case 4:
                Doughnut();
                break;
            case 5:
                /* Do Nothing */
                break;
            default:
                printf("Please Enter a Valid Option.");
                Sleep(baseDelay);
                break;
        }
    }
    printf("\nThank You For Using Our Program :)\n");
    FILE *file = fopen("data.csv", "a");
    if (file == NULL)
    {
        return -1;
    }
    fprintf(file, "%d\n", points);
    fclose(file);
    Sleep(baseDelay);
    system("cls");
    return 0;
}
