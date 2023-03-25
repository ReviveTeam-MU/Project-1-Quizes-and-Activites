#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Revive.h"

u8 Revive(void)
{
    u8 userName[50], userEmail[40], userLevel[5], userProgram[10], commChoice[MAX_SIZE], nonTechIndex, techIndex,
    *wantedCommNonTech[5] = {"PR(Public Relations)", "HR(Human Resources)", "FR(Financial Resources)", "Logistics", "Media"},
    *wantedCommTech[5] = {"Software", "Hardware", "Mechanical Design", "Embedded Systems", "N/A"};
    system("cls");
    Sleep(250);
    system("color 17");
    u8 *revive[144] =
    {
    "RRRRRRRRRRRRRRRRR                                                                 iiii                                                         ",
    "R::::::::::::::::R                                                               i::::i                                                        ",
    "R::::::RRRRRR:::::R                                                               iiii                                                         ",
    "RR:::::R     R:::::R                                                                                                                           ",
    "  R::::R     R:::::R         eeeeeeeeeeee         vvvvvvv           vvvvvvv     iiiiiii      vvvvvvv           vvvvvvv         eeeeeeeeeeee    ",
    "  R::::R     R:::::R       ee::::::::::::ee        v:::::v         v:::::v      i:::::i       v:::::v         v:::::v        ee::::::::::::ee  ",
    "  R::::RRRRRR:::::R       e::::::eeeee:::::ee       v:::::v       v:::::v        i::::i        v:::::v       v:::::v        e::::::eeeee:::::ee",
    "  R:::::::::::::RR       e::::::e     e:::::e        v:::::v     v:::::v         i::::i         v:::::v     v:::::v        e::::::e     e:::::e",
    "  R::::RRRRRR:::::R      e:::::::eeeee::::::e         v:::::v   v:::::v          i::::i          v:::::v   v:::::v         e:::::::eeeee::::::e",
    "  R::::R     R:::::R     e:::::::::::::::::e           v:::::v v:::::v           i::::i           v:::::v v:::::v          e:::::::::::::::::e ",
    "  R::::R     R:::::R     e::::::eeeeeeeeeee             v:::::v:::::v            i::::i            v:::::v:::::v           e::::::eeeeeeeeeee  ",
    "  R::::R     R:::::R     e:::::::e                       v:::::::::v             i::::i             v:::::::::v            e:::::::e           ",
    "RR:::::R     R:::::R     e::::::::e                       v:::::::v             i::::::i             v:::::::v             e::::::::e          ",
    "R::::::R     R:::::R      e::::::::eeeeeeee                v:::::v              i::::::i              v:::::v               e::::::::eeeeeeee  ",
    "R::::::R     R:::::R       ee:::::::::::::e                 v:::v               i::::::i               v:::v                 ee:::::::::::::e  ",
    "RRRRRRRR     RRRRRRR         eeeeeeeeeeeeee                  vvv                iiiiiiii                vvv                    eeeeeeeeeeeeee  "
    };
    printf("\n\n\n\n\n");
    for (u8 i = 0; revive[i] != NULL; i++)
    {
        printf("\t\t%s\n", revive[i]);
        Sleep(100);
    }
    Sleep(baseDelay);
    system("cls");
    printf("Welcome To Our Project!\n");
    Sleep(baseDelay/2);
    printf("Befor We Start, Please Enter The Following Data:\n");
    Sleep(baseDelay/2);
    do
    {
        printf("Full Name: ");
        fgets(userName, 50, stdin);
        userName[strlen(userName) - 1] = '\0';
        printf("Email: ");
        fgets(userEmail, 40, stdin);
        userEmail[strlen(userEmail) - 1] = '\0';
        printf("Level: ");
        fgets(userLevel, 5, stdin);
        userLevel[strlen(userLevel) - 1] = '\0';
        printf("Program: ");
        fgets(userProgram, 10, stdin);
        userProgram[strlen(userProgram) - 1] = '\0';
        printf("Non-Technical Committee You Want To Join (Select One Of The Following):\n");
        for (u8 i = 0; i < 5; i++)
        {
            printf("%d-%s\n", i+1, wantedCommNonTech[i]);
        }
        printf("\n");
        nonTechIndex = inputChecker(commChoice) - 1;
        printf("\n");
        printf("Technical Committee You Want To Join (Select N/A if you don't want any):\n");
        for (u8 i = 0; i < 5; i++)
        {
            printf("%d-%s\n", i+1, wantedCommTech[i]);
        }
        printf("\n");
        techIndex = inputChecker(commChoice) - 1;
        printf("\n");
        Sleep(baseDelay);
        system("cls");
        printf("This Is The Data You Entered:\n");
        printf("Full Name: %s\n", userName);
        printf("Email: %s\n", userEmail);
        printf("Level: %s\n", userLevel);
        printf("Program: %s\n", userProgram);
        printf("Non-Technical Committee Choice: %s\n", wantedCommNonTech[nonTechIndex]);
        printf("Technical Committee Choice: %s\n", wantedCommTech[techIndex]);
        Sleep(baseDelay);
        while (1)
        {
            /* Delay Reducer For Repeated Invalid Input */
            static u8 mult = 1;
            printf("Do You Want To Change Anything?\n");
            printf("1-Yes                      2-No\n");
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
        system("cls");
    } while (Copy_continue == 1);
    
    FILE *file = fopen("data.csv", "a");
    if (file == NULL)
    {
        return -1;
    }
    fprintf(file, "%s,%s,%s,%s,%s,%s,", userName, userEmail, userLevel, userProgram, wantedCommNonTech[nonTechIndex], wantedCommTech[techIndex]);
    fclose(file);
}
