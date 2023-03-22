#include "rb_trees.h"

/**
 * left_rotate - rotates the tree to the left around a given node
 * @tree: double pointer to the root node of the tree
 * @x: the node around which to rotate the tree
 */
void left_rotate(rb_tree_t **tree, rb_tree_t *x)
{
	rb_tree_t *y = NULL;

	if (!x->right)
		return;

	y = x->right;
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
	rb_tree_t *x = NULL;

	if (!y->left)
		return;

	x = y->left;
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
 * fix_left_uncle_subtree - fixes Red-Black subtree relative to the left uncle
 * @tree: address of pointer to root node
 * @node: pointer to the inserted node to start to fix
 * Return: pointer to the inserted node
 */
rb_tree_t *fix_left_uncle_subtree(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *uncle = node->parent->parent->left;

	/* Case 1: Uncle is red */
	if (uncle && uncle->color == RED)
	{
		uncle->color = BLACK;
		node->parent->color = BLACK;
		node->parent->parent->color = RED;
		node = node->parent->parent;
	}
	else
	{
		/* Case 2: Node is a left child */
		if (node == node->parent->left)
		{
			node = node->parent;
			right_rotate(tree, node);
		}

		/* Case 3: Node is a right child */
		node->parent->color = BLACK;
		node->parent->parent->color = RED;
		left_rotate(tree, node->parent->parent);
	}
	return (node);
}

/**
 * fix_right_uncle_subtree - fixes Red-Black subtree relative to the right
 * uncle
 * @tree: address of pointer to root node
 * @node: pointer to the inserted node to start to fix
 * Return: pointer to the inserted node
 */
rb_tree_t *fix_right_uncle_subtree(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *uncle = node->parent->parent->right;

	/* Case 1: uncle is red */
	if (uncle && uncle->color == RED)
	{
		uncle->color = BLACK;
		node->parent->color = BLACK;
		node->parent->parent->color = RED;
		node = node->parent->parent;
	}
	else
	{
		/* Case 2: Node is right child */
		if (node == node->parent->right)
		{
			node = node->parent;
			left_rotate(tree, node);
		}

		/* Case 3: Node is a left child */
		node->parent->color = BLACK;
		node->parent->parent->color = RED;
		right_rotate(tree, node->parent->parent);
	}
	return (node);
}

/**
 * fix_rb_tree_properties - fixes red-black tree properties after insertion
 * @tree: address of pointer to root node
 * @node: pointer to the inserted node to start to fix
 * Return: pointer to the inseerted node
 */
rb_tree_t *fix_rb_tree_properties(rb_tree_t **tree, rb_tree_t *node)
{
	while (node->parent && node->parent->color == RED)
	{
		if (node->parent->parent->left == node->parent)
			node = fix_right_uncle_subtree(tree, node);
		else
			node = fix_left_uncle_subtree(tree, node);
	}
	(*tree)->color = BLACK;

	return (node);
}

/**
 * rb_tree_insert - inserts a node into a Red-Black Tree
 * @tree: address of pointer to root node
 * @value: new value to insert
 * Return: pointer to new node on success, NULL otherwise
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *node, *prev = NULL, *curr;

	if (!tree)
		return (NULL);

	/* Traverse the tree to find the correct position for the insert */
	curr = *tree;
	while (curr)
	{
		prev = curr;
		if (value < curr->n)
			curr = curr->left;
		else if (value > curr->n)
			curr = curr->right;
		else
			return (NULL);
	}

	/* Create the new node with the given value and color it red */
	node = rb_tree_node(prev, value, RED);
	if (!node)
		return (NULL);

	/* If there's no previous node, make the new node the root and black */
	if (!prev)
	{
		node->color = BLACK;
		return (*tree = node);
	}
	/* Assign the new node as the left or right child of the prev node */
	if (value < prev->n)
		prev->left = node;
	else
		prev->right = node;

	/* Fix RB-tree properties after insertion */
	fix_rb_tree_properties(tree, node);

	return (node);
}
