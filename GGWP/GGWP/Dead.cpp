#include "Dead.h"

// Kiểm tra đụng thân rắn khi đi sang trái
bool ReachBodyLeft()
{
    int headX = snake[0].x - 1;
    int headY = snake[0].y;

    for (int i = 0; i < SIZE_SNAKE - 1; ++i)
    {
        if (snake[i].x == headX && snake[i].y == headY)
            return true;
    }
    return false;
}

bool LeftDeadLevel1()
{
    // Đụng tường trái
    if (snake[0].x - 1 == 1)
        return true;

    if (LEVELUP == 1)
    {
        for (int i = 14; i < 17; ++i)
        {
            if (snake[0].x - 1 == 68 && snake[0].y == i)
                return true;
        }

        for (int i = 12; i < 15; ++i)
        {
            if (snake[0].x - 1 == 65 && snake[0].y == i)
                return true;
        }

        for (int i = 16; i < 19; ++i)
        {
            if (snake[0].x - 1 == 65 && snake[0].y == i)
                return true;
        }
    }

    return false;
}
bool ReachBodyRight()
{
    int headX = snake[0].x + 1;
    int headY = snake[0].y;

    for (int i = 0; i < SIZE_SNAKE - 1; ++i)
    {
        if (snake[i].x == headX && snake[i].y == headY)
            return true;
    }
    return false;
}
bool RightDeadLevel1()
{
    // Đụng tường phải
    if (snake[0].x + 1 == WIDTH_CONSOLE - 1)
        return true;

    if (LEVELUP == 1)
    {
        // Cánh cổng bên phải – bạn đang dùng X = 68 và X = 65 bên trái
        // Bên phải ta đối xứng lại:

        for (int i = 14; i < 17; ++i)
        {
            if (snake[0].x + 1 == 68 && snake[0].y == i)
                return true;
        }

        for (int i = 12; i < 15; ++i)
        {
            if (snake[0].x + 1 == 65 && snake[0].y == i)
                return true;
        }

        for (int i = 16; i < 19; ++i)
        {
            if (snake[0].x + 1 == 65 && snake[0].y == i)
                return true;
        }
    }

    return false;
}

bool ReachBodyUp()
{
    int headX = snake[0].x;
    int headY = snake[0].y - 1;

    for (int i = 0; i < SIZE_SNAKE - 1; ++i)
    {
        if (snake[i].x == headX && snake[i].y == headY)
            return true;
    }
    return false;
}
bool UpDeadLevel1()
{
    if (snake[0].y - 1 == 1)
        return true;

    if (LEVELUP == 1)
    {
        for (int i = 65; i < 69; ++i)
        {
            if (snake[0].x == i && snake[0].y - 1 == 14)
                return true;
        }
    }
    return false;
}

bool ReachBodyDown()
{
    int headX = snake[0].x;
    int headY = snake[0].y + 1;

    for (int i = 0; i < SIZE_SNAKE - 1; ++i)
    {
        if (snake[i].x == headX && snake[i].y == headY)
            return true;
    }
    return false;
}
bool DownDeadLevel1()
{
    if (snake[0].y + 1 == HEIGH_CONSOLE - 1)
        return true;

    if (LEVELUP == 1)
    {
        for (int i = 65; i < 69; ++i)
        {
            if (snake[0].x == i && snake[0].y + 1 == 14)
                return true;
        }
    }

    return false;
}

bool HitWallLv2(int x, int y)
{
    int columns[4] = { 12, 28, 44, 60 };

    for (int i = 0; i < 4; ++i)
        if (x == columns[i])
            return true;

    return false;
}
bool LeftDeadLevel2()
{
    int nx = snake[0].x - 1;
    int ny = snake[0].y;

    if (nx == 1) return true;               

    for (int i = 0; i < SIZE_SNAKE - 1; ++i)
        if (snake[i].x == nx && snake[i].y == ny)
            return true;

    return false;
}

bool RightDeadLevel2()
{
    int nx = snake[0].x + 1;
    int ny = snake[0].y;

    if (nx == WIDTH_CONSOLE - 1) return true;


    for (int i = 0; i < SIZE_SNAKE - 1; ++i)
        if (snake[i].x == nx && snake[i].y == ny)
            return true;

    return false;
}

bool UpDeadLevel2()
{
    int nx = snake[0].x;
    int ny = snake[0].y - 1;

    if (ny == 1) return true;


    for (int i = 0; i < SIZE_SNAKE - 1; ++i)
        if (snake[i].x == nx && snake[i].y == ny)
            return true;

    return false;
}

bool DownDeadLevel2()
{
    int nx = snake[0].x;
    int ny = snake[0].y + 1;

    if (ny == HEIGH_CONSOLE - 1) return true;


    for (int i = 0; i < SIZE_SNAKE - 1; ++i)
        if (snake[i].x == nx && snake[i].y == ny)
            return true;

    return false;
}


bool LeftDeadLevel3() { return LeftDeadLevel2(); }
bool RightDeadLevel3() { return RightDeadLevel2(); }
bool UpDeadLevel3() { return UpDeadLevel2(); }
bool DownDeadLevel3() { return DownDeadLevel2(); }

bool LeftDeadLevel4() { return LeftDeadLevel2(); }
bool RightDeadLevel4() { return RightDeadLevel2(); }
bool UpDeadLevel4() { return UpDeadLevel2(); }
bool DownDeadLevel4() { return DownDeadLevel2(); }
