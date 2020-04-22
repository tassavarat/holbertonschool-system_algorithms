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
 * repair_rb_luncle - uncle of node is to the left
 * @tree: double pointer to root node
 * @node: pointer to node where violation detected
 */
void repair_rb_luncle(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *grandparent, *uncle = node->parent->parent->left;

	if (uncle && uncle->color == RED)
	{
		node->parent->color = BLACK;
		uncle->color = BLACK;
		grandparent = node->parent->parent;
		grandparent->color = RED;
		node = grandparent;
	}
	else
	{
		if (node == node->parent->left)
		{
			node = node->parent;
			rotr(tree, node);
		}
		node->parent->color = BLACK;
		node->parent->parent->color = RED;
		rotl(tree, node->parent->parent);
	}
}

/**
 * repair_rb_runcle - uncle of node is to the right
 * @tree: double pointer to root node
 * @node: pointer to node where violation detected
 */
void repair_rb_runcle(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *grandparent, *uncle = node->parent->parent->right;

	if (uncle && uncle->color == RED)
	{
		node->parent->color = BLACK;
		uncle->color = BLACK;
		grandparent = node->parent->parent;
		grandparent->color = RED;
		node = grandparent;
	}
	else
	{
		if (node == node->parent->right)
		{
			node = node->parent;
			rotl(tree, node);
		}
		node->parent->color = BLACK;
		node->parent->parent->color = RED;
		rotr(tree, node->parent->parent);
	}
}

/**
 * repair_rb - repairs red-black tree violations
 * @tree: double pointer to root node
 * @node: pointer to newly inserted node
 *
 * As violations are detected, node will continually shift up
 */
void repair_rb(rb_tree_t **tree, rb_tree_t *node)
{
	while (node->parent && node->parent->color == RED)
	{
		if (node->parent->parent &&
				node->parent == node->parent->parent->left)
			repair_rb_runcle(tree, node);
		else
			repair_rb_luncle(tree, node);
	}
	(*tree)->color = BLACK;
}

/**
 * insert_rb - inserts node into appropriate binary search tree position
 * @tree: pointer to red-black tree
 * @value: value of node to insert
 *
 * Description: newly created node will be RED
 * Return: pointer to newly created node, NULL on failure
 */
rb_tree_t *insert_rb(rb_tree_t **tree, int value)
{
	rb_tree_t *cur, *prev, *new;

	cur = *tree;
	while (cur)
	{
		if (value == cur->n)
			return (NULL);
		prev = cur;
		if (value < cur->n)
			cur = cur->left;
		else
			cur = cur->right;
	}
	new = rb_tree_node(NULL, value, RED);
	if (!new)
		return (NULL);
	new->parent = prev;
	if (!prev)
		*tree = new;
	else if (new->n < prev->n)
		prev->left = new;
	else
		prev->right = new;
	return (new);
}

/**
 * rb_tree_insert - inserts node into red-black tree
 * @tree: double pointer to root node of red-black tree
 * @value: value of node to insert
 *
 * Return: pointer to newly created node, NULL on failure
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new;

	if (!tree)
		return (NULL);
	new = insert_rb(tree, value);
	if (new)
		repair_rb(tree, new);
	return (new);
}
