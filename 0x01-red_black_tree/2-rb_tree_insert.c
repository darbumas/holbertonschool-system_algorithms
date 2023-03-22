#include "rb_trees.h"

/**
 * left_rotate - rotates the tree to the left around a given node
 * @tree: double pointer to the root node of the tree
 * @x: the node around which to rotate the tree
 */
void left_rotate(rb_tree_t **tree, rb_tree_t *x)
{
	rb_tree_t *y = x->right;

	x->right = y->left;
	if (y->left)
		y->left->parent = x;
	y->parent = x->parent;

	if (!x->parent)
		*tree = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

/**
 * right_rotate - rotates the tree to the right around a given node
 * @tree: double pointer to the root node of the tree
 * @y: the node around which to rotate the tree
 */
void right_rotate(rb_tree_t **tree, rb_tree_t *y)
{
	rb_tree_t *x = y->left;
	
	y->left = x->right;
	if (x->right)
		x->right->parent = y;
	x->parent = y->parent;
	if (!y->parent)
		*tree = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;
	x->right = y;
	y->parent = x;
}

/**
 * rb_tree_insert - inserts a value in a Red-Black Tree
 * @tree: double pointer to the root node of the Red-Black Tree
 * @value: value to store in the node to be inserted
 * Return: pointer to the created node; NULL otherwise
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new_node = NULL, *parent = NULL, *grd_parent = NULL;
	rb_tree_t *uncle = NULL;
	rb_color_t new_node_color = RED;

	if (!tree)
		return (NULL);

	/* Find appropriate position for the new node */
	parent = *tree;
	while (parent)
	{
		if (value == parent->n)
			return (NULL);
		grd_parent = parent;
		if (value < parent->n)
			parent = parent->left;
		else
			parent = parent->right;
	}

	/* Create the new node and attach it to the tree */
	new_node = rb_tree_node(grd_parent, value, new_node_color);
	if (!new_node)
		return (NULL);
	if (!grd_parent)
		*tree = new_node;
	else if (value < grd_parent->n)
		grd_parent->left = new_node;
	else
		grd_parent->right = new_node;

	/* Rebalance the tree */
	while (new_node != *tree && new_node->parent->color == RED)
	{
		grd_parent = new_node->parent->parent;
		if(new_node->parent == grd_parent->left)
		{
			uncle = grd_parent->right;
			if (uncle && uncle->color == RED)
			{
				new_node->parent->color = BLACK;
				uncle->color = BLACK;
				grd_parent->color = RED;
				new_node = grd_parent;
			}
			else
			{
				if (new_node == new_node->parent->right)
				{
					new_node = new_node->parent;
					left_rotate(tree, new_node);
				}
				new_node->parent->color = BLACK;
				grd_parent->color = RED;
				right_rotate(tree, grd_parent);
			}
		}
		else
		{
			uncle = grd_parent->left;
			if (uncle && uncle->color == RED)
			{
				new_node->parent->color = BLACK;
				uncle->color = BLACK;
				grd_parent->color = RED;
				new_node = grd_parent;
			}
			else
			{
				if (new_node == new_node->parent->left)
				{
					new_node = new_node->parent;
					right_rotate(tree, new_node);
				}
				new_node->parent->color = BLACK;
				grd_parent->color = RED;
				left_rotate(tree, grd_parent);
			}
		}
	}
	(*tree)->color = BLACK;
	return (new_node);
}
