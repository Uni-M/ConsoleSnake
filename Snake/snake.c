#include "Snake.h"

Snake snake;
Food food;

int main()
{
	srand(time(NULL));
	hidecursor();
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	

	int score = 0;
	bool in_game = true;
	bool pause = false;
	int direction = DIRECTION_RIGHT;

	bool** field = InitField();


	GenerateFood();
	GenerateSnake();

	clock_t start = clock(), diff;

	while (in_game)
	{
		SetConsoleTextAttribute(consoleHandle, 11);
		printf("=======================================\n");
		printf("                 SNAKE                 \n");
		printf("             SCORE........%d\n", score);
		printf("=======================================\n");

		PrintField(field, consoleHandle);

		char c = (_kbhit()) ? _getch() : -1;
		diff = clock() - start;

		if      (c == KEY_MOVE_LEFT)  MoveLeft(field);
		else if (c == KEY_MOVE_RIGHT) MoveRighth(field);
		else if (c == KEY_MOVE_DOWN)  MoveDown(field);
		else if (c == KEY_MOVE_UP)    MoveUp(field);
		else if (c == KEY_QUIT)       in_game = false;
		else if (c == KEY_PAUSE)      pause = true;
		else
		{
			if (diff > 1000)
			{
				MoveForvard(field, direction);
				start = clock();
			}
		}

		if (MeetBorder(field) == 0)
		{
			in_game = false;
			PrintGameOver();
			DeleteSnake();
			continue;
		}

		if (EatFood(field) == 0)
		{
			score += 1;
			GenerateFood();
			GrowUp();
		}

		Sleep(500);
		setcur(0, 0);

	}

	return 0;
}

bool** InitField()
{
	bool** field = (bool**)calloc(FIELD_SIZE, sizeof(bool*));

	for (int i = 0; i < FIELD_SIZE; ++i)
	{
		field[i] = (bool*)calloc(FIELD_SIZE, sizeof(bool));
	}

	return field;
}

void GenerateFood()
{
	food.x = rand() % (FIELD_SIZE - 1);
	food.y = rand() % (FIELD_SIZE - 1);
}

void GenerateSnake()
{
	int** a = (int**)malloc(DEFAULT_SNAKE_SIZE + sizeof(int*));
	for (int i = 0; i < DEFAULT_SNAKE_SIZE; ++i)
	{
		a[i] = (int*)malloc(2 * sizeof(int));
		for (int j = 0; j < 2; ++j)
		{
			a[i][j] = default_snake[i][j];
		}
	}
	
	snake.coords = a;
	snake.size = DEFAULT_SNAKE_SIZE;
}

void PrintField(bool** field, HANDLE consoleHandle)
{
	SetConsoleTextAttribute(consoleHandle, 14);

	int** arr = snake.coords;
	size_t size = snake.size;
	

	for (int i = 0; i < FIELD_SIZE; ++i)
	{
		for (int j = 0; j < FIELD_SIZE; ++j)
		{
			int s = 0;
			for (int k = 0; k < size; ++k)
			{
				if (arr[k][1] == i && arr[k][0] == j)
				{
					s = 1;
				}
			}

			if (s == 1)
			{
				SetConsoleTextAttribute(consoleHandle, 10);
				printf("O ");
				SetConsoleTextAttribute(consoleHandle, 14);
			}
			else if (i == food.y && j == food.x)
			{
				SetConsoleTextAttribute(consoleHandle, 12);
				printf("@ ");
				SetConsoleTextAttribute(consoleHandle, 14);
			}
			else
			{
				printf("- ");
			}
		}
		printf("\n");
	}
}

void MoveLeft(bool** field)
{

}

void MoveRighth(bool** field)
{

}

void MoveDown(bool** field)
{

}

void MoveUp(bool** field)
{

}

void MoveForvard(bool** field, int direction)
{
	for (int i = 0; i < snake.size - 1; ++i)
	{
		snake.coords[i][0] = snake.coords[i + 1][0];
		snake.coords[i][1] = snake.coords[i + 1][1];
	}

	if (direction == 0)
	{
		snake.coords[snake.size - 1][0] += 1;
	}
	if (direction == 1)
	{
		snake.coords[snake.size - 1][0] -= 1;
	}
	if (direction == 2)
	{
		snake.coords[snake.size - 1][1] += 1;
	}
	if (direction == 3)
	{
		snake.coords[snake.size - 1][1] -= 1;
	}

}

int MeetBorder(bool** field)
{

}

int EatFood(bool** field)
{

}

void GrowUp()
{

}

void DeleteSnake()
{
	for (int i = 0; i < snake.size; i++)
	{
		free(snake.coords[i]);
	}
	free(snake.coords);
}

void PrintGameOver()
{

}

hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

setcur(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}