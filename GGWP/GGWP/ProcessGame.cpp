#include "ProcessGame.h"
void StartGame()
{
    STATE = 1;
    system("cls");
    SetColor(2);

    // Initialize original data
    if (LEVEL == 1)
    {
        ResetDataLV1();
    }
    else if (LEVEL == 2)
    {
        ResetDataLV2();
        DrawWallLevel2();
    }
    else if (LEVEL == 3)
    {
        ResetDataLV3();
        DrawWallLevel3();
    }
    else if (LEVEL == 4)
    {
        ResetDataLV4();
        DrawWallLevel4();
    }

    DrawBoard(1, 1, WIDTH_CONSOLE, HEIGH_CONSOLE);   // Draw game
    GenerateFood();
    LEVELUP = 0;      // Reset when starting new game
}
void PauseGame(HANDLE t)
{
    SuspendThread(t);
}
void NextLevel()
{
    // tắt cổng của level cũ
    IS_GATE_ON = 0;
    LEVELUP = 0;
    FOOD_INDEX = 0;
    start_char = 0;

    // âm thanh qua cổng (nếu có file gate.wav thì dùng, không thì bỏ dòng này)
    if (SOUND)
        PlaySound(L"gate.wav", NULL, SND_ASYNC);

    // nếu chưa tới level cuối thì tăng level
    if (LEVEL < 4)
    {
        LEVEL++;

        // reset dữ liệu cho level mới
        if (LEVEL == 1)      ResetDataLV1();
        else if (LEVEL == 2) ResetDataLV2();
        else if (LEVEL == 3) ResetDataLV3();
        else if (LEVEL == 4) ResetDataLV4();

        // vẽ lại màn chơi (khung + tường + rắn + thức ăn)
        DrawContinueGame();
        STATE = 1;   // tiếp tục chơi
    }
    else
    {
        // đã qua level cuối -> game over
        STATE = 0;
        GameOver();
    }
}

void SaveGame()
{
    // Draw the save game screen
    system("cls");
    DrawBoard(1, 1, WIDTH_CONSOLE, HEIGH_CONSOLE);
    SmallBoard();
    SetColor(11);

    // Top horizontal line
    GotoXY(20, 4);
    for (int i = 0; i < 53; i++)
        cout << (char)196;

    // Bottom horizontal line
    GotoXY(20, 6);
    for (int i = 0; i < 53; i++)
        cout << (char)196;

    // Two vertical lines
    for (int i = 0; i < 20; i++)
    {
        GotoXY(45, 4 + i);
        cout << (char)179;
    }

    SetColor(14);
    GotoXY(20, 5);
    cout << "  YOUR SAVED GAME " << (char)2;
    GotoXY(46, 5);
    cout << " ENTER NAME TO SAVE " << (char)1;

    GotoXY(46, 7);
    cout << "Enter file name: ";

    // Print previously saved filenames
    FILE* file;
    fopen_s(&file, "namesaved.txt", "rt");
    char str[50];
    if (file != NULL)
    {
        fgets(str, 50, file);
        int i = 0;

        while (!feof(file))
        {
            GotoXY(29, 8 + i++);
            cout << str;
            fgets(str, 255, file);
        }
        fclose(file);
    }

    // Save the playing game
    GotoXY(51, 9);
    ShowCur(1);
    gets_s(str);

    if (SOUND)
        PlaySound(L"enter.wav", NULL, SND_ASYNC);

    fopen_s(&file, "namesaved.txt", "at");
    if (file != NULL)
    {
        fprintf(file, "%s\n", str);
        fclose(file);
    }

    strcat_s(str, ".txt");
    fopen_s(&file, str, "wt");
    if (file != NULL)
    {
        // Ghi 9 số nguyên, MOVING cũng là int
        fprintf(file, "%d %d %d %d %d %d %d %d %d\n",
            CHAR_LOCK, MOVING, SPEED, STATE, LEVEL,
            LEVELUP, temp, SCORE, SNAKE_COLOR);

        fprintf(file, "%d ", SIZE_SNAKE);

        for (int i = 0; i < SIZE_SNAKE; i++)
        {
            fprintf(file, "%d %d ", snake[i].x, snake[i].y);
        }

        fprintf(file, "\n%d ", FOOD_INDEX);

        for (int i = 0; i < MAX_SIZE_FOOD; i++)
        {
            fprintf(file, "%d %d ", food[i].x, food[i].y);
        }

        fclose(file);
    }

    ShowCur(0);
    GotoXY(49, 15);
    cout << "SAVING...";
    Sleep(1500);

    DrawContinueGame();  // redraw the paused game
}
void LoadGame()
{
    system("cls");
    DrawBoard(1, 1, WIDTH_CONSOLE, HEIGH_CONSOLE);
    SmallBoard();
    SetColor(11);

    GotoXY(25, 5);
    cout << "ENTER FILE NAME TO LOAD : ";

    // --- TỰ NHẬP TÊN FILE BẰNG _getch() ĐỂ BẮT PHÍM ESC ---
    char name[260] = "";
    int len = 0;

    int inputX = 25;
    int inputY = 7;

    GotoXY(inputX, inputY);
    ShowCur(1);

    while (true)
    {
        int c = _getch();

        if (c == 27)  // ESC -> HỦY LOAD
        {
            ShowCur(0);
            interf = MENU;      // hoặc giữ nguyên trạng thái tùy bạn
            return;
        }
        else if (c == 13) // ENTER
        {
            name[len] = '\0';
            break;
        }
        else if (c == 8)  // BACKSPACE
        {
            if (len > 0)
            {
                len--;
                name[len] = '\0';
                GotoXY(inputX + len, inputY);
                cout << ' ';
                GotoXY(inputX + len, inputY);
            }
        }
        else if (c >= 32 && c <= 126) // ký tự in được
        {
            if (len < 255)
            {
                name[len++] = (char)c;
                cout << (char)c;
            }
        }
    }

    ShowCur(0);

    // Nếu không nhập gì -> xem như HỦY
    if (len == 0)
    {
        interf = MENU;
        return;
    }

    // Ghép thêm .txt vào tên file
    char filename[270];
    strcpy_s(filename, name);
    strcat_s(filename, ".txt");

    FILE* f = nullptr;
    fopen_s(&f, filename, "rt");
    if (f == nullptr)
    {
        GotoXY(25, 9);
        cout << "Cannot open save file!";
        GotoXY(25, 11);
        cout << "Press any key to return...";
        _getch();
        interf = MENU;
        return;
    }

    // Đọc dữ liệu đúng thứ tự bạn đã SAVE
    // LƯU Ý: SaveGame phải dùng 9 %d cho 9 biến:
    // fprintf(file, "%d %d %d %d %d %d %d %d %d\n", CHAR_LOCK, MOVING, SPEED, STATE, LEVEL, LEVELUP, temp, SCORE, SNAKE_COLOR);
    fscanf_s(f, "%d %d %d %d %d %d %d %d %d",
        &CHAR_LOCK,
        &MOVING,
        &SPEED,
        &STATE,
        &LEVEL,
        &LEVELUP,
        &temp,
        &SCORE,
        &SNAKE_COLOR);

    // HIỂN THỊ ĐIỂM SAU KHI ĐỌC FILE
    GotoXY(25, 9);
    cout << "PLAYER SCORE: " << SCORE;

    GotoXY(25, 11);
    cout << "Press any key to continue...";
    _getch();

    // Đọc độ dài rắn
    fscanf_s(f, "%d", &SIZE_SNAKE);

    // Toạ độ từng đốt rắn
    for (int i = 0; i < SIZE_SNAKE; ++i)
    {
        fscanf_s(f, "%d %d", &snake[i].x, &snake[i].y);
    }

    // FOOD_INDEX
    fscanf_s(f, "%d", &FOOD_INDEX);

    // Toạ độ mảng food
    for (int i = 0; i < MAX_SIZE_FOOD; ++i)
    {
        fscanf_s(f, "%d %d", &food[i].x, &food[i].y);
    }

    fclose(f);

    // Đảm bảo rắn ở trạng thái "sống" và đang trong game
    STATE = 1;
    start_char = 0;

    // Sau khi load xong:
    // - Nếu main của bạn kiểu: case LOADGAME: LoadGame(); InGame(1); break;
    //   thì InGame(1) sẽ chơi tiếp với dữ liệu đã load.
    DrawContinueGame();
}

void Eat()
{
    if (SOUND)
        PlaySound(L"eat (1).wav", NULL, SND_FILENAME | SND_ASYNC);


    SCORE += 5;

    // tăng tốc độ sau khi ăn
    if (SPEED < 70)          // bạn muốn tối đa bao nhiêu thì đổi số này
        SPEED += 2;

    // thêm 1 đốt mới ở vị trí food hiện tại
    snake[SIZE_SNAKE] = food[FOOD_INDEX];

    if (FOOD_INDEX == MAX_SIZE_FOOD - 1)
    {
        food[FOOD_INDEX] = { 0, 0 };
        LEVELUP = 1;
		IS_GATE_ON = 1;
    }
    else
    {
        FOOD_INDEX++;
        GenerateFood();
    }

    SIZE_SNAKE++;

    if (LEVELUP == 1)
    {
        if (SOUND)
            PlaySound(L"gate (1).wav", NULL, SND_FILENAME| SND_ASYNC);

        SetColor(3);
        if (LEVEL == 1) DrawGateLv1();
        else if (LEVEL == 2) DrawGateLv2();
        else if (LEVEL == 3) DrawGateLv3();
        else if (LEVEL == 4) DrawGateLv4();
    }
}
    
void ProcessDead()
{
    STATE = 0;
    SetColor(SNAKE_COLOR + 1);

    // vẽ lại thân rắn bằng kí tự trong Snake_Body
    for (int i = 0; i < SIZE_SNAKE; i++)
    {
        GotoXY(snake[i].x, snake[i].y);
        cout << Snake_Body[i];
    }

    if (SOUND)
        PlaySound(L"die (1).wav", NULL, SND_FILENAME| SND_ASYNC);

    // Animation of death
    short t = 500;
    for (int i = 0; i < SIZE_SNAKE; i++)
    {
        if (temp == 13)    // dùng giống PDF
            break;

        GotoXY(snake[i].x, snake[i].y);
        cout << ' ';
        Sleep(t);
        t = (short)(t / 1.5);
        if (t < 30)
            t = 30;
    }
}
void MoveUp()
{
    int nextX = snake[0].x;
    int nextY = snake[0].y - 1;

    if (ReachBodyUp() ||
        nextY == 1 ||
        (LEVEL == 2 && UpDeadLevel2()) ||
        (LEVEL == 3 && UpDeadLevel3()) ||
        (LEVEL == 4 && UpDeadLevel4()))
    {
        ProcessDead();
        return;
    }

    if (!IS_GATE_ON &&
        nextX == food[FOOD_INDEX].x &&
        nextY == food[FOOD_INDEX].y)
    {
        Eat();
    }

    for (int i = SIZE_SNAKE - 1; i > 0; --i)
        snake[i] = snake[i - 1];

    snake[0].x = nextX;
    snake[0].y = nextY;

    if (IS_GATE_ON &&
        snake[0].x == gate.x &&
        snake[0].y == gate.y)
    {
        NextLevel();
        return;
    }
}



void MoveRight()
{
    int nextX = snake[0].x + 1;
    int nextY = snake[0].y;

    // chết?
    if (ReachBodyRight() ||
        nextX == WIDTH_CONSOLE - 1 ||
        (LEVEL == 2 && RightDeadLevel2()) ||
        (LEVEL == 3 && RightDeadLevel3()) ||
        (LEVEL == 4 && RightDeadLevel4()))
    {
        ProcessDead();
        return;
    }

    // ăn mồi (chỉ khi chưa có gate)
    if (!IS_GATE_ON &&
        nextX == food[FOOD_INDEX].x &&
        nextY == food[FOOD_INDEX].y)
    {
        Eat();
    }

    // dồn thân
    for (int i = SIZE_SNAKE - 1; i > 0; --i)
        snake[i] = snake[i - 1];

    // đầu mới
    snake[0].x = nextX;
    snake[0].y = nextY;

    // đi vào gate?
    if (IS_GATE_ON &&
        snake[0].x == gate.x &&
        snake[0].y == gate.y)
    {
        NextLevel();
        return;
    }
}



void MoveLeft()
{
    int nextX = snake[0].x - 1;
    int nextY = snake[0].y;

    if (ReachBodyLeft() ||
        nextX == 1 ||
        (LEVEL == 2 && LeftDeadLevel2()) ||
        (LEVEL == 3 && LeftDeadLevel3()) ||
        (LEVEL == 4 && LeftDeadLevel4()))
    {
        ProcessDead();
        return;
    }

    if (!IS_GATE_ON &&
        nextX == food[FOOD_INDEX].x &&
        nextY == food[FOOD_INDEX].y)
    {
        Eat();
    }

    for (int i = SIZE_SNAKE - 1; i > 0; --i)
        snake[i] = snake[i - 1];

    snake[0].x = nextX;
    snake[0].y = nextY;

    if (IS_GATE_ON &&
        snake[0].x == gate.x &&
        snake[0].y == gate.y)
    {
        NextLevel();
        return;
    }
}

    

void MoveDown()
{
    int nextX = snake[0].x;
    int nextY = snake[0].y + 1;

    if (ReachBodyDown() ||
        nextY == HEIGH_CONSOLE - 1 ||
        (LEVEL == 2 && DownDeadLevel2()) ||
        (LEVEL == 3 && DownDeadLevel3()) ||
        (LEVEL == 4 && DownDeadLevel4()))
    {
        ProcessDead();
        return;
    }

    if (!IS_GATE_ON &&
        nextX == food[FOOD_INDEX].x &&
        nextY == food[FOOD_INDEX].y)
    {
        Eat();
    }

    for (int i = SIZE_SNAKE - 1; i > 0; --i)
        snake[i] = snake[i - 1];

    snake[0].x = nextX;
    snake[0].y = nextY;

    if (IS_GATE_ON &&
        snake[0].x == gate.x &&
        snake[0].y == gate.y)
    {
        NextLevel();
        return;
    }
}



void ThreadFunc()
{
    while (1)
    {
        if (STATE == 1) // If my snake is alive
        {
            SmallBoard();
            DrawSnakeAndFood(' ');   // xoá rắn + food cũ

            if (start_char > 0)
            {
                // Khi đi qua cổng thì chỉ cho đi thẳng
                MOVING = 'D';
            }

            switch (MOVING)
            {
            case 'A': MoveLeft();  break;
            case 'D': MoveRight(); break;
            case 'W': MoveUp();    break;
            case 'S': MoveDown();  break;
            }

            if (LEVELUP == 0)
            {
                // VẼ LẠI rắn + food bằng ký tự '0'
                DrawSnakeAndFood('0');
            }
            else if (LEVELUP == 1)
            {
                // Vẽ rắn khi đang chui qua cổng
                DrawSnakeAndFood('0', start_char);
            }

            Sleep(1000 / SPEED);
        }
        else
        {
            break;
        }
    }
}


void Menu()
{
    system("cls");
    ShowCur(0);          // Ẩn con trỏ
    SetColor(11);

    const char* items[] =
    {
        " NEW GAME",
        " LOAD GAME",
        " SETTING",
        " INTRODUCTION",
        " QUIT GAME"
    };

    int totalItems = 5;
    int select = 0;            // mục đang chọn
    int x = 50, y = 12;        // vị trí hiển thị menu

    while (1)
    {
        // --- VẼ TITLE ---
        SetColor(10);
        GotoXY(43, 5);
        cout << "======= S N A K E   G A M E =======";

        // --- IN MENU ---
        for (int i = 0; i < totalItems; i++)
        {
            if (i == select)
            {
                SetColor(14);          // highlight
                GotoXY(x - 3, y + i);
                cout << ">> " << items[i];
            }
            else
            {
                SetColor(7);
                GotoXY(x - 3, y + i);
                cout << "   " << items[i];
            }
        }

        // --- NHẬN PHÍM ---
        char key = _getch();

        if (key == 'w' || key == 'W' || key == 72)      // UP
        {
            select--;
            if (select < 0) select = totalItems - 1;
        }
        else if (key == 's' || key == 'S' || key == 80) // DOWN
        {
            select++;
            if (select >= totalItems) select = 0;
        }
        else if (key == 13) // ENTER
        {
            switch (select)
            {
            case 0: interf = INGAME; return;       // NEW GAME
            case 1: interf = LOADGAME; return;     // LOAD GAME
            case 2: interf = SETTING; return;      // SETTING
            case 3: interf = INFORMATION; return;  // INTRO
            case 4: interf = QUITGAME; return;     // QUIT
            }
        }
    }
}
void InGame(int oldgame)
{
    ShowCur(0);

    if (oldgame == 0)   // NEW GAME thật sự
    {
        system("cls");

        // RESET toàn bộ dữ liệu game
        ResetDataLV1();
        STATE = 1;
        MOVING = 'D';
        CHAR_LOCK = 'D';
        LEVEL = 1;
        SCORE = 0;
        LEVELUP = 0;
        IS_GATE_ON = 0;
        FOOD_INDEX = 0;

        DrawBoard(1, 1, WIDTH_CONSOLE, HEIGH_CONSOLE);
        SmallBoard();
        DrawSnakeAndFood('0', 0);
    }
    else  // load game
    {
        DrawContinueGame();
    }

    // Thread rắn tự chạy
    HANDLE t = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFunc, NULL, 0, NULL);

    while (true)
    {
        if (STATE == 0)
        {
            TerminateThread(t, 0);
            CloseHandle(t);
            interf = GAMEOVER;
            return;
        }

        char key = _getch();

        if ((key == 'A' || key == 'a' || key == 75) && CHAR_LOCK != 'D')
        {
            MOVING = 'A';
            CHAR_LOCK = 'A';
        }
        else if ((key == 'D' || key == 'd' || key == 77) && CHAR_LOCK != 'A')
        {
            MOVING = 'D';
            CHAR_LOCK = 'D';
        }
        else if ((key == 'W' || key == 'w' || key == 72) && CHAR_LOCK != 'S')
        {
            MOVING = 'W';
            CHAR_LOCK = 'W';
        }
        else if ((key == 'S' || key == 's' || key == 80) && CHAR_LOCK != 'W')
        {
            MOVING = 'S';
            CHAR_LOCK = 'S';
        }
        else if (key == 'P' || key == 'p')
        {
            PauseGame(t);
        }
        else if (key == 'T' || key == 't')
        {
            PauseGame(t);
            SaveGame();
            STATE = 1;
        }
        else if (key == 'L' || key == 'l')
        {
            PauseGame(t);
            LoadGame();
            TerminateThread(t, 0);
            CloseHandle(t);
            interf = LOADGAME;
            return;
        }
        else if (key == 27) // ESC
        {
            TerminateThread(t, 0);
            CloseHandle(t);
            interf = MENU;
            return;
        }
    }
}


void GameOver()
{
    system("cls");
    ShowCur(0);

    SetColor(12);
    GotoXY(45, 10);
    cout << "===== GAME OVER =====";

    SetColor(14);
    GotoXY(42, 12);
    cout << "Your Score: " << SCORE;

    SetColor(7);
    GotoXY(38, 15);
    cout << "Press ENTER to return to MENU";

    // Reset một số biến để chuẩn bị chơi lại
    SIZE_SNAKE = 6;
    LEVEL = 1;
    LEVELUP = 0;
    SCORE = 0;
    MOVING = ' ';

    while (true)
    {
        if (_getch() == 13)  // Enter
        {
            interf = MENU;
            return;
        }
    }
}
void QuitGame()
{
    system("cls");
    ShowCur(0);

    SetColor(12);
    GotoXY(45, 10);
    cout << "QUIT GAME?";

    SetColor(7);
    GotoXY(40, 12);
    cout << "Press Y to exit, N to cancel.";

    while (true)
    {
        char k = _getch();
        if (k == 'y' || k == 'Y')
        {
            exit(0);
        }
        else if (k == 'n' || k == 'N')
        {
            interf = MENU;
            return;
        }
    }
}
void Information()
{
    system("cls");
    ShowCur(0);
    SetColor(11);

    GotoXY(40, 5);  cout << "===== INFORMATION =====";

    SetColor(14);
    GotoXY(30, 8);  cout << "Lecturer : Truong Toan Thinh ";
    GotoXY(30, 9);  cout << "Group    : 5 - Hunting Snake ";
    GotoXY(30, 10); cout << "Members  : 23120406 -Phan Cong Vinh";
	GotoXY(30, 11); cout << "           23120363 - Dao Ngoc Tho";
	GotoXY(30, 12); cout << "           23120375 - Le Duc Toan ";
    SetColor(11);
    GotoXY(30, 13); cout << "Controls:";
    GotoXY(32, 14); cout << "W - Move Up";
    GotoXY(32, 15); cout << "S - Move Down";
    GotoXY(32, 16); cout << "A - Move Left";
    GotoXY(32, 17); cout << "D - Move Right";
    GotoXY(32, 18); cout << "P - Pause Game";

    SetColor(7);
    GotoXY(35, 22);
    cout << "Press ENTER to return to MENU";

    while (true)
        if (_getch() == 13)
        {
            interf = MENU;
            return;
        }
}
void SetSnakeColor()
{
    system("cls");
    ShowCur(1);
    SetColor(11);

    GotoXY(40, 10);
    cout << "Choose Snake Color (1-7): ";

    int c;
    cin >> c;

    if (c >= 1 && c <= 7)
        SNAKE_COLOR = c;
    else
        SNAKE_COLOR = 2; // default

    interf = MENU;
}
void SetSpeed()
{
    system("cls");
    ShowCur(1);
    SetColor(11);

    GotoXY(40, 10);
    cout << "Enter Speed (1-10): ";

    int sp;
    cin >> sp;

    if (sp < 1) sp = 1;
    if (sp > 10) sp = 10;

    SPEED = sp;

    interf = MENU;
}
void SetSound()
{
    system("cls");
    ShowCur(1);
    SetColor(11);

    GotoXY(40, 10);
    cout << "Sound (1 = ON, 0 = OFF): ";

    int s;
    cin >> s;

    // Chỉ nhận giá trị 0 hoặc 1
    if (s != 0 && s != 1)
        s = 1;

    SOUND = s;

    // Nếu SOUND = 1 → bật nhạc nền lại
    if (SOUND == 1)
    {
        PlaySound(L"bg.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }
    else
    {
        // Nếu SOUND = 0 → tắt toàn bộ âm
        PlaySound(NULL, 0, 0);
    }

    interf = MENU;
}

void Setting()
{
    system("cls");
    ShowCur(0);
    SetColor(14);

    const char* setitems[] =
    {
        " SET SNAKE COLOR",
        " SET SPEED",
        " SET SOUND",
        " BACK TO MENU"
    };

    int select = 0;
    int total = 4;
    int x = 50, y = 12;

    while (1)
    {
        system("cls");
        GotoXY(45, 6);
        SetColor(10);
        cout << "===== SETTING =====";

        for (int i = 0; i < total; i++)
        {
            if (i == select)
            {
                SetColor(14);
                GotoXY(x - 3, y + i);
                cout << ">> " << setitems[i];
            }
            else
            {
                SetColor(7);
                GotoXY(x - 3, y + i);
                cout << "   " << setitems[i];
            }
        }

        char key = _getch();

        if (key == 'w' || key == 'W' || key == 72)
            select--;
        else if (key == 's' || key == 'S' || key == 80)
            select++;
        else if (key == 13)
        {
            switch (select)
            {
            case 0: SetSnakeColor(); return;
            case 1: SetSpeed(); return;
            case 2: SetSound(); return;
            case 3: interf = MENU; return;
            }
        }

        if (select < 0) select = total - 1;
        if (select >= total) select = 0;
    }
}

