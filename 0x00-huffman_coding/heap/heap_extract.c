#include "heap/heap.h"

/**
 * get_height - Finds the height of the Binary Tree
 * @size: size of the tree
 *
 * Return: size
 */
static size_t get_height(size_t size)
{
	size_t height = 0;

	while ((size_t)(1 << height) <= (size + 1))
		height++;
	return (height - 1);
}

/**
 * get_last_node - Finds the last node
 * @heap: pointer to the heap
 *
 * Return: pointer to the last node
 */
static binary_tree_node_t *get_last_node(heap_t *heap)
{
	size_t size, height, bit;
	binary_tree_node_t *node;

	if (heap->size == 0)
		return (NULL);
	size = heap->size - 1;
	height = get_height(size);
	bit = 1 << (height - 1);
	node = heap->root;

	while (bit > 1)
	{
		bit >>= 1;
		if (size & bit)
			node = node->right;
		else
			node = node->left;
	}
	return (node);
}

/**
 * bubble_down - Maintains the Min Heap properties
 * @heap: pointer to the heap
 * @node: pointer to the Binary Tree node
 */
static void bubble_down(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *smallest_child = NULL;
	void *tmp_data;

	while (1)
	{
		if (node->left && (!node->right ||
			heap->data_cmp(node->left->data, node->right->data) < 0))
			smallest_child = node->left;
		else if (node->right)
			smallest_child = node->right;
		else
			break;
		if (heap->data_cmp(node->data, smallest_child->data) > 0)
		{
			tmp_data = node->data;
			node->data = smallest_child->data;
			smallest_child->data = tmp_data;
			node = smallest_child;
		}
		else
			break;
	}
}

/**
 * detach_last_node - Detaches the last node from its parent while updating the
 * parent's left and right pointers accordingly
 * @heap: pointer to the heap
 * @last_node: pointer to the last node to detach
 */
static void detach_last_node(heap_t *heap, binary_tree_node_t *last_node)
{
	if (!heap || !last_node)
		return;
	if (last_node->parent->right == last_node)
		last_node->parent->right = NULL;
	else
		last_node->parent->left = NULL;
}

/**
 * heap_extract - Extracts the root value of a Min Binary Heap
 * @heap: pointer to the heap from which to extract the value
 *
 * Return: pointer to the data that was stored in the root node of the heap
 */
void *heap_extract(heap_t *heap)
{
	void *root_data;
	binary_tree_node_t *last_node;

	if (!heap || !heap->root)
		return (NULL);

	root_data = heap->root->data;

	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
	}
	else
	{
		last_node = get_last_node(heap);
		if (last_node == heap->root->left ||
			last_node == heap->root->right)
		{
			if (last_node->parent->left == last_node)
				last_node->parent->left = NULL;
		}
		else
			detach_last_node(heap, last_node);
		heap->root->data = last_node->data;
		free(last_node);
		bubble_down(heap, heap->root);
	}
	heap->size--;
	return (root_data);
}
