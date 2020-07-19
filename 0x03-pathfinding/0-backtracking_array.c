#include "pathfinding.h"

/**
 * free_2d - free memory allocated for 2-D array
 * @a: 2-D array to free
 * @size: size of 2-D array
 */
void free_2d(int **a, int size)
{
	while (size)
		free(a[--size]);
	free(a);
}

/**
 * queue_wrapper - wrapper used to call queue_push_front
 * @q: queue to push into
 * @x: point x coordinate
 * @y: point y coordinate
 *
 * Return: 0 on success, 1 on failure
 */
int queue_wrapper(queue_t *q, int x, int y)
{
	point_t *pt;

	pt = malloc(sizeof(*pt));
	if (pt == NULL)
		return (1);
	pt->x = x, pt->y = y;
	if (queue_push_front(q, pt) == NULL)
		return (1);
	return (0);
}

/**
 * dfs_array - traverse through array until target coordinates found
 * @q: pointer to queue to populate
 * @dir: pointer to array containing x-y cardinal directions
 * @visited: array containing visited coordinates represented as 1's
 * @map: pointer to 2-D array to search
 * @rows: number of rows in map
 * @cols: number of columns in map
 * @x: current x position
 * @y: current y position
 * @target: pointer to x-y target coordinates
 *
 * Return: 0 on success, 1 on failure
 */
int dfs_array(queue_t *q, point_t *dir, int **visited, char **map, int rows,
		int cols, int x, int y, point_t const *target)
{
	int i;

	if (x < 0 || x >= cols || y < 0 || y >= rows || map[y][x] == '1' ||
			visited[y][x] == 1)
		return (1);
	printf("Checking coordinates [%i, %i]\n", x, y);
	if (x == target->x && y == target->y)
		return (queue_wrapper(q, x, y));
	visited[y][x] = 1;
	for (i = 0; i < SIZE; ++i)
		if (dfs_array(q, dir, visited, map, rows, cols, x + dir[i].x,
					y + dir[i].y, target) == 0)
			return (queue_wrapper(q, x, y));
	return (1);
}

/**
 * init - initialise relevant variables
 * @q: double pointer to queue being allocated
 * @dir: pointer to array to initialise
 * @visited: double array
 * @rows: rows in visited array
 * @cols: columns in visited array
 *
 * Return: 0 on success, 1 on failure
 */
int init(queue_t **q, point_t *dir, int ***visited, int rows, int cols)
{
	int i;

	*q = queue_create();
	if (*q == NULL)
		return (1);
	dir[EAST].x = 1, dir[EAST].y = 0;
	dir[SOUTH].x = 0, dir[SOUTH].y = 1;
	dir[WEST].x = -1, dir[WEST].y = 0;
	dir[NORTH].x = 0, dir[NORTH].y = -1;
	*visited = malloc(rows * sizeof(**visited));
	if (*visited == NULL)
		return (1);
	for (i = 0; i < rows; ++i)
	{
		(*visited)[i] = calloc(cols, sizeof(***visited));
		if ((*visited)[i] == NULL)
			return (1);
	}
	return (0);
}

/**
 * backtracking_array - find first path from starting to target in 2-D array
 * @map: pointer to read-only 2-D array where 0 represents walkable cell
 * and 1 represents blocked cell
 * @rows: number of rows in map
 * @cols: number of columns in map
 * @start: coordinates of starting point
 * @target: coordinates of target point
 *
 * Return: queue containing nodes from start to target or NULL on error
 */
queue_t *backtracking_array(char **map, int rows, int cols,
		point_t const *start, point_t const *target)
{
	queue_t *q;
	int **visited;
	point_t dir[SIZE];

	if (!map || rows < 1 || cols < 1 || !start || !target)
		return (NULL);
	if (init(&q, dir, &visited, rows, cols) == 1)
		return (NULL);
	if (dfs_array(q, dir, visited, map, rows, cols, start->x, start->y,
				target) == 1)
	{
		queue_delete(q);
		q = NULL;
	}
	free_2d(visited, rows);
	return (q);
}
