#include "nary_trees.h"

/**
 * nary_tree_delete - deallocates an entire N-ary tree.
 *
 * @tree: pointer to the root node of the tree
 */
void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *child, *sibling;

	if (!tree)
		return;

	/* Recursively deallocate children nodes */
	child = tree->children;
	while (child)
	{
		sibling = child->next;
		nary_tree_delete(child);
		child = sibling;
	}

	/* Deallocate the content of the node */
	if (tree->content)
		free(tree->content);

	/* Deallocate the node itself */
	free(tree);
}
