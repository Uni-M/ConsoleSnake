#define DEFAULT_SNAKE {{8, 10}, {9, 10}, {10, 10}}

typedef struct
{
	int** coords;
	size_t size;
} Snake;

const int default_snake[3][2] = DEFAULT_SNAKE;
const size_t DEFAULT_SNAKE_SIZE = 3;

typedef enum
{
	DIRECTION_RIGHT,
	DIRECTION_LEFT,
	DIRECTION_UP,
	DIRECTION_DOWN
} Direction;


typedef struct
{
	int x;
	int y;
} Food;