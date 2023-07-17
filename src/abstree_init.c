#include "../incl/minishell.h"

t_tree	*node_create(int value)
{
	t_tree	*node;

	node = (t_tree *)malloc(sizeof(t_tree));
	node->value = value;
	node->count = 1;
	node->left = NULL;
	node->right = NULL;
	return node;
}

t_tree	*node_add(int value, t_tree *node)
{
	if (!node)
		return node_create(value);
	if (value == node->count)
	{
		node->count++;
		return node;
	}
	if (value < node->value)
	{
		if (!node->left)
		{
			node->left = node_create(value);
			return node->left;
		}
		return node_add(value, node->left);
	}
	if (!node->right)
	{
		node->right = node_create(value);
		return node->right;
	}
	return node_add(value, node->right);
}

void	abstree_init(void)
{
	t_tree **root;

	root = (t_tree **)malloc(sizeof(t_tree *));
	*root = node_create(42);
	ft_printf("node value: %d\n", (*root)->value);
	free(*root);
	free(root);
	return;
}
