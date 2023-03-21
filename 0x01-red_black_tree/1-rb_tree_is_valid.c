#include "rb_trees.h"

/**
 * is_red - validates color RED of a node
 * @node: the node to check
 * Return: 1 if node is red, 0 otherwise
 */
int is_red(rb_tree_t *node)
{
	return (node != NULL && node->color == RED);
}

/**
 * is_black - validates color BLACK of a node
 * @node: the node to check
 * Return: 1 if node is black, 0 otherwise
 */
int is_black(rb_tree_t *node)
{
	return (node == NULL || node->color == BLACK);
}

/**
 * count_black - counts number of black nodes in a red-black tree
 * @tree: pointer to the root of the tree
 * Return: the count
 */
int count_black(rb_tree_t *tree)
{
	int count = 0;

	while (tree)
	{
		if (tree->color == BLACK)
			count++;
		tree = tree->left;
	}
	return (count);
}

/**
 * recursive_validate_rb - validates that there are no two adjacent red nodes,
 * and that every path from the root to a leaf node has the same number of
 * black nodes.
 *
 * @root: pointer to the root of the tree
 * @black_count: pointer to int to keep track of number of black nodes
 * Return: 1 if conditions are satisfied, 0 otherwise
 */
int recursive_validate_rb(rb_tree_t *root, int *black_count)
{
	int l_black, r_black;

	if (!root)
	{
		*black_count = 1;
		return (1);
	}
	/* If the node is red, check that both of its children are black */
	if (!is_black(root))
	{
		if (is_red(root->left) || is_red(root->right))
			return (0);
	}
	/* recursively check left/right subtree */
	if (!recursive_validate_rb(root->left, &l_black) ||
	    !recursive_validate_rb(root->right, &r_black))
		return (0);
	/* Check that the number of black nodes on any path is the same */
	if (l_black != r_black)
		return (0);
	/* set number of black node +1  if current node is black */
	*black_count = l_black + (is_black(root) ? 1 : 0);
	return (1);
}

/**
 * rb_tree_is_valid - checks if a binary tree is a valid Red-Black Tree
 * @tree: pointer to the root node of the tree
 * Return: 1 if tree is a valid RB-Tree, 0 otherwise
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	int black_count;

	if (!tree)
		return (0);
	if (tree->color != BLACK)
		return (0);

	return (recursive_validate_rb((rb_tree_t *)tree, &black_count));
}
