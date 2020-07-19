#include "pathfinding.h"

/**
 * dfs_graph - traverse graph until target_content found
 * @q: pointer to q to populate
 * @visited: array specifying if vertex has been visited
 * @cur: pointer to current vertex node
 * @target_content: string to search for
 *
 * Return: queue containing nodes from start to target or NULL on error
 */
queue_node_t *dfs_graph(queue_t *q, int *visited, const vertex_t *cur,
		char *target_content)
{
	edge_t *e;

	if (cur == NULL || visited[cur->index] == 1)
		return (NULL);
	printf("Checking %s\n", cur->content);
	if (!strcmp(cur->content, target_content))
		return (queue_push_front(q, strdup(cur->content)));
	visited[cur->index] = 1;
	for (e = cur->edges; e != NULL; e = e->next)
		if (dfs_graph(q, visited, e->dest, target_content))
			return (queue_push_front(q, strdup(cur->content)));
	return (NULL);
}

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
	int *visited;

	if (!graph || !start || !target)
		return (NULL);
	q = queue_create();
	if (q == NULL)
		return (NULL);
	visited = calloc(graph->nb_vertices, sizeof(*visited));
	if (visited == NULL)
		return (NULL);
	if (dfs_graph(q, visited, start, target->content) == NULL)
	{
		queue_delete(q);
		q = NULL;
	}
	free(visited);
	return (q);
}
