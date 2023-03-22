#include "rb_trees.h"

/**
 * array_to_rb_tree - builds a BST from an array
 * @array: pointer to the first element of the array to be converted
 * @size: number of elements in the array
 * Return: pointer to the root node of the created RB-Tree, NULL otherwise
 */
rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
	rb_tree_t *root = NULL, *temp = NULL;
	size_t i;

	if (!array || size <= 0)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		temp = rb_tree_insert(&root, array[i]);
		if (!temp && !root)
			return (NULL);
	}
	return (root);
}
