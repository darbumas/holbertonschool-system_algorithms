#include "graphs.h"

/**
 * dfs_visit - recursive helper ƒ() that keeps track of the current depth and
 * visited vertices
 * @vertex: pointer to the current vertex
 * @visited: pointer to an array of visited vertices
 * @depth: current depth of the vertex relative to the starting vertex
 * @action: pointer to a function that will be called for each visited vertex
 * @max: pointer to int to store maximum depth encountered during the
 * traversal
 */
void dfs_visit(const vertex_t *vertex, bool *visited, size_t depth,
		void (*action)(const vertex_t *v, size_t depth), size_t *max)
{
	edge_t *edge;

	if (!vertex || visited[vertex->index])
		return;

	/* Mark the vertex as visited and call the action function */
	visited[vertex->index] = true;
	action(vertex, depth);

	/* Update the maximum depth if current depth is greater */
	if (depth > *max)
		*max = depth;

	/* Iterate through the edges of the current vertex */
	edge = vertex->edges;
	while (edge)
	{
		dfs_visit(edge->dest, visited, depth + 1, action, max);
		edge = edge->next;
	}
}

/**
 * depth_first_traverse - goes through graph using depth-first algorithm
 * @graph: pointer to the graph to traverse
 * @action: pointer to a function to be called for each visited vertex
 * Return: biggest vertex depth, 0 otherwise
 */
size_t depth_first_traverse(const graph_t *graph, void (*action)
		(const vertex_t *v, size_t depth))
{
	size_t max = 0, i = 0;
	bool *visited;

	if (!graph || !action)
	{
		return (0);
	}

	/* Initialize the visited array to keep track of visited vertices */
	visited = malloc(graph->nb_vertices * sizeof(bool));
	for (; i < graph->nb_vertices; i++)
		visited[i] = false;

	dfs_visit(graph->vertices, visited, 0, action, &max);

	free(visited);
	return (max);
}
