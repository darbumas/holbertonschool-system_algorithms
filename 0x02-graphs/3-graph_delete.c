#include "graphs.h"

/**
 * graph_delete - completely deletes a graph
 * @graph: pointer to the graph to be deleted
 */
void graph_delete(graph_t *graph)
{
	vertex_t *vertex, *temp_vx;
	edge_t *edge, *temp_edge;

	if (!graph)
		return;

	/* Iterate through the vertices in the graph */
	vertex = graph->vertices;
	while (vertex)
	{
		/* Iterate through the edges of the current vertex */
		edge = vertex->edges;
		while (edge)
		{
			temp_edge = edge;
			edge = edge->next;
			free(temp_edge);
		}
		/* Free the content and move to the next vertex */
		free(vertex->content);
		temp_vx = vertex;
		vertex = vertex->next;
		free(temp_vx);
	}
	free(graph);
}
