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
	vertex_t *vertex, *temp, *last;

	if (!graph || !str)
		return (NULL);

	/* Check if a vertex with the same content already exists */
	temp = graph->vertices;
	while (temp != NULL)
	{
		if (strcmp(temp->content, str) == 0)
			return (NULL);
		last = temp;
		temp = temp->next;
	}

	/* Allocate memory for the new vertex & the content/copy of the str*/
	vertex = malloc(sizeof(vertex_t));
	if (!vertex)
		return (NULL);
	vertex->content = strdup(str);
	if (!vertex->content)
	{
		free(vertex);
		return (NULL);
	}

	/* Initialize the new vertex */
	vertex->index = graph->nb_vertices;
	vertex->nb_edges = 0;
	vertex->edges = NULL;
	vertex->next = NULL;

	/* Update the graph */
	if (graph->vertices == NULL)
		graph->vertices = vertex;
	else
		last->next = vertex;
	graph->nb_vertices++;

	return (vertex);
}
