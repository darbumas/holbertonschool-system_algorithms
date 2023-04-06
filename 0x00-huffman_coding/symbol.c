#include "huffman.h"

/**
 * symbol_create - Creates a `symbol_t` data structure
 * @data: character to be stored in the structure
 * @freq: associated frequency of the character
 * Return: pointer to the created structure, NULL otherwise
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *symbol = malloc(sizeof(symbol_t));

	if (!symbol)
		return (NULL);
	symbol->data = data;
	symbol->freq = freq;

	return (symbol);
}
