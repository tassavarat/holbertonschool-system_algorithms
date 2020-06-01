#include "graphs.h"

/**
 * dfs - traverse graph using depth-first algorithm
 * @v: pointer vertex node being visited
 * @visited: array specifying if vertex has been visited
 * @action: function pointer to be called for each visited vertex
 * @depth: current depth
 * @max_depth: max depth reached during traversal
 */
void dfs(vertex_t *v, int *visited,
		void (*action)(const vertex_t *v, size_t depth), size_t depth,
		size_t *max_depth)
{
	edge_t *e;

	if (!v || visited[v->index])
		return;
	visited[v->index] = 1;
	action(v, depth);
	if (depth > *max_depth)
		*max_depth = depth;
	++depth;
	for (e = v->edges; e; e = e->next)
		dfs(e->dest, visited, action, depth, max_depth);
}

/**
 * depth_first_traverse - goes through a graph using depth-first algorithm
 * @graph: pointer to graph to traverse
 * @action: function pointer to be called for each visited vertex
 *	    v: pointer to visited vertex
 *	    depth: depth of v
 *
 * Return: greatest vertex depth, 0 on failure
 */
size_t depth_first_traverse(const graph_t *graph,
		void (*action)(const vertex_t *v, size_t depth))
{
	int *visited;
	size_t max_depth;

	if (!graph || !action || !graph->nb_vertices)
		return (0);
	visited = calloc(graph->nb_vertices, sizeof(*visited));
	if (!visited)
		return (0);
	max_depth = 0;
	dfs(graph->vertices, visited, action, 0, &max_depth);
	free(visited);
	return (max_depth);
}
