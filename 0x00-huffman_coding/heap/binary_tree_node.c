#include "heap.h"

/**
 * binary_tree_node - Creates a generic Binary Tree node
 * @parent: pointer to the parent node of the node to be created
 * @data: pointer to the data to be stored in the node
 * Return: pointer to the created node, NULL otherwise
 */
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *new_node = malloc(sizeof(binary_tree_node_t));

	if (!new_node)
		return (NULL);

	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = parent;

	return (new_node);
}
