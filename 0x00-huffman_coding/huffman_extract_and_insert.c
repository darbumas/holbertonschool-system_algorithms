#include "huffman.h"

/**
 * huffman_extract_and_insert - Extracts two nodes from the priority queue
 * and inserts a new one with the sum of their frequencies
 * @priority_queue: pointer to the priority queue
 *
 * Return: 1 on success, or 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node1, *node2, *new_node;
    binary_tree_node_t *extracted_node1, *extracted_node2;
    symbol_t *symbol1, *symbol2, *new_symbol;
    size_t sum_freq;

    if (!priority_queue)
        return 0;

    extracted_node1 = heap_extract(priority_queue);
    extracted_node2 = heap_extract(priority_queue);

    if (!extracted_node1 || !extracted_node2)
    {
        if (extracted_node1)
            free(extracted_node1->data), free(extracted_node1);
        if (extracted_node2)
            free(extracted_node2->data), free(extracted_node2);
        return 0;
    }

    node1 = (binary_tree_node_t *)extracted_node1->data;
    node2 = (binary_tree_node_t *)extracted_node2->data;
    symbol1 = (symbol_t *)node1->data;
    symbol2 = (symbol_t *)node2->data;
    sum_freq = symbol1->freq + symbol2->freq;

    new_symbol = symbol_create(-1, sum_freq);
    if (!new_symbol)
    {
        free(extracted_node1->data), free(extracted_node1);
        free(extracted_node2->data), free(extracted_node2);
        return 0;
    }

    new_node = binary_tree_node(NULL, new_symbol);
    if (!new_node)
    {
        free(extracted_node1->data), free(extracted_node1);
        free(extracted_node2->data), free(extracted_node2);
        free(new_symbol);
        return 0;
    }

    new_node->left = node1;
    new_node->right = node2;

    node1->parent = new_node;
    node2->parent = new_node;

    if (!heap_insert(priority_queue, binary_tree_node(NULL, new_node)))
    {
        free(extracted_node1->data), free(extracted_node1);
        free(extracted_node2->data), free(extracted_node2);
        free(new_symbol);
        free(new_node);
        return 0;
    }

    free(extracted_node1);
    free(extracted_node2);

    return 1;
}
