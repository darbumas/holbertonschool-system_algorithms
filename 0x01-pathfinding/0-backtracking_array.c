#include "pathfinding.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * backtrack - recursively does the backtracking
 * @map: pointer to a 2D grid
 * @rows: number of rows in grid
 * @cols: number of columns in grid
 * @x: x coordinate
 * @y: y coordinate
 * @path: pointer to the queue storing path
 * Return: 1 if path found, otherwise 0
 */
static int backtrack(char **map, int rows, int cols, int x, int y,
		queue_t *path)
{
	point_t *cur_point;

	if (x < 0 || x >= rows || y < 0 || y >= cols || map[x][y] == '1')
		return (0);

	/* Set current cell as visited */
	map[x][y] = '1';

	cur_point = malloc(sizeof(point_t));
	if (!cur_point)
		return (0);
	cur_point->x = x;
	cur_point->y = y;
	printf("Checking coordinates [%d, %d]\n", cur_point->x, cur_point->y);
	queue_push_back(path, cur_point);

	if (x == rows - 1 && y == cols - 1)
		return (1);
	/* Visit neighbor cells in RBLT order */
	if (backtrack(map, rows, cols, x, y + 1, path) || /* RIGHT */
		backtrack(map, rows, cols, x + 1, y, path) || /* BOTTOM */
		backtrack(map, rows, cols, x, y - 1, path) || /* LEFT */
		backtrack(map, rows, cols, x - 1, y, path)) /* TOP */
		return (1);

	free(dequeue(path));
	return (0);
}

/**
 * backtracking_array - searches for the first path from a starting point to
 * a target point within a 2D array
 * @map: pointer to a read-only 2D array
 * @rows: number of rows in the grid
 * @cols: number of columns in the grid
 * @start: stores coordinates of starting point
 * @target: stores coordinates of target point
 * Return: pointer to created queue with found path, or NULL
 */
queue_t *backtracking_array(char **map, int rows, int cols,
		point_t const *start, point_t const *target)
{
	char **copy;
	queue_t *path;
	int i;

	if (!map || rows <= 0 || cols <= 0 || !start || !target)
		return (NULL);
	copy = malloc(rows * sizeof(char *));
	if (!copy)
		return (NULL);

	for (i = 0; i < rows; i++)
	{
		copy[i] = malloc(cols + 1);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		memcpy(copy[i], map[i], cols);
		copy[i][cols] = '\0';
	}
	path = queue_create();
	if (!path)
	{
		for (i = 0; i < rows; i++)
			free(copy[i]);
		free(copy);
		return (NULL);
	}
	if (!backtrack(copy, rows, cols, start->x, start->y, path))
	{
		queue_delete(path);
		path = NULL;
	}
	for (i = 0; i < rows; i++)
		free(copy[i]);
	free(copy);
	return (path);
}
