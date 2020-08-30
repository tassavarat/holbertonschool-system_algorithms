#include "nary_trees.h"

/**
 * nary_tree_insert - insert node into n-ary tree
 * @parent: pointer to parent node
 * @str: string to store in inserted node
 *
 * Return: pointer to inserted node, NULL on error
 */
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->content = strdup(str);
	if (!new->content)
		return (NULL);

	new->parent = parent;
	new->nb_children = 0;
	new->children = NULL;
	if (parent)
	{
		++parent->nb_children;
		new->next = parent->children;
		parent->children = new;
	}
	else
	{
		new->next = NULL;
	}
	return (new);
}
