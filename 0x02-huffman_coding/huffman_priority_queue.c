#include "huffman.h"

/**
 * compar - compare two frequencies
 *
 * @p1: first pointer to binary_tree_node_t node
 * @p2: second pointer to binary_tree_node_t node
 *
 * Return: difference between the two frequencies
 */
int compar(void *p1, void *p2)
{
	symbol_t *sym1, *sym2;

	sym1 = ((binary_tree_node_t *)p1)->data;
	sym2 = ((binary_tree_node_t *)p2)->data;
	return (sym1->freq - sym2->freq);
}

/**
 * huffman_priority_queue - create priority queue for Huffman coding algorithm
 * @data: array of characters
 * @freq: array of associated character frequencies
 * @size: size of both arrays
 *
 * Return: pointer to created priority queue (min heap) or NULL on failure
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	symbol_t *symbol;
	binary_tree_node_t *node;
	size_t i;

	if (!data || !freq || !size)
		return (NULL);
	heap = heap_create(compar);
	if (!heap)
		return (NULL);
	for (i = 0; i < size; ++i)
	{
		symbol = symbol_create(data[i], freq[i]);
		if (!symbol)
			return (NULL);
		node = heap_insert(heap, binary_tree_node(NULL, symbol));
		if (!node)
			return (NULL);
	}
	return (heap);
}
