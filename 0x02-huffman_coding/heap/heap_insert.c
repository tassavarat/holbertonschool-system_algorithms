#include "heap.h"

/**
 * min_heapify - min heapifies a tree
 * @data_cmp: pointer to function comparing data of two nodes
 * @node: pointer to inserted node
 *
 * Return: pointer to node containing data value of inserted node
 */
binary_tree_node_t *min_heapify(int (*data_cmp)(void *, void *),
		binary_tree_node_t *node)
{
	void *tmp;

	while (node->parent && data_cmp(node->data, node->parent->data) < 0)
	{
		tmp = node->parent->data;
		node->parent->data = node->data;
		node->data = tmp;
		node = node->parent;
	}
	return (node);
}

/**
 * n_node - find n-th node (BFS order) of tree
 * @node: pointer to root node
 * @n: one-indexed n-th node to find
 *
 * Return: pointer to specified node or last node in tree if n greater than
 * number of nodes in tree
 */
binary_tree_node_t *n_node(binary_tree_node_t *node, int n)
{
	int bit_idx, mask;

	for (bit_idx = 0; 1 << (bit_idx + 1) <  n; ++bit_idx)
		;
	for (--bit_idx; bit_idx >= 0; --bit_idx)
	{
		mask = 1 << bit_idx;
		if (n & mask)
		{
			if (node->right)
				node = node->right;
			else
				break;
		}
		else
		{
			if (node->left)
				node = node->left;
			else
				break;
		}
	}
	return (node);
}

/**
 * heap_insert - insert node into a min binary heap
 * @heap: pointer to heap to insert node into
 * @data: pointer to data to store in node
 *
 * Return: pointer to created node, NULL on failure
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *node;

	if (!heap || !data)
		return (NULL);
	if (!heap->root)
	{
		heap->root = node = binary_tree_node(NULL, data);
		if (!node)
			return (NULL);
		++heap->size;
	}
	else
	{
		node = n_node(heap->root, ++heap->size);
		if (!node->left)
			node = node->left = binary_tree_node(node, data);
		else
			node = node->right = binary_tree_node(node, data);
	}
	if (!node)
		return (NULL);
	return (min_heapify(heap->data_cmp, node));
}
