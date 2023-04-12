#include "pathfinding.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * recursive_backtrack - Performs the actual recursive backtracking
 * @map: 2-D array of a grid, where '0' indicates a free cell and '1' indicates
 * a blocked cell
 * @rows: number of rows in the map
 * @cols: number of columns in the map
 * @cur: pointer to current point (cell) in the map
 * @target: points to the target point (destination) in the map
 * @path: points to a queue that stores the found path from 'start' to 'target'
 *
 * Return: 1 if a valid path to target is found, otherwise 0.
 */
static int recursive_backtrack(char **map, int rows, int cols, point_t *cur,
		point_t const *target, queue_t *path)
{
	point_t next, *point = NULL;
	int result;

	/* Is the current point blocked or out of bounds? */
	if (cur->x < 0 || cur->x >= rows || cur->y < 0 || cur->y >= cols ||
			map[cur->x][cur->y] == '1')
		return (0);

	/* Print the current coordinates */
	printf("Checking coordinates [%d, %d]\n", cur->x, cur->y);

/* If the current point is the target, add it to the path and return 1 */
	if (cur->x == target->x && cur->y == target->y)
		return (1);
	/* Mark the current cell as visited */
	map[cur->x][cur->y] = '1';

	point = malloc(sizeof(point_t));
	if (!point)
		return (0);
	*point = *cur;

	/* Move right */
	next.x = cur->x;
	next.y = cur->y + 1;
	result = recursive_backtrack(map, rows, cols, &next, target, path);
	if (result)
	{
		queue_push_front(path, point);
		return (1);
	}
	/* Move down */
	next.x = cur->x + 1;
	next.y = cur->y;
	result = recursive_backtrack(map, rows, cols, &next, target, path);
	if (result)
	{
		queue_push_front(path, point);
		return (1);
	}
	/* Move left */
	next.x = cur->x;
	next.y = cur->y - 1;
	result = recursive_backtrack(map, rows, cols, &next, target, path);
	if (result)
	{
		queue_push_front(path, point);
		return (1);
	}
	/* Move up */
	next.x = cur->x - 1;
	next.y = cur->y;
	result = recursive_backtrack(map, rows, cols, &next, target, path);
	if (result)
	{
		queue_push_front(path, point);
		return (1);
	}
	free(point);
	return (0);
}

/**
 * backtracking_array - searches for the first path from a starting point to a
 * target point within a 2D array
 * @map: the 2D grid
 * @rows: number of rows in the grid
 * @cols: number of columns in the grid
 * @start: stores the coordinate of starting point
 * @target: stores the coordinate of the target point.
 *
 * Return: pointer to a queue in which each node is a point in the path from
 * start to target; otherwise NULL.
 */
queue_t *backtracking_array(char **map, int rows, int cols,
		point_t const *start, point_t const *target)
{
	queue_t *path;
	point_t *origin, cur;

	path = queue_create();
	if (!path)
		return (NULL);
	cur = *start;

	if (recursive_backtrack(map, rows, cols, &cur, target, path))
	{
		origin = malloc(sizeof(point_t));
		if (!origin)
		{
			queue_delete(path);
			return (NULL);
		}
		*origin = *start;
		queue_push_front(path, origin);
		return (path);
	}
	/* If no path is found, delete the queue and return NULL */
	queue_delete(path);
	return (NULL);
}
