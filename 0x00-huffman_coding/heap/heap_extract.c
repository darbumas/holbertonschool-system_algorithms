#include "heap.h"

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
 * bubble_down - ensures that the min-heap property is maintained after
 * extracting the root node
 * @heap: pointer to the heap
 * @node: pointer to the node to start bubbling down from
 */
static void bubble_down(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *smallest_child;
	void *tmp_data;

	while (node->left)
	{
		smallest_child = node->left;
		if (node->right && heap->data_cmp(node->right->data, node->left->data) < 0)
		{
			smallest_child = node->right;
		}

		if (heap->data_cmp(smallest_child->data, node->data) >= 0)
			break;

		tmp_data = node->data;
		node->data = smallest_child->data;
		smallest_child->data = tmp_data;
		node = smallest_child;
	}
}

/**
 * get_last_node - Finds the last node in the heap
 * @heap: pointer to the heap
 *
 * Return: pointer to the last node in the heap
 */
static binary_tree_node_t *get_last_node(heap_t *heap)
{
	size_t size, height, bit;
	binary_tree_node_t *node = NULL;

	if (heap->size == 0)
		return (NULL);

	size = heap->size;
	height = get_height(size);
	bit = 1 << (height - 1);
	node = heap->root;

	while (bit > 1)
	{
		bit >>= 1;
		if ((size & bit) || ((size >> 1) & bit))
			node = node->right;
		else
			node = node->left;
	}
	return (node);
}

/**
 * detach_last_node - Detaches the last node in the heap
 * @heap: pointer to the heap
 * @last_node: pointer to the last node in the heap
 */
static void detach_last_node(heap_t *heap, binary_tree_node_t *last_node)
{
	if (!heap || !last_node)
		return;
	if (last_node->parent)
	{
		if (last_node->parent->left == last_node)
			last_node->parent->left = NULL;
		else
			last_node->parent->right = NULL;
	}
	last_node->parent = NULL;
}

/**
 * heap_extract - Extracts the root value of a Min Binary Heap
 * @heap: pointer to the heap
 *
 * Return: pointer to the data that was stored in the root node of the heap
 */
void *heap_extract(heap_t *heap)
{
	void *data = NULL;
	binary_tree_node_t *last_node = NULL;

	if (!heap || !heap->root)
		return (NULL);

	data = heap->root->data;

	last_node = get_last_node(heap);
	detach_last_node(heap, last_node);

	if (heap->root != last_node)
	{
		last_node->left = heap->root->left;
		last_node->right = heap->root->right;
		if (last_node->left)
			last_node->left->parent = last_node;
		if (last_node->right)
			last_node->right->parent = last_node;
	}

	free(heap->root);
	heap->root = last_node;
	heap->size--;

	bubble_down(heap, last_node);

	return (data);
}
