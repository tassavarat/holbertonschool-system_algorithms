#include "huffman.h"

/**
 * symbol_create - create symbol_t data structure
 * @data: data to store in the struct
 * @freq: associated frequency
 *
 * Return: pointer to created structure or NULL on failure
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *symbol = malloc(sizeof(*symbol));

	if (!symbol)
		return (NULL);
	symbol->data = data;
	symbol->freq = freq;
	return (symbol);
}
