#include "nary_trees.h"
#include <stdio.h>

size_t common_ancestor(depth_info_t *diam)
{
	size_t depth1 = diam->depth1, depth2 = diam->depth2;
	nary_tree_t *p1 = diam->max1, *p2 = diam->max2;

	while (depth1 != depth2)
	{
		if (depth1 > depth2)
			--depth1, p1 = p1->parent;
		else if (depth2 > depth1)
			--depth2, p2 = p2->parent;
	}
	/* printf("depth1: %lu\ndepth2: %lu\n", depth1, depth2); */
	while (p1 != p2)
		--depth1, p1 = p1->parent, p2 = p2->parent;
	/* printf("depth1: %lu\np1: %s\np2: %s\n", depth1, p1->content, p2->content); */
	return (diam->depth1 + diam->depth2 - 2 * depth1 + 1);
}

depth_info_t tree_depth(nary_tree_t const *root, depth_info_t *diam)
{
	static size_t depth;
	static nary_tree_t *parent;

	if (root)
		parent = (nary_tree_t *)root->parent;
	while (root)
	{
		++depth;
		tree_depth(root->children, diam);
		root = root->next;
	}
	if (diam->max1 != parent)
	{
		if (diam->depth1 <= depth)
		{
			diam->depth2 = diam->depth1, diam->depth1 = depth;
			diam->max2 = diam->max1, diam->max1 = parent;
		}
		else if (diam->depth2 < depth)
		{
			diam->depth2 = depth, diam->max2 = parent;
		}
	}
	if (depth == 0)
	{
		diam->max1 = diam->max1->children;
		diam->max2 = diam->max2->children;
	}
	else
	{
		--depth;
	}
	return (*diam);
}

size_t nary_tree_diameter(nary_tree_t const *root)
{
	depth_info_t diam;

	if (!root)
		return (0);
	memset(&diam, 0, sizeof(diam));
	tree_depth(root, &diam);
	/* printf("depth: %lu\n", diam.depth1); */
	/* printf("depth2: %lu\n", diam.depth2); */
	/* printf("max1: %s\n", diam.max1->content); */
	/* printf("max2: %s\n", diam.max2->content); */
	return (common_ancestor(&diam));
}
