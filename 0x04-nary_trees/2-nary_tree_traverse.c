#include "nary_trees.h"

/**
 * nary_tree_traverse - traverse through n-ary tree while calling function ptr
 * @root: pointer to root node of tree
 * @action: pointer to function to call for each node being traversed
 *	node: pointer to current node
 *	depth: depth of current node
 *
 * Return: maximum depth of tree
 */
size_t nary_tree_traverse(nary_tree_t const *root,
		void (*action)(nary_tree_t const *node, size_t depth))
{
	static size_t depth, max_depth;

	if (max_depth < depth)
		max_depth = depth;
	while (root)
	{
		action(root, depth);
		++depth;
		nary_tree_traverse(root->children, action);
		root = root->next;
	}
	--depth;
	return (max_depth);
}
