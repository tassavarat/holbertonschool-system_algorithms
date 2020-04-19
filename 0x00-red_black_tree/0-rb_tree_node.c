#include "rb_trees.h"

/**
 * rb_tree_node - creates a Red-Black Tree node
 * @parent: pointer to parent node of new node
 * @value: value to put in new node
 * @color: colour of new node
 *
 * Return: pointer to new node, NULL on failure
 */
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *new;

	if (color != RED && color != BLACK && color != DOUBLE_BLACK)
		goto out;
	new = malloc(sizeof(*new));
	if (!new)
out:
		return (NULL);
	new->n = value;
	new->color = color;
	new->parent = parent;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
