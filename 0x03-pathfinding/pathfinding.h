#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "queues.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * enum cardinal_dir - cardinal direction indexes for dir array
 * @EAST: east index
 * @SOUTH: south index
 * @WEST: west index
 * @NORTH: north index
 * @SIZE: size of dir array
 */
enum cardinal_dir
{
	EAST,
	SOUTH,
	WEST,
	NORTH,
	SIZE
};

/**
 * struct point_s - Structure storing coordinates
 *
 * @x: X coordinate
 * @y: Y coordinate
 */
typedef struct point_s
{
	int x;
	int y;
} point_t;

queue_t *backtracking_array(char **map, int rows, int cols,
		point_t const *start, point_t const *target);

#endif /* PATHFINDING_H */
