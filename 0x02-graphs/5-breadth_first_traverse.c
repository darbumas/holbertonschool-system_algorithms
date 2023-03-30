#include "graphs.h"

/**
 * enqueue - Enqueues a vertex with a given depth into a queue
 * @front: pointer to a pointer to the front node of the queue
 * @rear: pointer to a pointer to the rear node of the queue
 * @vertex: pointer to the vertex to be enqueued
 * @depth: the depth of the vertex in the graph
 */
void enqueue(queue_node_t **front, queue_node_t **rear, vertex_t *vertex,
		size_t depth)
{
	queue_node_t *new_node = malloc(sizeof(queue_node_t));

	new_node->vertex = vertex;
	new_node->depth = depth;
	new_node->next = NULL;

	/* If queue is empty, set both front and rear point to new node... */
	if (!*rear)
	{
		*front = *rear = new_node;
		return;
	}
	/* ...else, set new node at end of the queue */
	(*rear)->next = new_node;
	*rear = new_node;
}

/**
 * dequeue - Dequeues the front node from a queue
 * @front: pointer to a pointer to the front node of the queue
 * @rear: pointer to a pointer to the rear node of the queue
 * Return: pointer to the dequeued node, NULL otherwise
 */
queue_node_t *dequeue(queue_node_t **front, queue_node_t **rear)
{
	queue_node_t *temp;

	if (!*front)
		return (NULL);

	temp = *front;
	*front = (*front)->next;

	if (!*front)
		*rear = NULL;

	return (temp);
}

/**
 * breadth_first_traverse - goes through a graph using the BFS algorithm
 * @graph: pointer to the graph to traverse
 * @action: pointer to a function to be called for each visited vertex.
 * Return: biggest vertex depth, 0 otherwise
 */
size_t breadth_first_traverse(const graph_t *graph,
		void (*action)(const vertex_t *v, size_t depth))
{
	bool *visited;
	queue_node_t *current_node, *front = NULL, *rear = NULL;
	vertex_t *current_vertex, *neighbor;
	edge_t *edge;
	size_t current_depth, max_depth = 0;

	if (!graph || !action)
		return (0);
	if (graph->nb_vertices == 0)
		return (0);
	visited = calloc(graph->nb_vertices, sizeof(bool));
	if (!visited)
		return (0);
	enqueue(&front, &rear, graph->vertices, 0);
	visited[graph->vertices->index] = true;
	while (front != NULL)
	{
		/* Dequeue the front node and get its vertex and depth */
		current_node = dequeue(&front, &rear);
		current_vertex = current_node->vertex;
		current_depth = current_node->depth;
		/* Update max_depth if necessary and call action */
		if (current_depth > max_depth)
			max_depth = current_depth;
		action(current_vertex, current_depth);

		/* Iterate through the neighbors of the current vertex */
		for (edge = current_vertex->edges; edge; edge = edge->next)
		{
			neighbor = edge->dest;
			/* If not visited yet, enqueue it and mark visited */
			if (!visited[neighbor->index])
			{
				visited[neighbor->index] = true;
				enqueue(&front, &rear, neighbor,
						current_depth + 1);
			}
		}
		free(current_node);
	}
	free(visited);
	return (max_depth);
}
