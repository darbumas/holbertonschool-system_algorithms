#include "graphs.h"

/**
 * enqueue - enqueues a given vertex with its corresponding depth
 * @rear: pointer to the last node of the queue
 * @vertex: pointer to the vertex to enqueue
 * @depth: depth of the vertex being enqueued
 * Return: pointer to the newly created node; NULL otherwise
 */
queue_node_t *enqueue(queue_node_t *rear, vertex_t *vertex, size_t depth)
{
	queue_node_t *new_node = malloc(sizeof(queue_node_t));

	if (!new_node)
		return (NULL);

	new_node->vertex = vertex;
	new_node->depth = depth;
	new_node->next = NULL;

	if (rear)
		rear->next = new_node;

	return (new_node);
}

/**
 * dequeue - dequeues the front node from the queue and
 * update the front pointer
 * @front: pointer to a pointer to the first node of the queue
 *
 * Return: pointer to the dequeued node, NULL otherwise
 */
queue_node_t *dequeue(queue_node_t **front)
{
	queue_node_t *prev = NULL;

	if (!*front)
		return (prev);
	prev = *front;
	*front = prev->next;

	return (prev);
}

/**
 * breadth_first_traverse - goes through a graph using the breadth-first
 * algorithm
 * @graph: pointer to the graph to traverse
 * @action: pointer to a function to be called for each visited vertex
 * Return: the biggest vertex depth, 0 otherwise
 */
size_t breadth_first_traverse(const graph_t *graph, void (*action)
		(const vertex_t *v, size_t depth))
{
	size_t depth, i, max = 0;
	bool *visited;
	vertex_t *vertex;
	edge_t *edge;
	queue_node_t *rear, *current, *front;

	if (!graph || !action)
		return (0);

	visited = malloc(graph->nb_vertices * sizeof(bool));
	if (!visited)
		return (0);
	for (i = 0; i < graph->nb_vertices; i++)
		visited[i] = false;

	/* Initialize the queue with the first vertext and depth 0 */
	front = NULL;
	rear = enqueue(front, graph->vertices, 0);
	if (!rear)
	{
		free(visited);
		return (0);
	}
	front = rear;

	/* Iterate through the queue until it's empty */
	while (front)
	{
		current = dequeue(&front);
		vertex = current->vertex;
		depth = current->depth;
	/* If the vertex hasn't been visited yet */
		if (!visited[vertex->index])
		{
		/* Mark the vertex as visited and call the action */
			visited[vertex->index] = true;
			action(vertex, depth);
		/* Update the maximum depth if necessary */
			if (depth > max)
				max = depth;
		/* Enqueue all connected vertices with depth + 1 */
			edge = vertex->edges;
			while (edge)
			{
				rear = enqueue(rear, edge->dest, depth + 1);
				if (!rear)
				{
					free(visited);
					return (0);
				}
				edge = edge->next;
			}
		}
		free(current);
	}
	free(visited);
	return (max);
}
