#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "graphs.h"
#include "queues.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct vertex_queue_s - queue used for Dijkstra's algorithm
 * @vq_src: pointer to source vertex queue node
 * @dest: pointer to destination vertex node
 * @weight: weight of going from src to dest
 * @next: pointer to next queue node
 */
typedef struct vertex_queue_s
{
	struct vertex_queue_s *vq_src;
	vertex_t *dest;
	int weight;
	struct vertex_queue_s *next;
} vertex_queue_t;

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
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
		vertex_t const *target);
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
		vertex_t const *target);

#endif /* PATHFINDING_H */
