#include "pathfinding.h"

/**
 * _dequeue - free the head node of a queue
 * @q: pointer to head of queue
 */
void _dequeue(queue_t *q)
{
	queue_node_t *tmp;

	if (q)
	{
		tmp = q->front;
		q->front = q->front->next;
		free(tmp);
	}
}

queue_t *find_path(queue_t *path, pqueue_t *pq, edge_t *src, edge_t *e,
		const vertex_t *start, char *target_content)
{
	pqueue_t *new_pq, *cur_pq;
	edge_t *cur_e;

	/* printf("pushing: %s\n", e->dest->content); */
	/* return (path); */
	new_pq = malloc(sizeof(*new_pq));
	if (new_pq == NULL)
		return (NULL);
	new_pq->dest = e;
	new_pq->src = src;
	new_pq->next = NULL;
	new_pq->weight = e->weight;
	printf("Checking %s, distance from %s is %i\n", new_pq->dest->dest->content, new_pq->src->dest->content, new_pq->weight);
	for (cur_pq = pq; cur_pq->next && new_pq->weight > cur_pq->next->weight;
			cur_pq = cur_pq->next)
		;
	if (cur_pq->next != NULL)
		new_pq->next = cur_pq->next;
	cur_pq->next = new_pq;
	for (cur_pq = pq; cur_pq; cur_pq = cur_pq->next)
		printf("dest: %s src: %s (%i)\n", cur_pq->dest->dest->content, cur_pq->src->dest->content, cur_pq->weight);
	putchar('\n');
	return (path);
}

queue_t *bfs_graph(queue_t *path, pqueue_t *pq, int *visited,
		const vertex_t *start, char *target_content)
{
	queue_t *bfs_q;
	edge_t *e, *src;

	bfs_q = queue_create();
	if (bfs_q == NULL)
		return (NULL);
	visited[start->index] = 1;
	/* printf("%s\n", start->content); */
	e = start->edges;
	if (e == NULL)
		return (NULL);
	src = pq->src;
	do {
		if (e)
		{
			if (visited[e->dest->index] == 0)
			{
				if (!queue_push_back(bfs_q, e) ||
						!find_path(path, pq, src, e, start, target_content))
				{
					path = NULL;
					break;
				}
				visited[e->dest->index] = 1;
			}
			e = e->next;
		}
		else
		{
			src = bfs_q->front->ptr;
			for (e = src->dest->edges; e &&
					visited[e->dest->index] == 1; e = e->next)
				;
			if (e)
				continue;
			/* printf("popping: %s\n", ((vertex_t *)bfs_q->front->ptr)->content); */
			_dequeue(bfs_q);
		}
	} while (bfs_q->front != NULL);
	queue_delete(bfs_q);
	return (path);
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
	queue_t *path;
	pqueue_t *pq;
	edge_t *src_e;
	int *visited;

	if (!graph || !start || !target)
		return (NULL);
	path = queue_create();
	if (path == NULL)
		return (NULL);
	if (queue_push_front(path, start->content) == NULL)
		return (NULL);
	pq = malloc(sizeof(*pq));
	if (pq == NULL)
		return (NULL);
	src_e = malloc(sizeof(*src_e));
	if (src_e == NULL)
		return (NULL);
	src_e->dest = (vertex_t *)start, src_e->next = NULL, src_e->weight = 0;
	pq->dest = pq->src = src_e, pq->next = NULL;
	printf("Checking %s, distance from %s is %i\n", pq->dest->dest->content, start->content, pq->weight);
	visited = calloc(graph->nb_vertices, sizeof(*visited));
	if (visited == NULL)
		return (NULL);
	if (bfs_graph(path, pq, visited, start, target->content) == NULL)
	{
		queue_delete(path);
		path = NULL;
	}
	free(visited);
	/* free pq and src_e */
	return (path);
}
