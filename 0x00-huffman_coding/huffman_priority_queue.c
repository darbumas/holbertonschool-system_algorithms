#include "huffman.h"

/**
 * symbol_cmp - Compares two symbol_t structures based on frequency
 * @ptr1: First pointer to symbol_t structure
 * @ptr2: Second pointer to symbol_t structure
 *
 * Return: Difference between the two symbol_t frequencies
 */
int symbol_cmp(void *ptr1, void *ptr2)
{
	symbol_t *s1 = (symbol_t *)ptr1;
	symbol_t *s2 = (symbol_t *)ptr2;

	return (s1->freq - s2->freq);
}

/**
 * huffman_priority_queue - Creates a priority queue for the Huffman
 * coding algorithm
 * @data: An array of characters of size 'size'
 * @freq: An array containing the associated frequencies (of size 'size' too)
 * @size: The size of the 'data' and 'freq' arrays
 *
 * Return: A pointer to the created min heap (priority queue)
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *p_q;
	symbol_t *symbol;
	binary_tree_node_t *node;
	size_t i;
	
	if (!data || !freq || size == 0)
		return (NULL);

	p_q = heap_create(symbol_cmp);
	if (!p_q)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		if (!symbol)
		{
			heap_delete(p_q, free);
			return (NULL);
		}

		node = binary_tree_node(NULL, symbol);
		if (!node)
		{
			free(symbol);
			heap_delete(p_q, free);
			return (NULL);
		}
		if (!heap_insert(p_q, node))
		{
			free(symbol);
			free(node);
			heap_delete(p_q, free);
			return (NULL);
		}
	}
	return (p_q);
}
