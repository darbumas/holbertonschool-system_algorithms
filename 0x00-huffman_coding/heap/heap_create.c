#include "heap.h"

/**
 * heap_create - Creates a Heap data structure
 * @data_cmp: pointer to a comparison function
 *
 * Return: pointer to the created heap structure; NULL otherwise
 */
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *heap = malloc(sizeof(heap_t));

	if (!heap)
		return (NULL);

	heap->size = 0;
	heap->data_cmp = data_cmp;
	heap->root = NULL;

	return (heap);
}
