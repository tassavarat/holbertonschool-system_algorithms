#include "pathfinding.h"

/**
 * clean_up - free dynamically allocated memory
 * @vq: pointer to head node of queue to free
 * @visited: pointer to array to free
 * @dest_added: pointer to array to free
 */
void clean_up(vertex_queue_t *vq, int *visited, int *dest_added)
{
	vertex_queue_t *tmp;

	while (vq != NULL)
	{
		tmp = vq;
		vq = vq->next;
		free(tmp);
	}
	free(visited);
	free(dest_added);
}

/**
 * find_path - find the shortest path from start to target vertices
 * @cur: pointer to end of queue
 *
 * Return: queue with content string of stortest path from start to target node
 * or NULL on error
 */
queue_t *find_path(vertex_queue_t *cur)
{
	vertex_t *src;
	queue_t *path;

	if (!cur)
		return (NULL);
	path = queue_create();
	if (!path)
		return (NULL);
	if (!queue_push_front(path, strdup(cur->dest->content)))
		return (NULL);
	/* printf("pushing %s\n", cur->dest->content); */
	src = cur->src;
	/* printf("checking for %s\n", src->content); */
	cur = cur->prev;
	do {
		if (cur->dest == src)
		{
			if (!queue_push_front(path, strdup(cur->dest->content)))
				return (NULL);
			/* printf("pushing %s\n", cur->dest->content); */
			src = cur->src;
			/* printf("checking for %s\n", src->content); */
		}
		cur = cur->prev;
	} while (cur != NULL);
	return (path);
}

/**
 * insert_vq_node - insert node into queue sorted by ascending weight
 * @head: pointer to head node of queue
 * @src: pointer to queue node to be used as source value for new node
 * @dest: pointer to edge node to be used as dest value for new node
 * @dest_added: array to track if destination has been added to queue
 *
 * Return: queue node of given dest with lowest weight, NULL on failure
 */
vertex_queue_t *insert_vq_node(vertex_queue_t *head, vertex_queue_t *src,
		edge_t *dest, int *dest_added)
{
	vertex_queue_t *cur, *del, *tmp, *new;

	if (!head)
		return (NULL);
	for (cur = head; cur->next != NULL &&
			src->weight + dest->weight > cur->next->weight; cur = cur->next)
		if (dest->dest == cur->next->dest)
			return (cur->next);
	if (dest_added[dest->dest->index] == 1)
	{
		for (del = cur; del->dest != dest->dest; tmp = del, del = del->next)
			;
		tmp->next = del->next;
		free(del);
	}
	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->src = src->dest;
	new->dest = dest->dest;
	new->weight = src->weight + dest->weight;
	new->prev = cur;
	new->next = NULL;
	if (cur->next != NULL)
	{
		cur->next->prev = new;
		new->next = cur->next;
	}
	cur->next = new;
	dest_added[new->dest->index] = 1;
	/* for (cur = head; cur != NULL; cur = cur->next) */
	/*	printf("src: %s\tdest: %s\tweight: %i\n", cur->src->content, */
	/*			cur->dest->content, cur->weight); */
	/* putchar('\n'); */
	return (new);
}

/**
 * populate_queue - populate vertex_queue struct for dijkstra traversal
 * @vq_head: pointer to queue head node
 * @start: pointer to start vertex
 * @target: pointer to target vertex
 * @visited: array used to track visited vertices
 * @dest_added: array to track if destination has been added to queue
 *
 * Return: tail of queue, NULL on failure
 */
vertex_queue_t *populate_queue(vertex_queue_t *vq_head, const vertex_t *start,
		const vertex_t *target, int *visited, int *dest_added)
{
	vertex_queue_t *vq_cur;
	edge_t *e_cur;

	if (!vq_head || !visited)
		return (NULL);
	for (vq_cur = vq_head; vq_cur != NULL; vq_cur = vq_cur->next)
	{
		printf("Checking %s, distance from %s is %i\n", vq_cur->dest->content,
				start->content, vq_cur->weight);
		/* printf("vertex: %s\n", vq_cur->dest->content); */
		if (vq_cur->dest == target)
			return (vq_cur);
		for (e_cur = vq_cur->dest->edges; e_cur != NULL; e_cur = e_cur->next)
			if (visited[e_cur->dest->index] != 1 &&
					!insert_vq_node(vq_head, vq_cur, e_cur, dest_added))
				return (NULL);
		visited[vq_cur->dest->index] = 1;
	}
	return (vq_head);
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
	vertex_queue_t *vq;
	int *visited, *dest_added;
	queue_t *path;

	if (!graph || !start || !target)
		return (NULL);
	vq = malloc(sizeof(*vq));
	if (!vq)
		return (NULL);
	visited = calloc(graph->nb_vertices, sizeof(*visited));
	if (!visited)
		return (NULL);
	dest_added = calloc(graph->nb_vertices, sizeof(*dest_added));
	if (!dest_added)
		return (NULL);
	vq->src = vq->dest = (vertex_t *)start;
	vq->weight = 0;
	vq->prev = vq->next = NULL;
	path = find_path(populate_queue(vq, start, target, visited, dest_added));
	if (!path)
		return (NULL);
	clean_up(vq, visited, dest_added);
	return (path);
}
