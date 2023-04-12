#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * backtrack - recursive helper function
 * @graph: pointer to the graph
 * @vertex: pointer to a starting vertex in the graph
 * @target: pointer to the target vertex in the graph
 * @path: pointer to the found path
 * Return: 1 if path is found, otherwise 0
 */
int backtrack(graph_t *graph, vertex_t *vertex, vertex_t const *target,
		queue_t *path)
{
	edge_t *edge;
	vertex_t *next;

	if (!vertex)
		return (0);

	printf("Checking %s\n", vertex->content);
	vertex->index = 1;
	queue_push_back(path, vertex->content);

	if (vertex == target)
		return (1);

	for (edge = vertex->edges; edge; edge = edge->next)
	{
		next = edge->dest;
		if (!next->index)
		{
			if (backtrack(graph, next, target, path))
				return (1);
		}
	}
	dequeue(path);
	vertex->index = 0;

	return (0);
}

/**
 * backtracking_graph -  searches for the first path from a starting point to
 * a target point in a graph
 * @graph: pointer to the graph to traverse
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 * Return: a queue in which each node is a char * corresponding to a vertex,
 * forming a path from start to target
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
		vertex_t const *target)
{
	queue_t *path = queue_create();

	if (!graph || !start || !target || !path)
		return (NULL);

	backtrack(graph, (vertex_t *)start, target, path);

	return (path);
}
