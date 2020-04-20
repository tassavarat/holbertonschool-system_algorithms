#include "rb_trees.h"

/**
 * pop - removes last node in a linked list
 * @cur_s: double pointer to end of stack node
 * @black_count: current count of black nodes
 *
 * Return: node of cur_s right child, NULL if nothing to pop
 */
rb_tree_t *pop(stack **cur_s, int *black_count)
{
	rb_tree_t *tmp;
	stack *tmp_s;

	if (!*cur_s)
		return (NULL);
	tmp = (*cur_s)->node->right;
	tmp_s = *cur_s;
	*black_count = (*cur_s)->black_count;
	*cur_s = (*cur_s)->prev;
	free(tmp_s);
	if (*cur_s)
		(*cur_s)->next = NULL;
	return (tmp);
}

/**
 * push - create and append node to end of linked list
 * @cur_s: double pointer to end of stack node
 * @cur: pointer to current red-black tree node
 * @black_count: current count of black nodes
 *
 * Return: pointer to newly created node, otherwise NULL
 */
stack *push(stack **cur_s, rb_tree_t *cur, int black_count)
{
	stack *new = malloc(sizeof(*new));

	if (!new)
		return (NULL);
	new->black_count = black_count;
	new->node = cur;
	new->prev = *cur_s;
	new->next = NULL;
	*cur_s = new;
	return (new);
}

/**
 * key_fail - checks if valid binary search tree
 * @cur: pointer to current tree node
 *
 * Return: 1 if invalid binary search tree, otherwise 0
 */
int key_fail(rb_tree_t *cur)
{
	if ((cur->left && cur->left->n > cur->n) ||
			(cur->right && cur->right->n < cur->n))
		return (1);
	return (0);
}

/**
 * colour_fail - checks if red-black tree colour properties are valid
 * @cur: pointer to current tree node
 *
 * Return: 1 if invalid colour properties, otherwise 0
 */
int colour_fail(rb_tree_t *cur)
{
	if ((cur->color != RED && cur->color != BLACK) ||
			(!cur->parent && cur->color != BLACK))
		return (1);
	if (cur->color == RED &&
			((cur->parent && cur->parent->color == RED) ||
			 (cur->left && cur->left->color == RED) ||
			 (cur->right && cur->right->color == RED)))
		return (1);
	return (0);
}

/**
 * rb_tree_is_valid - checks if binary tree is valid red-black tree
 * @tree: pointer to root node of tree being checked
 *
 * Return: 1 if valid, otherwise 0
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	rb_tree_t *cur;
	stack *cur_s;
	int black_count, tmp_count, popped;

	if (!tree)
		return (0);
	cur = (rb_tree_t *) tree;
	cur_s = NULL;
	black_count = tmp_count = popped = 0;
	while (cur)
	{
		if (colour_fail((rb_tree_t *) cur) ||
				key_fail((rb_tree_t *) cur))
			return (0);
		if (cur->color == BLACK)
			++black_count;
		/* printf("cur->n\t%i\n", cur->n); */
		if (cur->right && !push(&cur_s, (rb_tree_t *) cur, black_count))
			return (0);
		if (cur->left)
		{
			cur = cur->left;
		}
		else
		{
			/* puts("popped"); */
			if (!popped)
				tmp_count = black_count;
			if (black_count != tmp_count)
				return (0);
			/* printf("black_count\t%i\n", black_count); */
			cur = pop(&cur_s, &black_count);
			popped = 1;
		}
		/* puts("####"); */
	}
	return (1);
}
