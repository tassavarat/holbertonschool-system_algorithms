#include "rb_trees.h"

/**
 * repaint_family - changes color of grandparent RED and its children BLACK
 */
void repaint_family(rb_tree_t *grandparent)
{
	printf("grandparent->n %i has RED children\n", grandparent->n);
	/* grandparent->color = RED; */
	/* grandparent->left->color = BLACK; */
	/* grandparent->right->color = BLACK; */
}

/**
 * get_uncle - retrieves a node's uncle
 * @new: node to check
 *
 * Return: new's uncle, otherwise NULL
 */
rb_tree_t *get_uncle(rb_tree_t *new)
{
	rb_tree_t *parent, *grandparent;

	if (!new || !new->parent || !new->parent->parent)
		return (NULL);
	parent = new->parent;
	grandparent = parent->parent;
	if (grandparent->left && grandparent->left != parent)
		return (grandparent->left);
	if (grandparent->right && grandparent->right != parent)
		return (grandparent->right);
	return (NULL);
}

/**
 * insert_bst - inserts node into appropriate binary search tree position
 * @tree: pointer to red-black tree
 * @value: value of node to insert
 *
 * Description: newly created node will be RED, BLACK if tree is NULL
 * Return: pointer to newly created node, NULL on failure
 */
rb_tree_t *insert_bst(rb_tree_t **tree, int value)
{
	rb_tree_t *cur, *new;

	if (!*tree)
	{
		new = *tree = rb_tree_node(*tree, value, BLACK);
		return (new);
	}
	new = cur = *tree;
	while (cur && new == *tree)
	{
		if (value < cur->n)
		{
			if (!cur->left)
				new = cur->left = rb_tree_node(cur, value, RED);
			else
				cur = cur->left;
		}
		else
		{
			if (!cur->right)
				new = cur->right = rb_tree_node(cur, value, RED);
			else
				cur = cur->right;
		}
	}
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
	rb_tree_t *new, *uncle;

	new = insert_bst(tree, value);
	uncle = get_uncle(new);
	if (uncle)
		printf("uncle->n %i\n", uncle->n);
	if (uncle && new->parent->color == RED)
	{
		if (uncle->color == RED)
			repaint_family(uncle->parent);
		else	/* uncle->color == BLACK */
			printf("uncle->n %i is BLACK\n", uncle->n);
	}
	return (new);
}
