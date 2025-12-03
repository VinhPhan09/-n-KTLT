#include "System.h"
POINT snake[10];
POINT food[MAX_SIZE_FOOD];
int MOVING = 'D';    
bool GAME_RUNNING = true;
POINT gate;
int IS_GATE_ON = 0;
// Khóa ký tự nhập vào
int CHAR_LOCK = 0;

// Biến dùng trong menu
int start_char = 0;
int temp = 0;

// Âm thanh: 1 = mở, 0 = tắt
int SOUND = 1;

// Trạng thái giao diện
state interf = MENU;

// Kích thước màn hình console
int WIDTH_CONSOLE = 80;
int HEIGH_CONSOLE = 25;

// Level & level up
int LEVEL = 1;
int LEVELUP = 0;
int FOOD_INDEX = 0;

// Độ dài rắn
int SIZE_SNAKE = 8;

// Trạng thái game
int STATE = 0;    // 0: dừng, 1: đang chạy 
int SCORE = 0;
int SPEED = 1;

// Màu của rắn
int SNAKE_COLOR = 2;

void FixConsoleWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void GotoXY(int x, int y)
{
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
    SetConsoleCursorInfo(handle, &cursor);
}
void SetColor(WORD color)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;

    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void DisableSelection()
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
}
void ShowScrollbar(BOOL Show)
{
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, Show);
}
void resizeConsole(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

