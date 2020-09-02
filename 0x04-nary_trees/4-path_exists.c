#include "nary_trees.h"
#include <stdio.h>

/**
 * path_exists - check if path exists in n-ary tree
 * @root: pointer to root node of tree
 * @path: pointer to NULL termined array of strings
 *
 * Return: 1 if path is present, otherwise 0
 */
int path_exists(nary_tree_t const *root, char const * const *path)
{
	size_t i;

	if (!root || !path || !*path)
		return (0);
	for (i = 0; path[i]; ++i, root = root->children)
	{
		while (root && strcmp(root->content, path[i]) != 0)
			root = root->next;
		if (!root)
			return (0);
	}
	return (1);
}
