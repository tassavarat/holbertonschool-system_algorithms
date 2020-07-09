#include "heap.h"

/**
 * restore_heapify - restore heap property for binary tree
 * @data_cmp: pointer to function determining whether to min or max heapify
 * @node: pointer to root node
 *
 * Return: pointer to tree node containing data of original node
 * or NULL on error
 */
binary_tree_node_t *restore_heapify(int (*data_cmp)(void *, void *),
		binary_tree_node_t *node)
{
	binary_tree_node_t *lg;

	if (!data_cmp || !node)
		return (NULL);
	do {
		lg = NULL;
		if (node->left && data_cmp(node->data, node->left->data) >= 0)
			lg = node->left;
		if (node->right && data_cmp(node->data, node->right->data) >= 0 &&
				(!lg || data_cmp(lg->data, node->right->data) > 0))
			lg = node->right;
		if (lg)
			node = swap_nodes(node, lg);
	} while (lg);
	return (node);
}

/**
 * extract_root - swaps data of root and last node in tree
 * @heap: pointer to heap to extract root from
 *
 * node containing original data of root will be freed
 *
 * Return: data of exactracted root node
 */
void *extract_root(heap_t *heap)
{
	binary_tree_node_t *node;
	void *data;

	node = n_node(heap->root, heap->size);
	if (node->parent)
	{
		data = swap_nodes(heap->root, node)->data;
		if (node->parent->left == node)
			node->parent->left = NULL;
		else
			node->parent->right = NULL;
	}
	else
	{
		data = heap->root->data;
		heap->root = NULL;
	}
	free(node);
	if (--heap->size == 0)
		heap->root = NULL;
	return (data);
}

/**
 * heap_extract - extract root value from binary heap and restore heap property
 * @heap: pointer to heap to extract from
 *
 * Return: pointer to data stored in extracted root node or NULL on error
 */
void *heap_extract(heap_t *heap)
{
	void *data;

	if (!heap)
		return (NULL);
	data = extract_root(heap);
	restore_heapify(heap->data_cmp, heap->root);
	return (data);
}
