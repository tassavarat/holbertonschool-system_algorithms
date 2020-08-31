#include "nary_trees.h"
#include <stdio.h>

depth_info_t tree_depth(nary_tree_t const *root, depth_info_t *depth_s)
{
	/* static size_t depth, max_depth, max_depth2; */
	/* static nary_tree_t *parent, *max_parent, *max_parent2; */
	static size_t depth;
	static nary_tree_t *parent;

	if (root)
		parent = (nary_tree_t *)root->parent;
	while (root)
	{
		++depth;
		tree_depth(root->children, depth_s);
		root = root->next;
	}
	if (depth_s->max_parent != parent)
	{
		if (depth_s->max <= depth)
		{
			puts("set");
			/* max_depth2 = max_depth, max_depth = depth; */
			/* max_parent2 = max_parent, max_parent = parent; */

			depth_s->max2 = depth_s->max, depth_s->max = depth;
			depth_s->max_parent2 = depth_s->max_parent, depth_s->max_parent = parent;
		}
		else if (depth_s->max2 < depth)
		{
			/* max_depth2 = depth; */
			/* max_parent2 = parent; */

			depth_s->max2 = depth;
			depth_s->max_parent2 = parent;
		}
	}
	/* if (depth == 0) */
	/* { */
	/* 	printf("max_depth: %lu\n", max_depth); */
	/* 	printf("max_depth2: %lu\n", max_depth2); */
	/* 	printf("max_parent: %s\n", max_parent->content); */
	/* 	printf("max_parent2: %s\n", max_parent2->content); */
	/* 	max_depth2 = max_depth = 0; */
	/* 	max_parent = NULL; */
	/* } */
	/* else */
	--depth;
	return (*depth_s);
}

size_t nary_tree_diameter(nary_tree_t const *root)
{
	depth_info_t depth_s;

	depth_s.max2 = depth_s.max = 0;
	depth_s.max_parent2 = depth_s.max_parent = NULL;
	tree_depth(root, &depth_s);
	printf("depth_s.max: %lu\n", depth_s.max);
	printf("depth_s.max2: %lu\n", depth_s.max2);
	printf("depth_s.max_parent: %s\n", depth_s.max_parent->content);
	printf("depth_s.max_parent2: %s\n", depth_s.max_parent2->content);
	return (0);
}
