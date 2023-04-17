#include "pathfinding.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

/**
 * init_arrays_and_queue - Initializes the distance and visted arrays,
 * and creates a priorirty queue for the vertices
 * @graph: pointer to the graph to go through
 * @start: pointer to the starting vertex
 * @dist: pointer to the distance array
 * @visited: pointer to the visited array
 * @queue: pointer to the priority queue for vertices
 *
 * Return: 0 if initialization is successfull, otherwise -1
 */
void init_arrays_and_queue(graph_t *graph, vertex_t const *start, int **dist,
		int **visited, queue_t **queue)
{
	size_t i;

	*dist = calloc(graph->nb_vertices, sizeof(int));
	*visited = calloc(graph->nb_vertices, sizeof(int));

	for (i = 0; i < graph->nb_vertices; i++)
		(*dist)[i] = INT_MAX;
	(*dist)[start->index] = 0;

	*queue = queue_create();
	queue_push_back(*queue, (void *)start);
}

/**
 * process_vertices - Processes vertices to find the shortest path using
 * Dijkstra's algorithm
 * @queue: pointer to the priority queue for vertices
 * @dist: pointer to the distance array
 * @visited: pointer to the visited array
 * @target: pointer to the target vertex
 *
 * Return: 0 if target is reached, otherwise -1
 */
void process_vertices(queue_t *queue, int *dist, int *visited,
		vertex_t const *target)
{
	vertex_t *current, *neighbor;
	edge_t *edge;
	queue_node_t *node;
	int min_dist, alt_dist;

	while (queue->front)
	{
		current = (vertex_t *)(queue->front->ptr);
		min_dist = dist[current->index];

		node = queue->front;
		queue->front = queue->front->next;
		if (queue->front)
			queue->front->prev = NULL;
		else
			queue->back = NULL;
		free(node);

		printf("Checking %s, distance from %s is %d\n", current->content,
				target->content, min_dist);
		visited[current->index] = 1;

		if (current == target)
			break;
		edge = current->edges;
		while (edge)
		{
			neighbor = edge->dest;
			if (!visited[neighbor->index])
			{
				alt_dist = min_dist + edge->weight;
				if (alt_dist < dist[neighbor->index])
				{
					dist[neighbor->index] = alt_dist;
					queue_push_back(queue, (void *)neighbor);
				}
			}
			edge = edge->next;
		}
	}
}

/**
 * build_path - Builds the shortest path from start to target vertices based
 * on the distance array
 * @dist: pointer to the distance array
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 *
 * Return: pointer to the resulting queue storing the path, otherwise NULL
 */
queue_t *build_path(int *dist, vertex_t const *start, vertex_t const *target)
{
	vertex_t *current, *neighbor;
	edge_t *edge;
	queue_node_t *node;
	int min_dist;
	queue_t *path = queue_create();

	if (!path)
		return (NULL);
	current = (vertex_t *)target;
	while (current != start)
	{
		node = queue_push_front(path, (void *)current->content);
		if (!node)
		{
			queue_delete(path);
			return (NULL);
		}
		min_dist = INT_MAX;
		edge = current->edges;
		while (edge)
		{
			neighbor = edge->dest;
			if (dist[neighbor->index] + edge->weight ==
			dist[current->index] && dist[neighbor->index] < min_dist)
			{
				min_dist = dist[neighbor->index];
				current = neighbor;
			}
			edge = edge->next;
		}
	}
	node = queue_push_front(path, (void *)start->content);
	if (!node)
	{
		queue_delete(path);
		return (NULL);
	}
	return (path);
}

/**
 * dijkstra_graph - Finds the shortest path from a starting point to a target
 * using Dijkstra's algorithm
 * @graph: pointer to the graph to go through
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 *
 * Return: pointer to the resulting queue storing the path, otherwise NULL
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
		vertex_t const *target)
{
	int *dist = NULL;
	int *visited = NULL;
	queue_t *queue = NULL;
	queue_t *path = NULL;

	init_arrays_and_queue(graph, start, &dist, &visited, &queue);
	if (!dist || !visited || !queue)
	{
		free(dist);
		free(visited);
		queue_delete(queue);
		return (NULL);
	}

	process_vertices(queue, dist, visited, target);
	path = build_path(dist, start, target);

	free(dist);
	free(visited);
	queue_delete(queue); /* Free the queue before returning */

	return (path);
}
