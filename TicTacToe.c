#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "Revive.h"

u8 rowPosition[MAX_SIZE], colPosition[MAX_SIZE], playerChoice[MAX_SIZE], _continue[MAX_SIZE],
boardCounter, Copy_rowPosition, Copy_colPosition, Copy_playerChoice, Copy_continue, score[3][3], isP1Winner, isP2Winner;

void boardPrinter(void)
{
    system("cls");
    printf("\n    1    2    3\n\n");
    for (u8 i = 0; i < 3; i++)
    {
        printf("%d ", i + 1);
        for (u8 j = 0; j < 3; j++)
        {
            printf("  %c  ", score[i][j]);
        }
        printf("\n\n");
    }
}

u8 inputChecker(u8 *input)
{
    /* Dynamically Allocate a Temporary String */
    u8 *str = calloc(MAX_SIZE, sizeof(u8)), num = 0;
    fgets(input, MAX_SIZE, stdin);
    /* Move All Non-Whitespace characters to the Temporary String */
    for (u8 i = 0, temp = 0; i < strlen(input); i++)
    {
        if (input[i] != ' ')
        {
            str[temp++] = input[i];
        }
    }
    /* Turn The Temporary String Into A Number */
    for (u8 i = 1, j = 0; str[j] != '\0'; j++)
    {
        u8 temp = str[strlen(str) - j - 1];
        if (temp >= '0' && temp <= '9')
        {
            num += (temp - '0') * i;
            i *= 10;
        }
    }
    free(str);
    return num;
}

u8 isPlayerXWinner(void)
{
    return (score[0][0] + score[1][0] + score[2][0] == sumOfX) || /* First Column */
           (score[0][1] + score[1][1] + score[2][1] == sumOfX) || /* Second Column */
           (score[0][2] + score[1][2] + score[2][2] == sumOfX) || /* Third Column */
           (score[0][0] + score[0][1] + score[0][2] == sumOfX) || /* First Row */
           (score[1][0] + score[1][1] + score[1][2] == sumOfX) || /* Second Row */
           (score[2][0] + score[2][1] + score[2][2] == sumOfX) || /* Third Row */
           (score[0][0] + score[1][1] + score[2][2] == sumOfX) || /* Diagonal (Top Left To Bottom Right) */
           (score[0][2] + score[1][1] + score[2][0] == sumOfX);   /* Diagonal (Top Right To Bottom Left) */
}

u8 isPlayerOWinner(void)
{
    return (score[0][0] + score[1][0] + score[2][0] == sumOfO) || /* First Column */
           (score[0][1] + score[1][1] + score[2][1] == sumOfO) || /* Second Column */
           (score[0][2] + score[1][2] + score[2][2] == sumOfO) || /* Third Column */
           (score[0][0] + score[0][1] + score[0][2] == sumOfO) || /* First Row */
           (score[1][0] + score[1][1] + score[1][2] == sumOfO) || /* Second Row */
           (score[2][0] + score[2][1] + score[2][2] == sumOfO) || /* Third Row */
           (score[0][0] + score[1][1] + score[2][2] == sumOfO) || /* Diagonal (Top Left To Bottom Right) */
           (score[0][2] + score[1][1] + score[2][0] == sumOfO);   /* Diagonal (Top Right To Bottom Left) */
}

void gameStart(void)
{
    boardCounter = 0;
    isP1Winner = false, isP2Winner = false;
    for (u8 i = 0; i < 3; i++)
    {
        for (u8 j = 0; j < 3; j++)
        {
            score[i][j] = '*';
        }
    }
    while (1)
    {
        /* Delay Reducer For Repeated Invalid Input */
        static u8 mult = 1;
        system("cls");
        printf("Choose The Player You Want: \n");
        printf("1- Player (X) \n");
        printf("2- Player (O) \n");
        printf("3- Quit The Game \n");
        Copy_playerChoice = inputChecker(playerChoice);
        if (Copy_playerChoice < 1 || Copy_playerChoice > 3)
        {
            printf("\nPlease Enter a Valid Choice.\n");
            Sleep(baseDelay / mult);
            mult *= 2;
        }
        else
        {
            break;
        }
    }
}

u8 boardPlacer(u16 compare, u8 row, u8 col, u8 *player, u8 playMove)
{
    if (compare == minusX && playMove == 'X')
    {
        if (strcmp(player, "Computer") == 0)
        {
            // printf("\nComputer %c\n", playMove);
            score[row][col] = playMove;
            return true;
        }
        else if (strcmp(player, "Human") == 0)
        {
            score[row][col] = 'O';
            // printf("\nHuman %c\n", playMove);
            return true;
        }
        else
        {
            /* Do Nothing */
        }
    }
    else if (compare == minusO && playMove == 'O')
    {
        if (strcmp(player, "Computer") == 0)
        {
            // printf("\nComputer %c\n", playMove);
            score[row][col] = playMove;
            return true;
        }
        else if (strcmp(player, "Human") == 0)
        {
            // printf("\nHuman %c\n", playMove);
            score[row][col] = 'X';
            return true;
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }
    return false;
}

u8 checkPossibleWin(u8 *player, u8 playMove)
{
    u16 rowSum, colSum, diag = 0, diagRev = 0;
    u8 row, col;
    /* Checking Rows */
    for (u8 i = 0; i < 3; i++)
    {
        row = col = rowSum = 0;
        for (u8 j = 0; j < 3; j++)
        {
            if (score[i][j] == '*')
            {
                row = i;
                col = j;
            }
            rowSum += score[i][j];
        }
        if (boardPlacer(rowSum, row, col, player, playMove))
        {
            return true;
        }
        else
        {
            /* Do Nothing */
        }
    }
    /* Checking Columns */
    for (u8 i = 0; i < 3; i++)
    {
        row = col = colSum = 0;
        for (u8 j = 0; j < 3; j++)
        {
            if (score[j][i] == '*')
            {
                row = j;
                col = i;
            }
            colSum += score[j][i];
        }
        if (boardPlacer(colSum, row, col, player, playMove))
        {
            return true;
        }
        else
        {
            /* Do Nothing */
        }
    }
    /* Checking Main Diagonal */
    row = col = 0;
    for (u8 i = 0; i < 3; i++)
    {
        if (score[i][i] == '*')
        {
            row = col = i;
        }
        diag += score[i][i];
    }
    if (boardPlacer(diag, row, col, player, playMove))
    {
        return true;
    }
    else
    {
        /* Do Nothing */
    }
    /* Checking Reversed Diagonal */
    row = col = 0;
    for (u8 i = 0; i < 3; i++)
    {
        if (score[i][2 - i] == '*')
        {
            row = i;
            col = 2 - i;
        }
        diagRev += score[i][2 - i];
    }
    if (boardPlacer(diagRev, row, col, player, playMove))
    {
        return true;
    }
    else
    {
        /* Do Nothing */
    }
    return false;
}

void continueOrNot(void)
{
    Sleep(baseDelay);
    while (1)
    {
        /* Delay Reducer For Repeated Invalid Input */
        static u8 mult = 1;
        system("cls");
        printf("Want to Play Another Game?\n");
        printf("1- Yes               2- No\n");
        Copy_continue = inputChecker(_continue);
        if (Copy_continue < 1 || Copy_continue > 2)
        {
            printf("\nPlease Enter A Correct Number.\n");
            Sleep(baseDelay / mult);
            mult *= 2;
        }
        else
        {
            break;
        }
    }
}

void gameEnd(void)
{
    boardPrinter();
    /* Checking Who Won */
    if (isP1Winner)
    {
        printf("Player (X) Has Won!\n\n");
    }
    else if (isP2Winner)
    {
        printf("Player (O) Has Won!\n\n");
    }
    else
    {
        printf("The Game Ended In A Draw!\n\n");
    }
    continueOrNot();
}

u8 gameAgainstHuman(void)
{
    gameStart();
    if (Copy_playerChoice == 3)
    {
        system("cls");
        return EXIT_GAME2;
    }
    /* Randomizing The First Player */
    srand(time(NULL));
    Copy_playerChoice = rand()%2 + 1;
    while (!isP1Winner && !isP2Winner && boardCounter != 9)
    {
        /* Printing The Score Board */
        boardPrinter();
        switch (Copy_playerChoice)
        {
        case 1:
            printf("Player (X) Turn\n");
            break;
        case 2:
            printf("Player (O) Turn\n");
            break;
        default:
            /* Do Nothing */
            break;
        }
        printf("Enter The Row Number: ");
        Copy_rowPosition = inputChecker(rowPosition);
        printf("Enter The Column Number: ");
        Copy_colPosition = inputChecker(colPosition);
        /* Must be a value from 1 to 3 */
        if ((Copy_rowPosition >= 1 && Copy_rowPosition <= 3) && (Copy_colPosition >= 1 && Copy_colPosition <= 3))
        {
            if (score[Copy_rowPosition - 1][Copy_colPosition - 1] == 'X' || score[Copy_rowPosition - 1][Copy_colPosition - 1] == 'O')
            {
                printf("\nYou Can't Play Here, Please Choose Another Cell.\n");
                Sleep(baseDelay);
                continue;
            }
            if (Copy_playerChoice == 1)
            {
                score[Copy_rowPosition - 1][Copy_colPosition - 1] = 'X';
            }
            else if (Copy_playerChoice == 2)
            {
                score[Copy_rowPosition - 1][Copy_colPosition - 1] = 'O';
            }
            else
            {
                /* Do Nothing */
            }
            boardCounter++;
        }
        else
        {
            printf("\nPlease Enter A Correct Row/Column Number.\n");
            Sleep(baseDelay);
            continue;
        }
        /* Checking if Any Player won */
        isP1Winner = isPlayerXWinner();
        isP2Winner = isPlayerOWinner();
        /* Switching Turns */
        if (Copy_playerChoice == 1)
        {
            Copy_playerChoice = 2;
        }
        else
        {
            Copy_playerChoice = 1;
        }
    }
    gameEnd();
    if (Copy_continue == 1)
    {
        return CONTINUE;
    }
    else
    {
        return EXIT_GAME2;
    }
}

u8 gameAgainstComputer(void)
{
    srand(time(NULL));
    u8 turnPlayer, randomizer = rand()%2;
    gameStart();
    if (Copy_playerChoice == 3)
    {
        system("cls");
        return EXIT_GAME2;
    }
    /* Randomizing The First Player */
    boardCounter += randomizer;
    while (!isP1Winner && !isP2Winner && (boardCounter != (9 + randomizer)))
    {
        /*
        If turnPlayer = 0, The player is The Human
        If turnPlayer = 1, The player is The Computer
        */
        turnPlayer = boardCounter % 2;
        /* Printing The Score Board */
        boardPrinter();
        if (turnPlayer == 0)
        {
            switch (Copy_playerChoice)
            {
            case 1:
                printf("Human Player (X) Turn\n");
                break;
            case 2:
                printf("Human Player (O) Turn\n");
                break;
            default:
                /* Do Nothing */
                break;
            }
            printf("Enter The Row Number: ");
            Copy_rowPosition = inputChecker(rowPosition);
            printf("Enter The Column Number: ");
            Copy_colPosition = inputChecker(colPosition);
            /* Must be a value from 1 to 3 */
            if ((Copy_rowPosition >= 1 && Copy_rowPosition <= 3) && (Copy_colPosition >= 1 && Copy_colPosition <= 3))
            {
                if (score[Copy_rowPosition - 1][Copy_colPosition - 1] == 'X' || score[Copy_rowPosition - 1][Copy_colPosition - 1] == 'O')
                {
                    printf("\nYou Can't Play Here, Please Choose Another Cell.\n");
                    Sleep(baseDelay);
                    continue;
                }
                if (Copy_playerChoice == 1)
                {
                    score[Copy_rowPosition - 1][Copy_colPosition - 1] = 'X';
                }
                else if (Copy_playerChoice == 2)
                {
                    score[Copy_rowPosition - 1][Copy_colPosition - 1] = 'O';
                }
                else
                {
                    /* Do Nothing */
                }
                boardCounter++;
            }
            else
            {
                printf("\nPlease Enter A Correct Row/Column Number.\n");
                Sleep(baseDelay);
                continue;
            }
            /* Checking if Any Player won */
            isP1Winner = isPlayerXWinner();
            isP2Winner = isPlayerOWinner();
        }
        else
        {
            /* A Variable that checks whether a move was made here or not */
            u8 currentBoardCounter = boardCounter, playMove;
            switch (Copy_playerChoice)
            {
            case 1:
                printf("Computer Player (O) Turn\n");
                playMove = 'O';
                if (checkPossibleWin("Computer", 'O') || checkPossibleWin("Human", 'X'))
                {
                    boardCounter++;
                }
                else
                {
                    /* Do Nothing */
                }
                break;
            case 2:
                printf("Computer Player (X) Turn\n");
                playMove = 'X';
                if (checkPossibleWin("Computer", 'X') || checkPossibleWin("Human", 'O'))
                {
                    boardCounter++;
                }
                else
                {
                    /* Do Nothing */
                }
                break;
            default:
                /* Do Nothing */
                break;
            }
            if (currentBoardCounter < boardCounter)
            {
                /* Checking if Any Player won */
                isP1Winner = isPlayerXWinner();
                isP2Winner = isPlayerOWinner();
                Sleep(rand() % (baseDelay/2) + (baseDelay/2));
                continue;
            }
            else
            {
                if (score[1][1] == '*')
                {
                    score[1][1] = playMove;
                }
                else if (score[0][0] == '*')
                {
                    score[0][0] = playMove;
                }
                else if (score[0][2] == '*')
                {
                    score[0][2] = playMove;
                }
                else if (score[2][0] == '*')
                {
                    score[2][0] = playMove;
                }
                else if (score[2][2] == '*')
                {
                    score[2][2] = playMove;
                }
                else if (score[0][1] == '*')
                {
                    score[0][1] = playMove;
                }
                else if (score[1][0] == '*')
                {
                    score[1][0] = playMove;
                }
                else if (score[1][2] == '*')
                {
                    score[1][2] = playMove;
                }
                else if (score[2][1] == '*')
                {
                    score[2][1] = playMove;
                }
                else
                {
                    /* Do Nothing */
                }
                boardCounter++;
            }
            /* Checking if Any Player won */
            isP1Winner = isPlayerXWinner();
            isP2Winner = isPlayerOWinner();
            Sleep(rand() % (baseDelay/2) + (baseDelay/2));
        }
    }
    if ((Copy_playerChoice == 1 && isP1Winner) || (Copy_playerChoice == 2 && isP2Winner))
    {
        points += 10;
    }
    gameEnd();
    if (Copy_continue == 1)
    {
        return CONTINUE;
    }
    else
    {
        return EXIT_GAME2;
    }
}

u8 TicTacToe(void)
{
    u8 game2Choice[MAX_SIZE], Copy_game2Choice = 0;
    while (Copy_game2Choice != 3)
    {
        system("cls");
        printf("Welcome to Tic Tac Toe!\n");
        printf("Please Select a game mode:\n");
        printf("--------------------------\n");
        printf("1- Against Another Player (No Points)\n");
        printf("2- Against The Computer (10 Points If You Beat The Computer)\n");
        printf("3- Choose Another Game\n");
        printf("--------------------------\n");
        Copy_game2Choice = inputChecker(game2Choice);
        switch (Copy_game2Choice)
        {
        case 1:
            Copy_game2Choice = gameAgainstHuman();
            break;
        case 2:
            Copy_game2Choice = gameAgainstComputer();
            break;
        case 3:
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
