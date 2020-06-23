#include "heap.h"

/**
 * heap_create - create heap data structure
 * @data_cmp: pointer to function comparing data of two nodes
 *
 * Return: pointer to new heap data structure, NULL on failure
 */
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *heap = malloc(sizeof(*heap));

	if (!heap)
		return (NULL);
	heap->size = 0;
	heap->data_cmp = data_cmp;
	heap->root = NULL;
	return (heap);
}
