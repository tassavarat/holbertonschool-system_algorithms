#include "rb_trees.h"

/**
 * rotr - rotates subtree right
 * @tree: double pointer to root node
 * @node: pointer to node where violation detected
 *
 * child is the pivot point, that is the link between the newly inserted node
 * and its grandparent
 */
void rotr(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *child = node->left;

	if (!child)
		return;
	node->left = child->right;
	if (child->right)
		child->right->parent = node;
	child->parent = node->parent;
	if (!node->parent)
		*tree = child;
	else if (node == node->parent->right)
		node->parent->right = child;
	else
		node->parent->left = child;
	child->right = node;
	node->parent = child;
}

/**
 * rotl - rotates subtree left
 * @tree: double pointer to root node
 * @node: pointer to node where violation detected
 *
 * child is the pivot point, that is the link between the newly inserted node
 * and its grandparent
 */
void rotl(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *child = node->right;

	if (!child)
		return;
	node->right = child->left;
	if (child->left)
		child->left->parent = node;
	child->parent = node->parent;
	if (!node->parent)
		*tree = child;
	else if (node == node->parent->left)
		node->parent->left = child;
	else
		node->parent->right = child;
	child->left = node;
	node->parent = child;
}

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
