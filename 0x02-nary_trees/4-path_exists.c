#include "nary_trees.h"

/**
 * path_exists - checks if a path exists in an N-ary tree
 * @root: pointer to the root node of the tree
 * @path: NULL terminated array of strings representing the path to check
 *
 * Return: 1 if the path exists, 0 otherwise
 */
int path_exists(nary_tree_t const *root, char const * const *path)
{
	size_t depth = 0;
	nary_tree_t const *node = root;

	/* traverse the tree according to passed path */
	while (path[depth])
	{
	/* search the children of current node for a child with the content */
		while (node)
		{
			if (strcmp(node->content, path[depth]) == 0)
			{
			/* If leaf node is reached return success */
				if (path[depth + 1] == NULL)
					return (1);
				node = node->children;
				depth++;
				break;
			}
			/* move to the next child in the linked list */
			node = node->next;
		}
		if (!node)
			return (0);
	}
	return (0);
}
