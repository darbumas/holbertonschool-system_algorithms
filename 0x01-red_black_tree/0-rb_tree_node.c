#include "rb_trees.h"

/**
 * rb_tree_node - creates a Red-Black Tree node
 * @parent: pointer to the parent node of the node to create
 * @value: value to insert in the new node
 * @color: color of the node
 * Return: pointer to the newly created node, NULL otherwise
 */
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *new_node = malloc(sizeof(rb_tree_t));

	if (!new_node)
		return (NULL);

	new_node->color = color;
	new_node->parent = parent;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->n = value;

	return (new_node);
}
