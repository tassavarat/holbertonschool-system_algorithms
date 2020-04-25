#include "rb_trees.h"

/**
 * main - entry point
 *
 * Return: 0
 */
int main(void)
{
	rb_tree_t *tree;
	int array[] = {
		79, 47, 68, 87, 84, 91, 21, 32, 34, 2,
		20, 22
	};
	size_t n = sizeof(array) / sizeof(array[0]);
	int rm_val = 68;

	tree = array_to_rb_tree(array, n);
	if (!tree)
		return (1);
	puts("Initial tree");
	rb_tree_print(tree);
	tree = rb_tree_remove(tree, rm_val);
	printf("After removing %i\n", rm_val);
	rb_tree_print(tree);
	return (0);
}
