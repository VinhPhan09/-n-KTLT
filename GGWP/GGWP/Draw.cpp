#include "Draw.h"
void DrawBoard(int x, int y, int width, int height, int curPosX, int curPosY)
{
    char a = 223;
    char b = 220;
    char c = 219;

    GotoXY(x, y);
    cout << b;
    for (int i = 1; i < width; i++)
        cout << b;
    cout << b;

    GotoXY(x, height + y);
    cout << a;
    for (int i = 1; i < width; i++)
        cout << a;
    cout << a;

    for (int i = y + 1; i < height + y; i++)
    {
        GotoXY(x, i);
        cout << c;

        GotoXY(x + width, i);
        cout << c;
    }

    GotoXY(x + width + 2, y);
    for (int i = 0; i < 30; i++)
        cout << b;

    GotoXY(x + width + 2, y + height);
    for (int i = 0; i < 30; i++)
        cout << a;

    for (int i = 1; i < height; i++)
    {
        GotoXY(x + width + 2, y + i);
        cout << c;

        GotoXY(x + width + 31, y + i);
        cout << c;
    }

    GotoXY(curPosX, curPosY);
}
void SmallBoard()
{
    SetColor(14);
    GotoXY(WIDTH_CONSOLE + 5, 3);
    cout << "SCORE: " << SCORE;

    GotoXY(WIDTH_CONSOLE + 5, 5);
    cout << "SNAKE LENGTH: " << SIZE_SNAKE;

    GotoXY(WIDTH_CONSOLE + 5, 7);
    cout << "LEVEL: " << LEVEL;

    GotoXY(WIDTH_CONSOLE + 5, 9);
    cout << "SPEED: " << SPEED;

    GotoXY(WIDTH_CONSOLE + 5, 11);
    cout << "W/A/S/D: Move";

    GotoXY(WIDTH_CONSOLE + 5, 13);
    cout << "P: Pause| L: Load| T: Save";

    GotoXY(WIDTH_CONSOLE + 5, 15);
    cout << "ESC: Quit";
}
void DrawSnakeAndFood(const char str, int start_char)
{
    if (STATE == 0) return;

    SetColor(SNAKE_COLOR);

    // Vẽ thức ăn
    if (SIZE_SNAKE != 40 && food[FOOD_INDEX].x != 0 && STATE == 1)
    {
        GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
        cout << str;
    }

    // Vẽ rắn
    for (int i = 0; i < SIZE_SNAKE; i++)
    {
        GotoXY(snake[i].x, snake[i].y);

        if (str != ' ')
            cout << Snake_Body[i + start_char];
        else
            cout << str;
    }
}
void DrawContinueGame()
{
    system("cls");
    SetColor(2);

    DrawBoard(1, 1, WIDTH_CONSOLE, HEIGH_CONSOLE);
    SmallBoard();
    SetColor(2);

    switch (LEVEL)
    {
    case 2:
        DrawWallLevel2();
        break;

    case 3:
        DrawWallLevel3();
        break;

    case 4:
        DrawWallLevel4();
        break;
    }

    if (LEVELUP == 1)
    {
        SetColor(3);
        if (LEVEL == 1)
            DrawGateLv1();
        else if (LEVEL == 2)
            DrawGateLv2();
        else if (LEVEL == 3)
            DrawGateLv3();
        else if (LEVEL == 4)
            DrawGateLv4();
    }

    DrawSnakeAndFood(4); // vẽ lại rắn & thức ăn
}
void DrawWallLevel2()
{
    char wall = (char)219;

    int top = 2;
    int bottom = HEIGH_CONSOLE - 2;

    int columns[4] = { 12, 28, 44, 60 };

    for (int y = top; y <= bottom; y++)
    {
        for (int i = 0; i < 4; i++)
        {
            GotoXY(columns[i], y);
            cout << wall;
        }
    }
}
void DrawWallLevel3()
{
    char wall = (char)219;

    int left = 4;
    int right = WIDTH_CONSOLE - 4;

    int midY1 = 8;
    int midY2 = HEIGH_CONSOLE - 8;


    for (int x = left; x <= right; x++)
    {
        GotoXY(x, midY1);
        cout << wall;

        GotoXY(x, midY2);
        cout << wall;
    }

    int colX1 = 20;
    int colX2 = WIDTH_CONSOLE - 20;

    for (int y = midY1; y <= midY2; y++)
    {
        GotoXY(colX1, y);
        cout << wall;

        GotoXY(colX2, y);
        cout << wall;
    }
}
void DrawWallLevel4()
{
    char wall = (char)219;

    int top = 3;
    int bottom = HEIGH_CONSOLE - 3;

    int left = 10;
    int right = WIDTH_CONSOLE - 10;

    int midX = WIDTH_CONSOLE / 2;
    int midY = HEIGH_CONSOLE / 2;


    for (int y = top; y <= bottom; y++)
    {
        GotoXY(left, y);  cout << wall;
        GotoXY(right, y); cout << wall;
    }

    for (int x = left; x <= right; x++)
    {
        GotoXY(x, top); cout << wall;
        GotoXY(x, bottom); cout << wall;
    }

    for (int x = left; x <= right; x++)
    {
        GotoXY(x, midY); cout << wall;
    }
    int inner1 = midX - 10;
    int inner2 = midX + 10;

    for (int y = top; y <= bottom; y++)
    {
        GotoXY(inner1, y); cout << wall;
        GotoXY(inner2, y); cout << wall;
    }
}
void DrawGateLv1()
{
    char g = (char)178;
    int gx = WIDTH_CONSOLE - 5;
    int gy = HEIGH_CONSOLE / 2;

    for (int i = -1; i <= 1; i++)
    {
        GotoXY(gx, gy + i);
        cout << g;
    }

    gate.x = gx;
    gate.y = gy;
}
void DrawGateLv2()
{
    char g = (char)178;
    int gx = WIDTH_CONSOLE / 2;
    int gy = HEIGH_CONSOLE / 2;

    for (int i = -1; i <= 1; i++)
    {
        GotoXY(gx + i, gy);
        cout << g;
    }

    gate.x = gx;
    gate.y = gy;
}
void DrawGateLv3()
{
    char g = (char)178;
    int gx = WIDTH_CONSOLE / 2;
    int gy = 3; // trên cùng

    for (int i = -1; i <= 1; i++)
    {
        GotoXY(gx + i, gy);
        cout << g;
    }

    gate.x = gx;
    gate.y = gy;
}
void DrawGateLv4()
{
    char g = (char)178;
    int gx = WIDTH_CONSOLE / 2;
    int gy = HEIGH_CONSOLE - 4;

    for (int i = -2; i <= 2; i++)
    {
        GotoXY(gx + i, gy);
        cout << g;
    }

    gate.x = gx;
    gate.y = gy;
}

