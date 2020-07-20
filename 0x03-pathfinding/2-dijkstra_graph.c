#include "pathfinding.h"

queue_t *bfs_graph(queue_t *bfs_q, int *visited, const vertex_t *start,
		char *target_content)
{
	edge_t *e;
	size_t i;

	visited[start->index] = 1;
	printf("%s\n", start->content);
	e = start->edges;
	if (e == NULL)
		return (NULL);
	do {
		if (e)
		{
			if (visited[e->dest->index] == 0)
			{
				if (queue_push_back(bfs_q, e->dest) == NULL)
					return (NULL);
				visited[e->dest->index] = 1;
				/* for (i = 0; i < 10; ++i) */
				/* 	printf("%i ", visited[i]); */
				printf("pushing: %s\n", e->dest->content);
			}
			e = e->next;
		}
		else
		{
			puts("else");
			for (e = ((vertex_t *)bfs_q->front->ptr)->edges;
					e && visited[e->dest->index] == 1;
					e = e->next)
				printf("e: %s\n", e->dest->content);
			printf("popping: %s\n", ((vertex_t *)bfs_q->front->ptr)->content);
			free(dequeue(bfs_q));
		}
	} while(bfs_q->front != NULL);
	return (NULL);
}

/**
 * dijkstra_graph - search for shortest path from start to target in graph
 * @graph: pointer to graph to search
 * @start: pointer to starting vertex
 * @target: pointer to target vertex
 *
 * Return: queue with content string of stortest path from start to target node
 * or NULL on error
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
		vertex_t const *target)
{
	queue_t *bfs_q, *path;
	int *visited;

	if (!graph || !start || !target)
		return (NULL);
	bfs_q = queue_create();
	if (bfs_q == NULL)
		return (NULL);
	visited = calloc(graph->nb_vertices, sizeof(*visited));
	if (visited == NULL)
		return (NULL);
	if (bfs_graph(bfs_q, visited, start, target->content) == NULL)
	{
		queue_delete(bfs_q);
		bfs_q = NULL;
	}
	free(visited);
	return (path);
}
