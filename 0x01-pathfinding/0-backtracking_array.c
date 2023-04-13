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
 * @start: the starting point
 * @target: the target point
 * @path: pointer to the queue storing path
 * Return: 1 if path found, otherwise 0
 */
static int backtrack(char **map, int rows, int cols, int x, int y,
		point_t *start, point_t *target, queue_t *path)
{
	point_t *point;

	if (x < 0 || x >= cols || y < 0 || y >= rows || map[y][x] == '1')
		return (0);

	printf("Checking coordinates [%d, %d]\n", x, y);

	if (x == target->x && y == target->y)
	{
		point = malloc(sizeof(point_t));
		if (!point)
			return (0);
		point->x = x;
		point->y = y;
		queue_push_front(path, point);
			return (1);
	}
	/* Mark cell as visited */
	map[y][x] = '1';

	/* Visit neighbor cells in RBLT order */
	if (backtrack(map, rows, cols, x + 1, y, start, target, path) ||
		backtrack(map, rows, cols, x, y + 1, start, target, path) ||
		backtrack(map, rows, cols, x - 1, y, start, target, path) ||
		backtrack(map, rows, cols, x, y - 1, start, target, path))
	{
		point = malloc(sizeof(point_t));
		if (!point)
			return (0);
		point->x = x;
		point->y = y;
		queue_push_front(path, point);
		return (1);
	}
	map[y][x] = '0';

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
	int i, j;

	if (!map || !start || !target)
		return (NULL);
	path = queue_create();
	if (!path)
		return (NULL);
	/* A bit redundant but operate on a copy of map */
	copy = malloc(rows * sizeof(char *));
	if (!copy)
	{
		queue_delete(path);
		return (NULL);
	}
	for (i = 0; i < rows; i++)
	{
		copy[i] = malloc(cols + 1);
		if (!copy[i])
		{
			for (j = 0; j < i; j++)
				free(copy[j]);
			free(copy);
			queue_delete(path);
			return (NULL);
		}
		strncpy(copy[i], map[i], cols);
	}
	if (!backtrack(copy, rows, cols, start->x, start->y, (point_t *)start,
		(point_t *)target, path))
	{
		queue_delete(path);
		path = NULL;
	}
	for (i = 0; i < rows; i++)
		free(copy[i]);
	free(copy);

	return (path);
}
