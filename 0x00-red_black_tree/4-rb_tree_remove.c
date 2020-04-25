#include "rb_trees.h"

/**
 * repair_lsibling - sibling of node is to the right
 * @root: double pointer to root node
 * @node: pointer to node where violation detected
 * @node_parent: pointer to parent of node
 *
 * Return: pointer to node
 */
rb_tree_t *repair_lsibling(rb_tree_t **root, rb_tree_t *node,
		rb_tree_t *node_parent)
{
	rb_tree_t *sibling;

	sibling = node ? node->parent->left : node_parent->left;
	if (sibling && sibling->color == RED)
	{
		sibling->color = BLACK;
		node_parent->color = RED;
		rotl(root, node_parent);
		sibling = node ? node->parent->left : node_parent->left;
	}
	if (sibling && (!sibling->right || sibling->right->color == BLACK)
			&& (!sibling->left || sibling->left->color == BLACK))
	{
		sibling->color = RED;
		node = node ? node->parent : node_parent;
	}
	else
	{
		if (sibling && (!sibling->left ||
					sibling->left->color == BLACK))
		{
			sibling->right->color = BLACK;
			sibling->color = RED;
			rotr(root, sibling);
			sibling = node ? node->parent->left :
				node_parent->left;
		}
		if (sibling)
		{
			sibling->color = node_parent->color;
			if (sibling->left)
				sibling->left->color = BLACK;
		}
		node_parent->color = BLACK;
		if (sibling->left)
			sibling->left->color = BLACK;
		rotl(root, node_parent);
		node = *root;
	}
	return (node);
}

/**
 * repair_rsibling - sibling of node is to the right
 * @root: double pointer to root node
 * @node: pointer to node where violation detected
 * @node_parent: pointer to parent of node
 *
 * Return: pointer to node
 */
rb_tree_t *repair_rsibling(rb_tree_t **root, rb_tree_t *node,
		rb_tree_t *node_parent)
{
	rb_tree_t *sibling;

	sibling = node ? node->parent->right : node_parent->right;
	if (sibling && sibling->color == RED)
	{
		sibling->color = BLACK;
		node_parent->color = RED;
		rotl(root, node_parent);
		sibling = node ? node->parent->right : node_parent->right;
	}
	if (sibling && (!sibling->left || sibling->left->color == BLACK) &&
			(!sibling->right || sibling->right->color == BLACK))
	{
		sibling->color = RED;
		node = node ? node->parent : node_parent;
	}
	else
	{
		if (sibling && (!sibling->right ||
					sibling->right->color == BLACK))
		{
			sibling->left->color = BLACK;
			sibling->color = RED;
			rotr(root, sibling);
			sibling = node ? node->parent->right :
				node_parent->right;
		}
		if (sibling)
		{
			sibling->color = node_parent->color;
			if (sibling->right)
				sibling->right->color = BLACK;
		}
		node_parent->color = BLACK;
		if (sibling->right)
			sibling->right->color = BLACK;
		rotl(root, node_parent);
		node = *root;
	}
	return (node);
}

/**
 * rb_rm_repair - fixes red-black tree violations after a node has been removed
 * @root: double pointer to root node
 * @node: pointer to node where violation detected
 * @node_parent: pointer to parent of node
 */
void rb_rm_repair(rb_tree_t **root, rb_tree_t *node, rb_tree_t *node_parent)
{
	while (node != *root && (!node || node->color == BLACK))
	{
		if (node == node_parent->left)
			node = repair_rsibling(root, node, node_parent);
		else
			node = repair_lsibling(root, node, node_parent);
	}
	if (node)
		node->color = BLACK;
}

/**
 * rb_transplant - transplants child node with rm_node
 * @root: pointer to root node
 * @rm_node: node to transplant
 * @child: node being transplanted
 *
 * If rm_node is the root node then points root to child
 * Return: pointer to root node
 */
rb_tree_t *rb_transplant(rb_tree_t *root, rb_tree_t *rm_node, rb_tree_t *child)
{
	if (!rm_node->parent)
		root = child;
	else if (rm_node == rm_node->parent->left)
		rm_node->parent->left = child;
	else
		rm_node->parent->right = child;
	if (child)
		child->parent = rm_node->parent;
	return (root);
}

/**
 * rb_tree_remove - removes a node from red-black tree
 * @root: pointer to root node
 * @n: value to remove from tree
 *
 * root		T
 * rm_node	z
 * rm_node_cpy	y
 * node		x
 * Return: pointer to root node
 */
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n)
{
	rb_tree_t *rm_node, *rm_node_cpy, *node, *node_parent, *min;
	int rm_node_cpy_color;

	rm_node = root;
	GET_NODE(rm_node, n);
	rm_node_cpy = rm_node;
	if (!rm_node)
		return (NULL);
	rm_node_cpy_color = rm_node_cpy->color;
	if (!rm_node->left)
	{
		node = rm_node->right;
		if (!node)
			node_parent = rm_node->parent;
		root = rb_transplant(root, rm_node, rm_node->right);
	}
	else if (!rm_node->right)
	{
		node = rm_node->left;
		if (!node)
			node_parent = rm_node->parent;
		root = rb_transplant(root, rm_node, rm_node->left);
	}
	else
	{
		MIN_TRANSPLANT();
	}
	free(rm_node);
	if (rm_node_cpy_color == BLACK)
		rb_rm_repair(&root, node, node_parent);
	return (root);
}
