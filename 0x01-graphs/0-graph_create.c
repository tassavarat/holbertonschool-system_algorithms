#include "graphs.h"

/**
 * graph_create - allocate memory for graph_t and initialises its contents
 *
 * Return: pointer to allocated structure, NULL on failure
 */
graph_t *graph_create(void)
{
	graph_t *graph = malloc(sizeof(*graph));

	if (!graph)
		return (NULL);
	graph->nb_vertices = 0;
	graph->vertices = NULL;
	return (graph);
}
