#include "graphs.h"

/**
 * get_vertex_by_content - Finds a vertex in the graph by its content
 * @graph: pointer to the graph
 * @str: pointer to the content string to search for
 * Return: pointer to the vertex with matching content string
 */
static vertex_t *get_vertex_by_content(graph_t *graph, const char *str)
{
	vertex_t *vertex;

	if (!graph || !str)
		return (NULL);

	vertex = graph->vertices;
	while (vertex)
	{
		if (strcmp(vertex->content, str) == 0)
			return (vertex);
		vertex = vertex->next;
	}
	return (NULL);
}

/**
 * add_edge - Adds an edge between two vertices
 * @src_v: pointer to the source vertex
 * @dest_v: pointer to the destination vertex
 * Return: 1 on success, 0 otherwise
 */
static int add_edge(vertex_t *src_v, vertex_t *dest_v)
{
	edge_t *current, *new = malloc(sizeof(edge_t));

	if (!new)
		return (0);

	new->dest = dest_v;
	new->next = NULL;

	if (!src_v->edges)
		src_v->edges = new;
	else
	{
		current = src_v->edges;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	src_v->nb_edges++;

	return (1);
}

/**
 * graph_add_edge - Adds an edge between two vertices in the graph
 * @graph: pointer to the graph
 * @src: pointer to the string content of the source vertex
 * @dest: pointer to the string content of the destination vertex
 * @type: edge is either UNIDIRECTIONAL or BIDIRECTIONAL
 * Return: 1 on success, 0 on failure
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest,
			edge_type_t type)
{
	vertex_t *src_vx, *dest_vx;
	edge_t *temp;

	if (!graph || !src || !dest)
		return (0);

	/* Find the source/dest vertices by their content */
	src_vx = get_vertex_by_content(graph, src);
	dest_vx = get_vertex_by_content(graph, dest);

	if (!src_vx || !dest_vx)
		return (0);

	/* Add the edge from the source to the destination vertex */
	if (!add_edge(src_vx, dest_vx))
		return (0);

	/* If the edge type is bidirectional, add the reverse edge too */
	if (type == BIDIRECTIONAL)
	{
		if (!add_edge(dest_vx, src_vx))
		{
			temp = src_vx->edges;
			src_vx->edges = src_vx->edges->next;
			free(temp);
			src_vx->nb_edges--;

			return (0);
		}
	}
	return (1);
}
