#ifndef REVIVE_H
#define REVIVE_H
#define sumOfX 264
#define sumOfO 237
#define minusX sumOfX - 46
#define minusO sumOfO - 37
#define CONTINUE 0
#define Easy 1
#define Medium 2
#define Hard 3
#define Maths 1
#define Anatomy 2
#define RandomFacts 3
#define EXIT_GAME1 3
#define EXIT_GAME2 3
#define EXIT_GAME3 4
#define true 1
#define false 0
#define wordsCount 60
#define MAX_SIZE 4
#define baseDelay 2000
typedef unsigned char u8;
typedef unsigned short int u16;
typedef struct Questions{
    u8 *question;
    u8 *choices[4];
    u8 *answer;
}Questions;
extern u8 points, _continue[MAX_SIZE], Copy_continue;
void boardPrinter(void);
u8 isPlayerXWinner(void);
u8 isPlayerOWinner(void);
u8 inputChecker(u8*);
void gameStart(void);
u8 boardPlacer(u16, u8, u8, u8*, u8);
u8 checkPossibleWin(u8*, u8);
void continueOrNot(void);
void gameEnd(void);
void questionSolver(u8, u8);
void _questionSolver(Questions);
void quiz(u8);
u8 gameAgainstHuman(void);
u8 gameAgainstComputer(void);
void showHangingStage(void);
void showHangingHead(void);
void showHangingBody(void);
void showHangingArms(void);
void showHangingLegs(void);
u8 wordGuesser(u8*, u8*, u8);

u8 BMEQuiz(void);
u8 TicTacToe(void);
u8 Hangman(void);
void Doughnut(void);
u8 Revive(void);
#endif