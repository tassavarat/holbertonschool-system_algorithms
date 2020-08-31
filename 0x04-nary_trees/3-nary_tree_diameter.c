#include "nary_trees.h"

/**
 * common_ancestor - set common ancestor to given depth_info_t struct
 * @diam: pointer to depth_info_t struct to set
 */
void common_ancestor(depth_info_t *diam)
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
	while (p1 != p2)
		--depth1, p1 = p1->parent, p2 = p2->parent;
	diam->ancestor_depth = depth1;
}

/**
 * tree_depth - set relevant depth information to given depth_info_t struct
 * @root: pointer to root node of tree
 * @diam: pointer to depth_info_t struct to set
 */
void tree_depth(nary_tree_t const *root, depth_info_t *diam)
{
	static size_t depth;
	static nary_tree_t *tmp;
	nary_tree_t *root_bak;

	if (root)
		root_bak = tmp = (nary_tree_t *)root;
	while (root)
	{
		++depth;
		tree_depth(root->children, diam);
		root = root->next;
	}
	if (diam->max1 != tmp->parent)
	{
		if (diam->depth1 <= depth)
		{
			diam->depth2 = diam->depth1, diam->depth1 = depth;
			diam->max2 = diam->max1, diam->max1 = tmp->parent;
		}
		else if (diam->depth2 < depth)
		{
			diam->depth2 = depth, diam->max2 = tmp->parent;
		}
	}
	if (depth == 0)
	{
		if (diam->max1)
			diam->max1 = diam->max1->children;
		else
			diam->depth1 = 1, diam->max1 = root_bak;
		if (diam->max2)
			diam->max2 = diam->max2->children;
		else
			diam->depth2 = 1, diam->max2 = root_bak;
	}
	else
	{
		--depth;
	}
}

/**
 * nary_tree_diameter - find diameter of n-ary tree
 * @root: pointer to root node
 *
 * Return: diameter of tree
 */
size_t nary_tree_diameter(nary_tree_t const *root)
{
	depth_info_t diam;

	if (!root)
		return (0);
	memset(&diam, 0, sizeof(diam));
	tree_depth(root, &diam);
	common_ancestor(&diam);
	return (diam.depth1 + diam.depth2 - 2 * diam.ancestor_depth + 1);
}
