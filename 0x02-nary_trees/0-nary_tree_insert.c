#include "nary_trees.h"

/**
 * nary_tree_insert - inserts a node in a N-ary tree.
 * @parent: pointer to the parent node
 * @str: the string to be stored in the created node
 *
 * Description: If parent is not NULL, the created node must be added at the
 * beginning of the parent's children linked list
 *
 * Return: pointer to the created node, otherwise NULL
 */
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *node = NULL;

	if (!str)
		return (NULL);

	node = malloc(sizeof(nary_tree_t));
	if (!node)
		return (NULL);

	/* Duplicate the given string and store it in the new node */
	node->content = strdup(str);
	if (!node->content)
	{
		free(node);
		return (NULL);
	}
	/* Set the parent of the new node */
	node->parent = parent;
	/* Initialize the number of children to 0 */
	node->nb_children = 0;

	/* Add the new node at the beginning of parent's children llst */
	if (parent)
	{
		node->next = parent->children;
		parent->children = node;
		parent->nb_children++;
	}
	else
	/* parent is NULL so... set the new node's next pointer to NULL */
		node->next = NULL;

	return (node);
}
