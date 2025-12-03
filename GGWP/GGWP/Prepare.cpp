#include "Prepare.h"
#include <ctime>   // time
#include <cstdlib> 
bool IsValidCommon(int x, int y)
{
    for (int i = 0; i < SIZE_SNAKE; i++)
    {
        if (snake[i].x == x && snake[i].y == y)
            return false;
    }
    return true;
}
bool IsValidLevel1(int x, int y)
{
    return IsValidCommon(x, y);
}
bool IsValidLevel2(int x, int y)
{
    if (!IsValidCommon(x, y)) return false;
    for (int i = 20; i <= 60; i++)
    {
        if (x == i && y == 10) return false;
    }
    for (int i = 20; i <= 60; i++)
    {
        if (x == i && y == 20) return false;
    }



    return true;
}
bool IsValidLevel3(int x, int y)
{
    if (!IsValidCommon(x, y)) return false;

    for (int j = 6; j <= 22; j++)
        if (x == 30 && y == j) return false;

    for (int j = 6; j <= 22; j++)
        if (x == 50 && y == j) return false;

    return true;
}
bool IsValidLevel4(int x, int y)
{
    if (!IsValidCommon(x, y)) return false;
    for (int i = 10; i <= 70; i++)
        if (x == i && y == 8) return false;

    for (int i = 10; i <= 70; i++)
        if (x == i && y == 18) return false;

    return true;
}
//Tạo thức ăn ở vị trí ngẫu nhiên
void GenerateFood()
{
    srand(time(NULL));

    int x, y;

    do
    {
        x = rand() % (WIDTH_CONSOLE - 3) + 2;
        y = rand() % (HEIGH_CONSOLE - 3) + 2;

        bool ok = false;

        if (LEVEL == 1) ok = IsValidLevel1(x, y);
        if (LEVEL == 2) ok = IsValidLevel2(x, y);
        if (LEVEL == 3) ok = IsValidLevel3(x, y);
        if (LEVEL == 4) ok = IsValidLevel4(x, y);

        if (ok)
        {
            food[FOOD_INDEX].x = x;
            food[FOOD_INDEX].y = y;
            return;
        }

    } while (true);
}
void ResetDataLV1()
{
    SIZE_SNAKE = 6;
    FOOD_INDEX = 0;
    LEVELUP = 0;
    LEVEL = 1;
    SCORE = 0;

    MOVING = 'D';
    CHAR_LOCK = 'D';

    for (int i = 0; i < SIZE_SNAKE; i++)
    {
        snake[i].x = 10 - i;
        snake[i].y = 10;
    }
}
void ResetDataLV2()
{
    ResetDataLV1();
    LEVEL = 2;
}
void ResetDataLV3()
{
    ResetDataLV1();
    LEVEL = 3;
}
void ResetDataLV4()
{
    ResetDataLV1();
    LEVEL = 4;
}
