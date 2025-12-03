#ifndef System_h
#define System_h
#include<iostream>
#include<Windows.h>
#include<string>
#include<fstream>
#include<conio.h>
#include <mmsystem.h>
#include<stdio.h>
#define MAX_SIZE_SNAKE 10
#define MAX_SIZE_FOOD 4
using namespace std;
struct CROOD {
    int x;
    int y;
};
const char Snake_Body[] = "231204062312036323120375";
extern POINT snake[10];
extern POINT food[MAX_SIZE_FOOD];
extern POINT gate;
enum state {
    MENU,
    INGAME,
    SETTING,
    SETCOLOR,
    SETSPEED,
    SETSOUND,
    LOADGAME,
    INFORMATION,
    GAMEOVER,
    QUITGAME
}; 
extern int IS_GATE_ON;
extern state interf;
extern int CHAR_LOCK;
extern int MOVING;
extern int SPEED;
extern int HEIGH_CONSOLE, WIDTH_CONSOLE;
extern int FOOD_INDEX;
extern int SIZE_SNAKE;
extern int STATE;
extern int LEVEL;
extern int LEVELUP;
extern int temp;
extern int SCORE;
extern int start_char;
extern int SOUND;
extern int SNAKE_COLOR;
extern bool GAME_RUNNING;

void FixConsoleWindow();
void DisableSelection();
void ShowScrollbar(BOOL Show);
void GotoXY(int x, int y);
void ShowCur(bool CursorVisibility);
void SetColor(WORD color);
void resizeConsole(int width, int height);
#endif 

