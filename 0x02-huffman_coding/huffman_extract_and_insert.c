#include "huffman.h"

/**
 * huffman_extract_and_insert - combine the frequencies of two nodes together
 * @priority_queue: pointer to priority queue to have nodes combined
 *
 * Extra node will be removed, min-heap property is maintained
 * Return: 1 on success or 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	size_t sum;
	symbol_t *symbol;

	if (!priority_queue)
		return (0);
	sum = ((symbol_t *)((binary_tree_node_t *)
				heap_extract(priority_queue))->data)->freq;
	sum += ((symbol_t *)((binary_tree_node_t *)
				heap_extract(priority_queue))->data)->freq;
	symbol = symbol_create(-1, sum);
	if (!symbol)
		return (0);
	return (heap_insert(priority_queue, binary_tree_node(NULL, symbol)) != NULL);
}
