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
	Direction direction = DIRECTION_RIGHT;

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

		if      (c == KEY_MOVE_LEFT)  MoveLeft(&direction);
		else if (c == KEY_MOVE_RIGHT) MoveRight(&direction);
		else if (c == KEY_MOVE_DOWN)  MoveDown(&direction);
		else if (c == KEY_MOVE_UP)    MoveUp(&direction);
		else if (c == KEY_QUIT)       in_game = false;
		else if (c == KEY_PAUSE)      pause = true;
		else
		{
			if (diff > 500)
			{
				MoveForvard(field, direction);
				start = clock();
			}
		}

		if (MeetBorder(direction) == 1)
		{
			in_game = false;
			PrintGameOver();
			DeleteSnake();
			continue;
		}

		if (EatFood(direction) == 1)
		{
			score += 1;
			GrowUp();
			GenerateFood();
		}

		Sleep(100);
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
	int** a = (int**)malloc(DEFAULT_SNAKE_SIZE * sizeof(int*));
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

void MoveLeft(int* direction)
{
	if (*direction != DIRECTION_RIGHT) *direction = DIRECTION_LEFT;
}

void MoveRight(int* direction)
{
	if (*direction != DIRECTION_LEFT) *direction = DIRECTION_RIGHT;
}

void MoveDown(int* direction)
{
	if (*direction != DIRECTION_UP) *direction = DIRECTION_DOWN;
}

void MoveUp(int* direction)
{

	if (*direction != DIRECTION_DOWN) *direction = DIRECTION_UP;
}

void MoveForvard(bool** field, Direction direction)
{
	for (int i = 0; i < snake.size - 1; ++i)
	{
		snake.coords[i][0] = snake.coords[i + 1][0];
		snake.coords[i][1] = snake.coords[i + 1][1];
	}

	if (direction == DIRECTION_RIGHT)  snake.coords[snake.size - 1][0] += 1;
	if (direction == DIRECTION_LEFT)   snake.coords[snake.size - 1][0] -= 1;
	if (direction == DIRECTION_UP)     snake.coords[snake.size - 1][1] -= 1;
	if (direction == DIRECTION_DOWN)   snake.coords[snake.size - 1][1] += 1;

}

int MeetBorder(Direction direction)
{

	if (direction == DIRECTION_RIGHT &&
		snake.coords[snake.size - 1][0] == FIELD_SIZE)
		return 1;
	else if (direction == DIRECTION_LEFT &&
		snake.coords[snake.size - 1][0] < 0)
		return 1;
	else if (direction == DIRECTION_UP &&
		snake.coords[snake.size - 1][1] < 0)
		return 1;
	else if (direction == DIRECTION_DOWN &&
		snake.coords[snake.size - 1][1] == FIELD_SIZE)
		return 1;
	

	for (int i = snake.size-1; i > 1; --i) // TODO need to be fixed
	{
		if (i > 4 && snake.coords[0][0] == snake.coords[i][0] && snake.coords[0][1] == snake.coords[i][1])
		{
			return 1;
		}
	}

	return 0;
}

int EatFood(Direction direction)
{
	if (direction == DIRECTION_RIGHT &&
		snake.coords[snake.size - 1][0] + 1 == food.x &&
		snake.coords[snake.size - 1][1] == food.y)
		return 1;
	else if (direction == DIRECTION_LEFT &&
		snake.coords[snake.size - 1][0] - 1 == food.x &&
		snake.coords[snake.size - 1][1] == food.y)
		return 1;
	else if (direction == DIRECTION_UP &&
		snake.coords[snake.size - 1][0] == food.x &&
		snake.coords[snake.size - 1][1] - 1 == food.y)
		return 1;
	else if (direction == DIRECTION_DOWN &&
		snake.coords[snake.size - 1][0] == food.x &&
		snake.coords[snake.size - 1][1] + 1 == food.y)
		return 1;
	return 0;
}

void GrowUp()
{
	size_t new_size = snake.size + 1;

	int** a = (int**)realloc(snake.coords, new_size * sizeof(int*));
	for (int i = 0; i < snake.size; ++i)
	{
		a[i] = (int*)realloc(snake.coords[i], 2 * sizeof(int));
	}
	a[snake.size] = (int*)malloc(2 * sizeof(int));

	a[snake.size][0] = food.x;
	a[snake.size][1] = food.y;

	snake.coords = a;
	snake.size = new_size;

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
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle, 12);
	printf("=======================================\n");
	printf("                GAME OVER              \n");
	printf("=======================================\n");
	SetConsoleTextAttribute(consoleHandle, 14);
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