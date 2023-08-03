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
	else 
	{
		if (!node->right)
		{
			node->right = node_create(value);
			return node->right;
		}
		return node_add(value, node->right);
	}
}

void	node_lst_asc(t_tree *node)
{
	if (node->left)
		node_lst_asc(node->left);
	ft_printf("%d x\t %d\n", node->count, node->value);
	
	if (node->right)
		node_lst_asc(node->right);
}

void	node_lst_desc(t_tree *node) 
{
	if (node->right)
		node_lst_desc(node->right);
	ft_printf("%d x\t %d\n", node->count, node->value);

	if (node->left)
		node_lst_desc(node->left);
	return ;
}

void	node_free(t_tree *node)
{
	if (!node)
		return ;
	if (node->left)
		node_free(node->left);
	if (node->right)
		node_free(node->right);
	free(node);
	return ;
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
