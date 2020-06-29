#include "huffman.h"

/**
 * huffman_extract_and_insert - combine the frequencies of two nodes together
 * @priority_queue: pointer to priority queue to have nodes combined
 *
 * Extra node will be removed, min-heap property is maintained. Newly created
 * node will have extracted nodes as its children
 * Return: 1 on success or 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node, *l_node, *r_node;
	size_t sum;
	symbol_t *symbol;

	if (!priority_queue || priority_queue->size < 2)
		return (0);
	l_node = heap_extract(priority_queue);
	r_node = heap_extract(priority_queue);
	sum = ((symbol_t *)l_node->data)->freq;
	sum += ((symbol_t *)r_node->data)->freq;
	symbol = symbol_create(-1, sum);
	if (!symbol)
		return (0);
	l_node->parent = r_node->parent = node = binary_tree_node(NULL, symbol);
	node->left = l_node, node->right = r_node;
	return (heap_insert(priority_queue, node) != NULL);
}
