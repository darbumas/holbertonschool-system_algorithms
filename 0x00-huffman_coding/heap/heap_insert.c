#include "heap.h"

/**
 * get_insertion_point - Finds the appropriate position for the new node
 * @heap: pointer to the Binary Tree
 *
 * Return: pointer to the appropriate node to insert
 */
static binary_tree_node_t *get_insertion_point(heap_t *heap)
{
	binary_tree_node_t *node = NULL, **queue = NULL;
	size_t i, size = 0, capacity = 0;
	bool insert_point = false;

	node = heap->root;
	if (!node)
		return (NULL);
	/* Initialize the queue with an initial capacity of 10 nodes */
	capacity = 10;
	queue = malloc(capacity * sizeof(*queue));
	if (!queue)
		return (NULL);
	/* Add root to the queue and update size */
	queue[0] = node;
	size = 1;
	/* Perform Breadth-First Search to find insertion point */
	for (i = 0; i < size && !insert_point; ++i)
	{
		node = queue[i];
		/* If we're at a leaf node, the insertion point is found */
		if (!node->left || !node->right)
			insert_point = true;
		else
		{
		/* Check if the queue needs to be resized before insertion */
			if (size + 2 >= capacity)
			{
				capacity *= 2;
				queue = realloc(queue, capacity * sizeof(*queue));
				if (!queue)
					return (NULL);
			}
		/* Add the left and right children of current node to queue */
		queue[size++] = node->left;
		queue[size++] = node->right;
		}
	}
	free(queue);
	return (insert_point ? node : NULL);
}
/**
 * bubble_up - ensures that the min-heap property is maintained after inserting
 * the new node
 * @heap: pointer to the heap
 * @node: pointer to the newly inserted node
 */
static void bubble_up(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *parent;
	void *tmp_data;

	while (node->parent && heap->data_cmp(node->data, node->parent->data)
			< 0)
	{
		parent = node->parent;
		tmp_data = parent->data;
		parent->data = node->data;
		node->data = tmp_data;
		node = parent;
	}
}

/**
 * heap_insert - Inserts a value in a Min Binary Heap
 * @heap: pointer to the heap
 * @data: pointer containing the data to store in the new node
 * Return: pointer to the created node, NULL otherwise
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new_node = NULL;
	binary_tree_node_t *insert_point = NULL;

	if (!heap || !data)
		return (NULL);

	new_node = binary_tree_node(NULL, data);
	if (!new_node)
		return (NULL);

	insert_point = get_insertion_point(heap);
	if (!insert_point)
		heap->root = new_node;
	else
	{
		if (!insert_point->left)
			insert_point->left = new_node;
		else
			insert_point->right = new_node;

		new_node->parent = insert_point;
		bubble_up(heap, new_node);
	}
	heap->size++;
	return (new_node);
}
