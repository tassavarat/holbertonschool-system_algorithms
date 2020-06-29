#include "huffman.h"

/**
 * free_data - free contents of data
 * @p: pointer to data
 */
void free_data(void *p)
{
	if (!p)
		return;
	free(p);
}

/**
 * print_codes - print character along with its corresponding Huffman code
 * @data: stored character
 * @codes: pointer to array of characters
 * @size: stopping point for printing
 */
void print_codes(char data, char *codes, size_t size)
{
	size_t i;

	printf("%c: ", data);
	for (i = 0; i < size; ++i)
		printf("%c", codes[i]);
	putchar('\n');
}

/**
 * find_leaves - find leaf nodes and calls print_codes each time leaf is found
 * @node: pointer to Huffman tree node
 * @codes: pointer to array of characters
 * @i: index for codes array
 */
void find_leaves(binary_tree_node_t *node, char *codes, size_t i)
{
	if (!node)
		return;
	if (!node->left && !node->right)
		print_codes(((symbol_t *)node->data)->data, codes, i);
	if (node->left)
	{
		codes[i] = '0';
		find_leaves(node->left, codes, i + 1);
	}
	if (node->right)
	{
		codes[i] = '1';
		find_leaves(node->right, codes, i + 1);
	}
}

/**
 * huffman_codes - build Huffman tree and print resulting symbol codes
 * @data: array of characters
 * @freq: array of associated character frequencies
 * @size: size of both arrays
 *
 * Return: 1 on success or 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *h_tree;
	char *codes;

	if (!data || !freq || !size)
		return (0);
	h_tree = huffman_tree(data, freq, size);
	if (!h_tree)
		return (0);
	codes = calloc(size, sizeof(char));
	find_leaves(h_tree, codes, 0);
	free_tree(h_tree, free_data);
	free(codes);
	return (1);
}
