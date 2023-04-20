#include "nary_trees.h"

/**
 * nary_tree_height - helper ƒ() to compute the height of an N-ary tree
 * @node: pointer to the current node
 *
 * Return: height
 */
size_t nary_tree_height(nary_tree_t const *node)
{
	size_t height, max_height = 0;
	nary_tree_t const *child;

	if (!node)
		return (0);

	for (child = node->children; child; child = child->next)
	{
		height = nary_tree_height(child);
		if (height > max_height)
			max_height = height;
	}
	return (max_height + 1);
}

/**
 * nary_tree_diameter - computes the diameter of an N-ary tree
 * @root: pointer to the root node of the N-ary tree
 *
 * Return: diameter of the tree pointed to by root
 */
size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t max_d, first_max, second_max, diameter, height, current_d;
	nary_tree_t const *child = NULL;

	if (!root)
		return (0);

	max_d = 0;
	first_max = 0;
	second_max = 0;

	for (child = root->children; child; child = child->next)
	{
		diameter = nary_tree_diameter(child);
		height = nary_tree_height(child);

		/* Update the maximum diameter found so far */
		if (diameter > max_d)
			max_d = diameter;

		/* Update the first and second largest heights */
		if (height > first_max)
		{
			second_max = first_max;
			first_max = height;
		}
		else if (height > second_max)
			second_max = height;
	}
	current_d = first_max + second_max + 1;

	return (max_d > current_d ? max_d : current_d);
}
