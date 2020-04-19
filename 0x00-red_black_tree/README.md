# 0x00. C - Red-Black trees

## Learning Objectives
* What is a Red-Black Tree

## Requirements

* Allowed editors: `vi`, `vim`, `emacs`
* All your files will be compiled on Ubuntu 14.04 LTS
* Your programs and functions will be compiled with `gcc 4.8.4` using the flags `-Wall` `-Werror` `-Wextra` and `-pedantic`
* All your files should end with a new line
* A `README.md` file, at the root of the folder of the project, is mandatory
* Your code should use the `Betty` style. It will be checked using [betty-style.pl](https://github.com/holbertonschool/Betty/blob/master/betty-style.pl) and [betty-doc.pl](https://github.com/holbertonschool/Betty/blob/master/betty-doc.pl)
* You are not allowed to use global variables
* No more than 5 functions per file
* You are allowed to use the standard library
* In the following examples, the `main.c` files are shown as examples. You can use them to test your functions, but you don’t have to push them to your repo (if you do we won’t take them into account). We will use our own `main.c` files at compilation. Our `main.c` files might be different from the one shown in the examples
* The prototypes of all your functions should be included in your header files called `rb_trees.h`
* Don’t forget to push your header files
* All your header files should be include guarded

### [0. Red-Black - New node](./0-rb_tree_node.c)
Write a function that creates a Red-Black Tree node
* Prototype: `rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color);`
* Where `parent` is a pointer to the parent node of the node to create
* `value` is the value to put in the new node
* And `color` is the color of the node
* When created, a node does not have any child
* Your function must return a pointer to the new node, or `NULL` on failure
```
alex@/tmp/huffman_rb_trees$ cat 0-main.c
#include <stdlib.h>
#include "rb_trees.h"

void rb_tree_print(const rb_tree_t *tree);

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    rb_tree_t *root;

    root = rb_tree_node(NULL, 98, BLACK);

    root->left = rb_tree_node(root, 12, RED);
    root->left->left = rb_tree_node(root->left, 6, BLACK);
    root->left->right = rb_tree_node(root->left, 16, BLACK);

    root->right = rb_tree_node(root, 402, RED);
    root->right->left = rb_tree_node(root->right, 256, BLACK);
    root->right->right = rb_tree_node(root->right, 512, BLACK);

    rb_tree_print(root);
    return (EXIT_SUCCESS);
}
alex@/tmp/huffman_rb_trees$ gcc -Wall -Wextra -Werror -pedantic 0-main.c 0-rb_tree_node.c rb_tree_print.c -o rb_tree_node
alex@/tmp/huffman_rb_trees$ ./rb_tree_node
         .--------B(098)---------.
   .--R(012)---.           .--R(402)---.
B(006)      B(016)      B(256)      B(512)
alex@/tmp/huffman_rb_trees$
```

### [1. Red-Black - Is Red-Black](./1-rb_tree_is_valid.c)
Write a function that checks if a binary tree is a valid Red-Black Tree
* Prototype: `int rb_tree_is_valid(const rb_tree_t *tree);`
* Where `tree` is a pointer to the root node of the tree to check
* Your function must return `1` if tree is a valid Red-Black Tree, and `0` otherwise
* If `tree` is `NULL`, return `0`

Properties of a Red-Black Tree:
* A Red-Black Tree is a BST
* Every node has a color either red or black.
* Root of tree is always black.
* There are no two adjacent red nodes (A red node cannot have a red parent or red child).
* Every path from root to a NULL node has same number of black nodes.
```
alex@/tmp/huffman_rb_trees$ cat 1-main.c
#include <stdlib.h>
#include <stdio.h>
#include "rb_trees.h"

void rb_tree_print(const rb_tree_t *tree);

/**
 * valid_rb - Builds a valid R-B tree
 *
 * Return: A pointer to the created tree
 */
rb_tree_t *valid_rb(void)
{
    rb_tree_t *root;

    root = rb_tree_node(NULL, 98, BLACK);
    root->left = rb_tree_node(root, 90, BLACK);
    root->right = rb_tree_node(root, 120, BLACK);
    root->left->left = rb_tree_node(root->left, 79, RED);
    root->left->right = rb_tree_node(root->left, 95, RED);
    return (root);
}

/**
 * not_valid_rb - Builds a not valid R-B tree
 *
 * Return: A pointer to the created tree
 */
rb_tree_t *not_valid_rb(void)
{
    rb_tree_t *root;

    root = rb_tree_node(NULL, 98, BLACK);
    root->left = rb_tree_node(root, 90, RED);
    root->right = rb_tree_node(root, 120, RED);
    root->left->left = rb_tree_node(root->left, 79, BLACK);
    root->left->right = rb_tree_node(root->left, 95, BLACK);
    root->left->right->left = rb_tree_node(root->left->right, 92, RED);
    root->left->right->right = rb_tree_node(root->left->right, 96, RED);
    root->right->right = rb_tree_node(root->right, 130, BLACK);
    return (root);
}

/**
 * main - Entry point
 *
 * Return: Always EXIT_SUCCESS
 */
int main(void)
{
    rb_tree_t *root;
    int valid;

    root = valid_rb();
    rb_tree_print(root);
    valid = rb_tree_is_valid(root);
    printf("Is %d valid: %d\n", root->n, valid);

    root = not_valid_rb();
    rb_tree_print(root);
    valid = rb_tree_is_valid(root);
    printf("Is %d valid: %d\n", root->n, valid);

    root->color = RED;
    rb_tree_print(root);
    valid = rb_tree_is_valid(root);
    printf("Is %d valid: %d\n", root->n, valid);
    return (EXIT_SUCCESS);
}
alex@/tmp/huffman_rb_trees$ gcc -Wall -Wextra -Werror -pedantic 1-main.c 1-rb_tree_is_valid.c 0-rb_tree_node.c  rb_tree_print.c -o rb_tree_valid
alex@/tmp/huffman_rb_trees$ ./rb_tree_valid
         .--------B(098)---.
   .--B(090)---.        B(120)
R(079)      R(095)
Is 98 valid: 1
         .--------------------B(098)---.
   .--R(090)---------.              R(120)---.
B(079)         .--B(095)---.              B(130)
            R(092)      R(096)
Is 98 valid: 0
         .--------------------R(098)---.
   .--R(090)---------.              R(120)---.
B(079)         .--B(095)---.              B(130)
            R(092)      R(096)
Is 98 valid: 0
alex@/tmp/huffman_rb_trees$
```
