#include "graphs.h"

/**
 * graph_create - Allocates memory for a graph_t structure and initialiazes its
 * contents
 *
 * Return: pointer to the allocated structure, NULL otherwise
 */
graph_t *graph_create(void)
{
	graph_t *graph;

	graph = calloc(1, sizeof(graph_t));
	if (!graph)
		return (NULL);

	/* Calloc will init our nb_vertices and vertices to 0/NULL */

	return (graph);
}
