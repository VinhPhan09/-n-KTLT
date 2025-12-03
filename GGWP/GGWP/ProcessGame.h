#pragma once
#include "System.h"
#include "Draw.h"
#include "Dead.h"
#include "Prepare.h"

void StartGame();
void PauseGame(HANDLE t);
void SaveGame();
void LoadGame();
void Eat();
void ProcessDead();
void MoveLeft();
void MoveRight();
void MoveUp();
void MoveDown();
void NextLevel();

void ThreadFunc();
void Menu();
void InGame(int oldgame = 0);
void GameOver();
void QuitGame();
void Information();

void SetSnakeColor();
void SetSpeed();
void SetSound();
void Setting();

