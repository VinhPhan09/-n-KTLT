#include "ProcessGame.h"

int main()
{
    if (SOUND)
        PlaySound(L"bg.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    else
        PlaySound(NULL, 0, 0);
    interf = MENU;
    resizeConsole(1100, 600);
    FixConsoleWindow();
    DisableSelection();
    ShowScrollbar(0);

    StartGame();
    ShowCur(0);
    SetColor(2);
    Menu();

    while (1)
    {
        switch (interf)
        {
        case MENU:
            Menu();
            break;

        case INGAME:
            InGame();
            break;

        case SETTING:
            Setting();
            break;

        case SETCOLOR:
            SetSnakeColor();
            break;

        case SETSPEED:
            SetSpeed();
            break;

        case SETSOUND:
            SetSound();
            break;

        case LOADGAME:
            LoadGame();
            break;

        case INFORMATION:
            Information();
            break;

        case GAMEOVER:
            GameOver();
            break;

        case QUITGAME:
            QuitGame();
            return 0;
        }
    }
}
