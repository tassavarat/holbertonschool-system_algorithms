#include "graphs.h"

/**
 * pop - free the head node of a queue
 * @head: double pointer to head node
 *
 * Return: pointer to vertex pointed to by queue node being freed
 */
vertex_t *pop(queue_t **head)
{
	queue_t *tmp;
	vertex_t *v;

	if (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		v = tmp->node;
		free(tmp);
	}
	return (v);
}

/**
 * push - push new node into a queue
 * @head: double pointer to head node of queue
 * @tail: pointer to tail node of queue
 * @v: pointer to node queue will point to
 *
 * Return: newly created node, NULL on failure
 */
queue_t *push(queue_t **head, queue_t *tail, vertex_t *v)
{
	queue_t *new = malloc(sizeof(*new));

	if (!new)
		return (NULL);
	new->node = v;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
		tail->next = new;
	return (new);
}

/**
 * bfs - traverse graph using breath-first algorithm
 * @v: pointer vertex node being visited
 * @visited: array specifying if vertex has been visited
 * @action: function pointer to be called for each visited vertex
 *
 * Return: maximum depth reached, 0 on failure
 */
size_t bfs(vertex_t *v, int *visited,
		void (*action)(const vertex_t *v, size_t depth))
{
	size_t depth;
	queue_t *qhead, *qtail;
	edge_t *e;

	depth = 1;
	visited[v->index] = depth;
	action(v, 0);
	qhead = NULL;
	e = v->edges;
	if (!e)
		return (0);
	do {
		if (e)
		{
			qtail = push(&qhead, qtail, e->dest);
			if (!qtail)
				return (0);
			visited[qtail->node->index] = depth;
			e = e->next;
		}
		else
		{
			depth = visited[qhead->node->index] + 1;
			for (e = qhead->node->edges; e && visited[e->dest->index];
					e = e->next)
				;
			action(pop(&qhead), visited[qhead->node->index]);
		}
	} while (qhead);
	return (--depth);
}

/**
 * goes through graph using breadth-first algorithm
 * @graph: pointer to graph to traverse
 * @action: function pointer to be called for each visited vertex
 *	    v: pointer to visited vertex
 *	    depth: depth of v
 *
 * Return: greatest vertex depth, 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
		void (*action)(const vertex_t *v, size_t depth))
{
	int *visited;
	size_t depth;

	if (!graph || !action || !graph->nb_vertices)
		return (0);
	visited = calloc(graph->nb_vertices, sizeof(*visited));
	if (!visited)
		return (0);
	depth = bfs(graph->vertices, visited, action);
	free(visited);
	return (depth);
}
