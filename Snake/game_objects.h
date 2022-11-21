#define DEFAULT_SNAKE {{8, 10}, {9, 10}, {10, 10}}

#define DIRECTION_RIGHT 0
#define DIRECTION_LEFT 1
#define DIRECTION_UP 2
#define DIRECTION_DOWN 3

typedef struct
{
	int** coords;
	size_t size;
} Snake;

const int default_snake[3][2] = DEFAULT_SNAKE;
const size_t DEFAULT_SNAKE_SIZE = 3;


typedef struct
{
	int x;
	int y;
} Food;