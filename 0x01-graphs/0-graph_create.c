#include "graphs.h"

/**
 * graph_create - allocate memory for graph_t and initialises its contents
 *
 * Return: pointer to allocated structure, NULL on failure
 */
graph_t *graph_create(void)
{
	graph_t *new = malloc(sizeof(*new));

	if (!new)
		return (NULL);
	new->nb_vertices = 0;
	new->vertices = NULL;
	return (new);
}
