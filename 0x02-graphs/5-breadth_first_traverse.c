#include "graphs.h"

/**
 * breadth_first_traverse - goes through a graph using the BFS algorithm
 * @graph: pointer to the graph to traverse
 * @action: pointer to a function to be called for each visited vertex
 * Return: biggest vertex depth, 0 otherwise
 */

size_t breadth_first_traverse(const graph_t *graph, void (*action)
		(const vertex_t *v, size_t depth))
{
	size_t max_depth, current_level_size, next_level_size, i;
	bool *visited;
	vertex_t **current_level, **next_level, *v, *neighbor;
	edge_t *edge;

	if (!graph || !action)
		return (0);
	visited = calloc(graph->nb_vertices, sizeof(bool));
	if (!visited)
		return (0);

	max_depth = 0;
	current_level_size = 1;
	current_level = malloc(current_level_size * sizeof(vertex_t *));

	if (!current_level)
	{
		free(visited);
		return (0);
	}
	current_level[0] = graph->vertices;
	while (current_level_size > 0)
	{
		next_level_size = 0;
		next_level = NULL;

		for (i = 0; i < current_level_size; ++i)
		{
			v = current_level[i];

			if (!visited[v->index])
			{
				visited[v->index] = true;
				action(v, max_depth);
				for (edge = v->edges; edge; edge = edge->next)
				{
					neighbor = edge->dest;

					if (!visited[neighbor->index])
					{
						++next_level_size;
						next_level = realloc(next_level, next_level_size * sizeof(vertex_t *));
						if (!next_level)
						{
							free(current_level);
							free(visited);
							return (0);
						}
						next_level[next_level_size - 1] = neighbor;
					}
				}
			}
		}
		free(current_level);
		current_level = next_level;
		current_level_size = next_level_size;
		++max_depth;
	}
	free(visited);
	return (max_depth - 1);
}
