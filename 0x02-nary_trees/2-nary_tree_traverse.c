#include "nary_trees.h"

/**
 * nary_depth_first_traverse - helper ƒ() to traverses N-ary tree using DFS
 * algorithm
 * @node: pointer to the root node of the tree
 * @depth: depth of the current node
 * @action: pointer to a function to execute for each node being traversed
 * Return: maximum depth
 */
size_t nary_depth_first_traverse(nary_tree_t const *node, size_t depth,
		void (*action)(nary_tree_t const *node, size_t depth))
{
	nary_tree_t const *child;
	size_t current_d, max_d;

	if (!node)
		return (depth);

	/* Execute the action for the current node */
	action(node, depth);

	/* Traverse the children nodes */
	child = node->children;
	max_d = depth;

	while (child)
	{
		current_d = nary_depth_first_traverse(child, depth + 1, action);
		if (current_d > max_d)
			max_d = current_d;
		child = child->next;
	}
	return (max_d);
}

/**
 * nary_tree_traverse - traverses an N-ary tree node by node
 * @root: pointer to the root node of the tree to traverse
 * @action: pointer to a function to execute for each node being traversed.
 *	Its arguments being:
 *		- node: pointer to the node being traversed
 *		- depth: depth of the node being traversed
 *
 * Return: the maximum depth of the tree pointed to by root.
 */
size_t nary_tree_traverse(nary_tree_t const *root,
		void (*action)(nary_tree_t const *node, size_t depth))
{
	return (nary_depth_first_traverse(root, 0, action));
}
