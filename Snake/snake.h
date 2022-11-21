#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>

#include "keys.h"
#include "game_objects.h"

const size_t FIELD_SIZE = 20;

bool** InitField();
void GenerateFood();
void GenerateSnake();
void DeleteSnake();

void PrintField(bool** field, HANDLE consoleHandle);
void MoveLeft(bool** field);
void MoveRighth(bool** field);
void MoveDown(bool** field);
void MoveUp(bool** field);
void MoveForvard(bool** field, int direction);
int MeetBorder(bool** field);
int EatFood(bool** field);
void GrowUp();
void PrintGameOver();

hidecursor();
setcur(int x, int y);


