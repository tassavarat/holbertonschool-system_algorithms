#include "pathfinding.h"

/**
 * backtracking_graph - find first path from starting to target in a graph
 * @graph: pointer to graph being searched
 * @start: pointer to starting vertex
 * @target: pointer to target vertex
 *
 * Return: queue containing nodes from start to target or NULL on error
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
		vertex_t const *target)
{
	queue_t *q;

	if (!graph || !start || !target)
		return (NULL);
	return (q);
}
