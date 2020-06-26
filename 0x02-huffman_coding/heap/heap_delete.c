#include "heap.h"

/**
 * free_tree - free all nodes in a binary tree
 * @node: pointer to root node
 * @free_data: pointer to function used to free node content
 */
void free_tree(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (!node)
		return;
	free_tree(node->left, free_data);
	free_tree(node->right, free_data);
	if (free_data)
		free_data(node->data);
	free(node);
}

/**
 * heap_delete - deallocate a heap
 * @heap: pointer to heap to delete
 * @free_data: pointer to function used to free node content
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (!heap)
		return;
	free_tree(heap->root, free_data);
	free(heap);
}
