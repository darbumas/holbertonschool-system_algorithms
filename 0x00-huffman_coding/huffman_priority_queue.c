#include "huffman.h"

/**
 * symbol_cmp - Compares two symbol_t structures based on frequency
 * @p1: First pointer to symbol_t structure
 * @p2: Second pointer to symbol_t structure
 *
 * Return: Difference between the two symbol_t frequencies
 */
int symbol_cmp(void *p1, void *p2)
{
	symbol_t *s1 = (symbol_t *)p1;
	symbol_t *s2 = (symbol_t *)p2;

	return (s1->freq - s2->freq);
}

/**
 * huffman_priority_queue - Creates a priority queue for the Huffman coding
 * algorithm
 * @data: An array of characters of size 'size'
 * @freq: An array containing the associated frequencies (of size 'size' too)
 * @size: The size of the 'data' and 'freq' arrays
 *
 * Return: A pointer to the created min heap (priority queue)
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue;
	symbol_t *symbol;
	binary_tree_node_t *node;
	size_t i;

	priority_queue = heap_create(symbol_cmp);
	if (!priority_queue)
		return (NULL);

	for (i = 0; i < size; ++i)
	{
		symbol = symbol_create(data[i], freq[i]);
		if (!symbol)
		{
			heap_delete(priority_queue, free);
			return (NULL);
		}

		node = binary_tree_node(NULL, symbol);
		if (!node)
		{
			free(symbol);
			heap_delete(priority_queue, free);
			return (NULL);
		}

		if (!heap_insert(priority_queue, node))
		{
			free(symbol);
			free(node);
			heap_delete(priority_queue, free);
			return (NULL);
		}
	}

	return (priority_queue);
}

