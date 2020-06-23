#include "heap.h"

/**
 * binary_tree_node - create generic binary tree node
 * @parent: pointer to parent of node being created
 * @data: data to store in node
 *
 * Return: pointer to created node, NULL on failure
 */
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *node = malloc(sizeof(*node));

	if (!node)
		return (NULL);
	node->data = data;
	node->left = node->right = NULL;
	node->parent = parent;
	return (node);
}
