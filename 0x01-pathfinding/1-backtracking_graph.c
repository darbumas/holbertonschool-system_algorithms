#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * backtrack - recursively does the backtracking on a graph
 * @graph: pointer to the graph
 * @vertex: pointer to the current vertex
 * @visited: array to keep track of visited vertices
 * @target: the target vertex
 * @path: pointer to the queue storing path
 * Return: 1 if path found, otherwise 0
 */
static int backtrack(graph_t *graph, vertex_t *vertex, int *visited,
			vertex_t const *target, queue_t *path)
{
	edge_t *edge;
	int found = 0;
	char *content;

	if (vertex == target)
	{
		printf("Checking %s\n", vertex->content);
		content = strdup(vertex->content);
		queue_push_front(path, content);
		return (1);
	}
	if (visited[vertex->index])
		return (0);

	printf("Checking %s\n", vertex->content);
	visited[vertex->index] = 1;

	for (edge = vertex->edges; edge; edge = edge->next)
	{
		found = backtrack(graph, edge->dest, visited, target, path);
		if (found)
		{
			content = strdup(vertex->content);
			queue_push_front(path, content);
			break;
		}
	}
	return (found);
}

/**
 * backtracking_graph - searches for the first path from a starting point to
 * a target point within a graph
 * @graph: pointer to the graph to go through
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 * Return: pointer to created queue with found path, or NULL
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
		vertex_t const *target)
{
	int *visited;
	queue_t *path;

	if (!graph || !start || !target)
		return (NULL);

	/* Init visited array */
	visited = calloc(graph->nb_vertices, sizeof(int));
	if (!visited)
		return (NULL);

	/* Init the queue for the path */
	path = queue_create();
	if (!path)
	{
		free(visited);
		return (NULL);
	}
	if (!backtrack(graph, (vertex_t *)start, visited, target, path))
	{
		queue_delete(path);
		path = NULL;
	}
	free(visited);
	return (path);
}
