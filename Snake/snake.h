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
void MoveLeft(int* direction);
void MoveRight(int* direction);
void MoveDown(int* direction);
void MoveUp(int* direction);
void MoveForvard(bool** field, Direction direction);
int MeetBorder(Direction direction);
int EatFood(Direction direction);
void GrowUp();
void PrintGameOver();

hidecursor();
setcur(int x, int y);


