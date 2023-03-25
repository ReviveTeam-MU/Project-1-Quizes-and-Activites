#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "Revive.h"

u8 rowPosition[MAX_SIZE], colPosition[MAX_SIZE], playerChoice[MAX_SIZE], _continue[MAX_SIZE],
boardCounter, Copy_rowPosition, Copy_colPosition, Copy_playerChoice, Copy_continue, score[3][3],
letters[26], wordToBeGuessed[20], wordTemplate[20], isP1Winner, isP2Winner, points = 0;

u8 *words[wordsCount] =
    {
        "funny", "document", "galaxy", "bee", "education", "extra", "family", "salmon", "employee", "sand",
        "lazy", "game", "fish", "book", "application", "water", "orange", "office", "department", "stress",
        "warm", "animal", "hand", "active", "success", "age", "africa", "approve", "pass", "canada",
        "honey", "diet", "bonus", "weather", "coffee", "session", "horse", "friend", "cheese", "heat",
        "message", "picture", "matrix", "yesterday", "user", "version", "blueberry", "music", "background", "smooth"
    };

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
        // printf("Rows %d: %d\n", i, rowSum);
        // Sleep(100);
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
        // printf("Cols %d: %d\n", i, colSum);
        // Sleep(100);
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
    // printf("diag: %d\n", diag);
    // Sleep(100);
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
    // printf("diagRev: %d\n", diagRev);
    // Sleep(100);
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

void questionSolver(u8 numberOfChoices, u8 correctChoice)
{
    u8 choice[MAX_SIZE];
    system("cls");
    printf("\nChoose The Correct Answer:\n");
    for (u8 i = 0; i < numberOfChoices; i++)
    {
        printf("%d-%c\n", i+1, i+'a');
    }
    fgets(choice, MAX_SIZE, stdin);
    choice[strlen(choice) - 1] = '\0';
    if (correctChoice == choice[0] || correctChoice == choice[0]+32 || correctChoice-'a'+'1' == choice[0])
    {
        printf("\nCorrect!\n");
        points++;
        Sleep(baseDelay/4);
    }
    else
    {
        printf("\nWrong!\n");
        Sleep(baseDelay/4);
    }
    printf("\nThe Answer was: %d-%c\n", correctChoice-'a'+1, correctChoice);
    Sleep(baseDelay);
}

u8 mathQuiz(void)
{
    srand(time(NULL));
    u8 questionsCounter = 5, questionSelector = 0, notToBeSelected[5];
    while (questionsCounter > 0)
    {
        /* Number Between 1 and 25 */
        questionSelector = rand() % 25 + 1;
        for (u8 i = 0; i < 5; i++)
        {
            if (notToBeSelected[i] == questionSelector)
            {
                questionSelector = rand() % 25 + 1;
                break;
            }
            else
            {
                /* Do Nothing */
            }
        }
        switch (questionSelector)
        {
        case 1:
            system("start vlc.exe .\\Diff_Integ\\1.png");
            questionSolver(3, 'a');
            break;
        case 2:
            system("start vlc.exe .\\Diff_Integ\\2.png");
            questionSolver(3, 'b');
            break;
        case 3:
            system("start vlc.exe .\\Diff_Integ\\3.png");
            questionSolver(3, 'c');
            break;
        case 4:
            system("start vlc.exe .\\Diff_Integ\\4.png");
            questionSolver(3, 'a');
            break;
        case 5:
            system("start vlc.exe .\\Diff_Integ\\5.png");
            questionSolver(3, 'b');
            break;
        case 6:
            system("start vlc.exe .\\Diff_Integ\\6.png");
            questionSolver(3, 'c');
            break;
        case 7:
            system("start vlc.exe .\\Diff_Integ\\7.png");
            questionSolver(3, 'a');
            break;
        case 8:
            system("start vlc.exe .\\Diff_Integ\\8.png");
            questionSolver(4, 'c');
            break;
        case 9:
            system("start vlc.exe .\\Diff_Integ\\9.png");
            questionSolver(4, 'b');
            break;
        case 10:
            system("start vlc.exe .\\Diff_Integ\\10.png");
            questionSolver(3, 'a');
            break;
        case 11:
            system("start vlc.exe .\\Diff_Integ\\11.png");
            questionSolver(3, 'b');
            break;
        case 12:
            system("start vlc.exe .\\Diff_Integ\\12.png");
            questionSolver(3, 'c');
            break;
        case 13:
            system("start vlc.exe .\\Diff_Integ\\13.png");
            questionSolver(4, 'b');
            break;
        case 14:
            system("start vlc.exe .\\Diff_Integ\\14.png");
            questionSolver(4, 'b');
            break;
        case 15:
            system("start vlc.exe .\\Diff_Integ\\15.png");
            questionSolver(3, 'c');
            break;
        case 16:
            system("start vlc.exe .\\Diff_Integ\\16.png");
            questionSolver(4, 'a');
            break;
        case 17:
            system("start vlc.exe .\\Diff_Integ\\17.png");
            questionSolver(4, 'b');
            break;
        case 18:
            system("start vlc.exe .\\Diff_Integ\\18.png");
            questionSolver(4, 'd');
            break;
        case 19:
            system("start vlc.exe .\\Diff_Integ\\19.png");
            questionSolver(4, 'c');
            break;
        case 20:
            system("start vlc.exe .\\Diff_Integ\\20.png");
            questionSolver(4, 'b');
            break;
        default:
            /* Do Nothing */
            break;
        }
        system("taskkill /im vlc.exe");
        for (u8 i = 0; i < 5; i++)
        {
            if (notToBeSelected[i] == 0)
            {
                notToBeSelected[i] = questionSelector;
                break;
            }
            else
            {
                /* Do Nothing */
            }
        }
        questionsCounter--;
    }
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
            Sleep(baseDelay);
        }
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

u8 BMEQuiz(void)
{
    u8 game1Choice[MAX_SIZE], Copy_game1Choice = 0;
    while (Copy_game1Choice != 3)
    {
        system("cls");
        printf("Welcome to The Biomedical Quiz!\n");
        printf("Please Select The Type Of Questions You Want:\n");
        printf("---------------------------------------------\n");
        printf("1- Math (Differntiation And Integration)\n");
        printf("2- Medicine (Anatomy)\n");
        printf("3- General Information\n");
        printf("4- Choose Another Game\n");
        printf("---------------------------------------------\n");
        Copy_game1Choice = inputChecker(game1Choice);
        switch (Copy_game1Choice)
        {
        case 1:
            mathQuiz();
            break;
        case 2:
            Copy_game1Choice = gameAgainstComputer();
            break;
        case 3:
            Copy_game1Choice = gameAgainstComputer();
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

u8 TicTacToe(void)
{
    u8 game2Choice[MAX_SIZE], Copy_game2Choice = 0;
    while (Copy_game2Choice != 3)
    {
        system("cls");
        printf("Welcome to Tic Tac Toe!\n");
        printf("Please Select a game mode:\n");
        printf("--------------------------\n");
        printf("1- Against Another Player\n");
        printf("2- Against The Computer\n");
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

void Doughnut(void)
{
    u8 _;
    float A = 0, B = 0;
    float i, j;
    int k;
    float z[1760];
    char b[1760];
    printf("\x1b[2J");
    for(;_ < 100;) {
        memset(b,32,1760);
        memset(z,0,7040);
        for(j=0; j < 6.28; j += 0.07) {
            for(i=0; i < 6.28; i += 0.02) {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y= 12 + 15 * D * (l * h * n + t * m);
                int o = x + 80 * y;
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if(22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }
        printf("\x1b[H");
        for(k = 0; k < 1761; k++) {
            putchar(k % 80 ? b[k] : 10);
            A += 0.00004;
            B += 0.00002;
        }
        Sleep(1);
        _++;
    }
}

u8 Revive(void)
{
    system("cls");
    Sleep(100);
    system("color 17");
    u8 *revive[146] =
    {
    "  RRRRRRRRRRRRRRRRR                                                                 iiii                                                         ",
    "  R::::::::::::::::R                                                               i::::i                                                        ",
    "  R::::::RRRRRR:::::R                                                               iiii                                                         ",
    "  RR:::::R     R:::::R                                                                                                                           ",
    "    R::::R     R:::::R         eeeeeeeeeeee         vvvvvvv           vvvvvvv     iiiiiii      vvvvvvv           vvvvvvv         eeeeeeeeeeee    ",
    "    R::::R     R:::::R       ee::::::::::::ee        v:::::v         v:::::v      i:::::i       v:::::v         v:::::v        ee::::::::::::ee  ",
    "    R::::RRRRRR:::::R       e::::::eeeee:::::ee       v:::::v       v:::::v        i::::i        v:::::v       v:::::v        e::::::eeeee:::::ee",
    "    R:::::::::::::RR       e::::::e     e:::::e        v:::::v     v:::::v         i::::i         v:::::v     v:::::v        e::::::e     e:::::e",
    "    R::::RRRRRR:::::R      e:::::::eeeee::::::e         v:::::v   v:::::v          i::::i          v:::::v   v:::::v         e:::::::eeeee::::::e",
    "    R::::R     R:::::R     e:::::::::::::::::e           v:::::v v:::::v           i::::i           v:::::v v:::::v          e:::::::::::::::::e ",
    "    R::::R     R:::::R     e::::::eeeeeeeeeee             v:::::v:::::v            i::::i            v:::::v:::::v           e::::::eeeeeeeeeee  ",
    "    R::::R     R:::::R     e:::::::e                       v:::::::::v             i::::i             v:::::::::v            e:::::::e           ",
    "  RR:::::R     R:::::R     e::::::::e                       v:::::::v             i::::::i             v:::::::v             e::::::::e          ",
    "  R::::::R     R:::::R      e::::::::eeeeeeee                v:::::v              i::::::i              v:::::v               e::::::::eeeeeeee  ",
    "  R::::::R     R:::::R       ee:::::::::::::e                 v:::v               i::::::i               v:::v                 ee:::::::::::::e  ",
    "  RRRRRRRR     RRRRRRR         eeeeeeeeeeeeee                  vvv                iiiiiiii                vvv                    eeeeeeeeeeeeee  "
    };
    printf("\n\n\n\n\n");
    for (u8 i = 0; revive[i] != NULL; i++)
    {
        printf("\t\t%s\n", revive[i]);
        Sleep(100);
    }
    
    Sleep(baseDelay);
}

/* gcc .\Revive.c .\Logic.c -o .\Revive.exe */

