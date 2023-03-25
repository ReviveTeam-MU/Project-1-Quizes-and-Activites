#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "Revive.h"

Questions anatomyBank[] = {{"Which blood group is called a universal donor?", {"A", "B", "AB", "O"}, "O"},
                           {"Which of the following helps in blood clotting?", {"Vitamin A", "Vitamin D", "Vitamin K", "Folic Acid"}, "Vitamin K"},
                           {"Whic of the following is the main thinking part of the human brain?", {"Hind-Brain", "Cerebrum", "Mid-brain", "None of the above"}, "Cerebrum"},
                           {"Which blood group is called a universal acceptor?", {"O+", "O-", "AB-", "AB+"}, "AB+"},
                           {"Saliva helps in digestion of_______.", {"Starch", "Fiber", "Proteins", "Fats"}, "Starch"},
                           {"Human anatomy is the study of_______.", {"The functions of body parts", "The structure of the human body", "Bacteria and viruses", "Disease and its causes"}, "The structure of the human body"},
                           {"How many bones does an adult human skeleton have?", {"202", "204", "206", "208"}, "206"},
                           {"What substance are nails made of?", {"Keratin", "Melanin", "Collagen", "Carbon"}, "Keratin"},
                           {"What gas is a waste product of respiration?", {"CH4", "CO2", "CO", "O2"}, "CO2"},
                           {"What is the largest gland in human body?", {"Thymus", "Kidneys", "Liver", "Pancreases"}, "Liver"},
                           {"What is a human heart made up of?", {"Tissues", "Muscle", "Skin", "Bone"}, "Muscle"},
                           {"Human Physiology is the study of_______.", {"The mind and behavior", "The internal and external structures of the human body", "The functions of body parts", "Microscopic organisms"}, "The internal and external structures of the human body"},
                           {"Which type of cell carries oxygen around the body?", {"Platelets", "Red Blood Cells", "White Blood Cells", "Hormones"}, "Red Blood Cells"},
                           {"What is a human heart made up of?", {"Tissues", "Muscle", "Skin", "Bone"}, "Muscle"},
                           {"What percentage of the human body is water?", {"50%", "66%", "75%", "80%"}, "66%"},
                           {"The smallest bones in the human body are found in the_______.", {"Feet", "Ears", "Fingers", "Knees"}, "Ears"},
                           {"What is the largest organ of the human body?", {"Brain", "Liver", "Spine", "Skin"}, "Skin"},
                           {"The weight of the human body is mainly made up of_______.", {"Bones", "Skin", "Body parts", "Water"}, "Water"},
                           {"What is the strongest muscle in the human body?", {"Neck", "Thighs", "Hands", "Jaws"}, "Jaws"},
                           {"How many chambers does the human heart have?", {"One", "Two", "Four", "Six"}, "Four"}};

Questions randomFactsBank[] = {{"In which museum can you find Leonardo Da Vinci's Mona Lisa?", {"Le Louvre", "Uffizi Museum", "British Museum", "Metropolitan Museum of Art"}, "Le Louvre"},
                               {"What is the largest continent in size?", {"Asia", "Africa", "Europe", "North America"}, "Asia"},
                               {"Which famous inventor invented the telephone?", {"Thomas Edison", "Benjamin Franklin", "Alexander Graham Bell", "Nikola Tesla"}, "Alexander Graham Bell"},
                               {"What does the Richter scale measure?", {"Wind Speed", "Temperature", "Tornado Strength", "Earthquake intensity"}, "Earthquake intensity"},
                               {"Which country is the footballer Cristiano Ronaldo from?", {"Spain", "Brazil", "Uruguay", "Portugal"}, "Portugal"},
                               {"What is the longest river in the world?", {"Amazon River", "Nile River", "Yellow River", "Congo River"}, "Nile River"},
                               {"How many sides does a Hexagon have?", {"5", "6", "7", "8"}, "6"},
                               {"Who is the CEO of Amazon?", {"Elon Musk", "Tim Cook", "Mark Zuckerberg", "Jeff Bezos"}, "Jeff Bezos"},
                               {"Who was Euclid?", {"A philosopher", "A poet", "A painter", "A mathematician"}, "A mathematician"},
                               {"What is the capital of Iraq?", {"Baghdad", "Islamabad", "Tehran", "Amman"}, "Baghdad"},
                               {"What colour is the 'M' from the McDonald's logo?", {"Blue", "Red", "Yellow", "Black"}, "Yellow"},
                               {"What is guacamole made of?", {"Banana", "Yoghurt", "Avocado", "Chick Pea"}, "Avocado"},
                               {"'Onze' is the french number for?", {"3", "8", "9", "11"}, "11"},
                               {"What does NASA stand for?", {"National Aeronautics and Space Administration", "Nautical And Space Association", "National Aeronautics and Space Association", "New Aeronautics and Spacial Administration"}, "National Aeronautics and Space Administration"},
                               {"Who was the first woman to win a Nobel Prize?", {"Mother Teresa", "Marie Curie", "Jane Adams", "Alva Myrdal"}, "Marie Curie"},
                               {"What is the national animal of England?", {"Puffin", "Lion", "Rabbit", "Fox"}, "Lion"},
                               {"Which one of the following companies has a mermaid in its logo?", {"Twitter", "HSBC", "Target", "Starbucks"}, "Starbucks"},
                               {"Apart from water, what is the most popular drink in the world?", {"Tea", "Coffee", "Beer", "Orange Juice"}, "Tea"},
                               {"In The Lion King, who is Simba's uncle?", {"Mufasa", "Scar", "Timon", "Zazu"}, "Scar"},
                               {"Which chemical element has Ag as a symbol?", {"Gold", "Silver", "Iron", "Carbon"}, "Silver"}};

void questionSolver(u8 numberOfChoices, u8 correctChoice)
{
    /* The Choice You Took */
    u8 choice[MAX_SIZE];
    system("cls");
    printf("\nChoose The Correct Answer:\n");
    for (u8 i = 0; i < numberOfChoices; i++)
    {
        printf("%d-%c\n", i+1, i+'a');
    }
    fgets(choice, MAX_SIZE, stdin);
    choice[strlen(choice) - 1] = '\0';
    /* Determining If You Wrote The Correct Choice As An Alphabet Capital Character Or A Small Character Or A Number */
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
    /* Printing The Answer */
    printf("\nThe Answer was: %d-%c\n", correctChoice-'a'+1, correctChoice);
    Sleep(baseDelay);
}

void _questionSolver(Questions Q)
{
    /* The Choice You Took And A Variable To Store The Index Of The Correct Answer */
    u8 choice[MAX_SIZE], correctChoiceIndex;
    system("cls");
    /* Printing The Question */
    printf("%s\n\n", Q.question);
    for(u8 i = 0; i < 4; i++)
    {
        /* Printing The Choices */
        printf("%d-%s\n", i+1, Q.choices[i]);
        /* Saving The Index Of The Correct Answer */
        if (strcmp(Q.choices[i], Q.answer) == 0)
        {
            correctChoiceIndex = i;
        }
    }
    fgets(choice, MAX_SIZE, stdin);
    choice[strlen(choice) - 1] = '\0';
    /* Determining If You Wrote The Correct Choice As A Number */
    if (strcmp(Q.choices[choice[0]-'1'], Q.answer) == 0)
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
    /* Printing The Answer */
    printf("\nThe Answer was: %d-%s\n", correctChoiceIndex+1, Q.answer);
    Sleep(baseDelay);
}

void quiz(u8 typeOfQuestion)
{
    srand(time(NULL));
    u8 questionsCounter = 5, questionSelector = 0;
    while (questionsCounter > 0)
    {
        /* Random Number Between 1 and 20 */
        questionSelector = rand() % 20 + 1;
        if (typeOfQuestion == Maths)
        {
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
        }
        else if (typeOfQuestion == Anatomy)
        {
            _questionSolver(anatomyBank[questionSelector-1]);
        }
        else if (typeOfQuestion == RandomFacts)
        {
            _questionSolver(randomFactsBank[questionSelector-1]);
        }
        else
        {
            /* Do Nothing */
        }
        questionsCounter--;
    }
}

u8 BMEQuiz(void)
{
    u8 game1Choice[MAX_SIZE], Copy_game1Choice = 0;
    while (Copy_game1Choice != 4)
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
            quiz(Maths);
            break;
        case 2:
            quiz(Anatomy);
            break;
        case 3:
            quiz(RandomFacts);
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

/* gcc .\Revive.c .\Hangman.c .\TicTacToe.c .\BMEQuiz.c .\Doughnut.c .\Revive_Logo.c  -o .\Revive.exe */