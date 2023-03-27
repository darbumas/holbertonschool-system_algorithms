#include <string.h>
#include "graphs.h"

/**
 * graph_add_vertex - Adds a vertex to an existing graph
 * @graph: pointer to the graph to add the vertex to
 * @str: pointer to the string to store in the new vertex
 * Return: pointer to the created vertex, NULL otherwise
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *vertex, *temp;

	if (!graph || !str)
		return (NULL);
	/* First check if a vertex with same content already exist */
	temp = graph->vertices;
	while (temp)
	{
		if (strcmp(temp->content, str) == 0)
			return (NULL);
		temp = temp->next;
	}
	/* Allocate memory for new vertex */
	vertex = malloc(sizeof(vertex_t));
	if (!vertex)
		return (NULL);
	/* Allocate memory for the content and copy the string */
	vertex->content = strdup(str);
	if (!vertex->content)
	{
		free(vertex);
		return (NULL);
	}
	/* Initialize new vertex */
	vertex->index = graph->nb_vertices;
	vertex->nb_edges = 0;
	vertex->edges = NULL;
	vertex->next = NULL;
	/* Update the graph */
	if (!graph->last_v)
		graph->vertices = vertex;
	else
		graph->last_v->next = vertex;
	graph->last_v = vertex;
	graph->nb_vertices++;
	return (vertex);
}
