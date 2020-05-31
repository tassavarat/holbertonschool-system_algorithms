#include "graphs.h"

/**
 * link_vert - links specified vertices together with a newly created edge
 * @src_v: pointer to vertex to link from
 * @dest_v: pointer to vertex to link to
 * @type: type of edge: UNIDIRECTIONAL or BIDIRECTIONAL
 *
 * Return: 1 on success, 0 on failure
 */
int link_vert(vertex_t *src_v, vertex_t *dest_v, edge_type_t type)
{
	edge_t *new, *cur;

	new = malloc(sizeof(*new));
	if (!new)
		return (0);
	new->dest = dest_v;
	new->next = NULL;
	++src_v->nb_edges;
	for (cur = src_v->edges; cur && cur->next; cur = cur->next)
		;
	if (!cur)
		src_v->edges = new;
	else
		cur->next = new;
	if (type == BIDIRECTIONAL)
		return (link_vert(dest_v, src_v, UNIDIRECTIONAL));
	return (1);
}

/**
 * find_vert - find vertices containing content specified by src and dest
 * @graph: pointer to graph containing vertices
 * @src: string identifying content of vertex src_v should point to
 * @dest: string identifying content of vertex dest_v should point to
 * @src_v: double pointer to initialise
 * @dest_v: double pointer to initialise
 *
 * Return: 1 on success, 0 if specified vertices not found
 */
int find_vert(graph_t *graph, const char *src, const char *dest,
		vertex_t **src_v, vertex_t **dest_v)
{
	vertex_t *cur;

	for (cur = graph->vertices; cur && (!*src_v || !*dest_v);
			cur = cur->next)
	{
		if (!(strcmp(cur->content, src)))
			*src_v = cur;
		if (!(strcmp(cur->content, dest)))
			*dest_v = cur;
	}
	if (!*src_v || !*dest_v)
		return (0);
	return (1);
}

/**
 * graph_add_edge - add an edge between two vertices in an existing graph
 * @graph: pointer to graph to add edge to
 * @src: string identifying vertex to make connection from
 * @dest: string identifying vertex to connect to
 * @type: type of edge: UNIDIRECTIONAL or BIDIRECTIONAL
 *
 * Return: 1 on success, 0 on failure
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest,
		edge_type_t type)
{
	vertex_t *src_v, *dest_v;

	if (!graph || !src || !dest ||
			(type != UNIDIRECTIONAL && type != BIDIRECTIONAL))
		return (0);
	src_v = dest_v = NULL;
	if (!find_vert(graph, src, dest, &src_v, &dest_v))
		return (0);
	return (link_vert(src_v, dest_v, type));
}
