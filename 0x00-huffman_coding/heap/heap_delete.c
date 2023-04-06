#include "heap.h"

/**
 * delete_node - Recursively deletes nodes of a binary tree
 * @node: pointer to the node to delete
 * @_free: function pointer to a function that frees the content of a node
 */
static void delete_node(binary_tree_node_t *node, void (*_free)(void *))
{
	if (!node)
		return;

	delete_node(node->left, _free);
	delete_node(node->right, _free);

	if (_free)
		_free(node->data);
	free(node);
}

/**
 * heap_delete - Deallocates a heap
 * @heap: pointer to the heap to delete
 * @free_data: pointer to a function that will be used to free the content
 * of a node
 */
void heap_delete(heap_t *heap, void(*free_data)(void *))
{
	if (!heap)
		return;

	delete_node(heap->root, free_data);
	free(heap);
}
