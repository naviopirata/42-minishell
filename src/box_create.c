#include "../incl/minishell.h"
#include <readline/readline.h>
#include <stdlib.h>

static	char **cat_create()
{
	char **cat;

	cat = (char **)malloc(3 * sizeof(char *));
	cat[0] = "cat";
	cat[1] = "echoed.txt";
	cat[2] = NULL;
	return (cat);
}

static	char **sort_create()
{
	char **sort;

	sort = (char **)malloc(2 * sizeof(char *));
	sort[0] = "sort";
	sort[1] = NULL;
	return (sort);
}

static	char **tail_create()
{
	char **tail;

	tail = (char **)malloc(4 * sizeof(char *));
	tail[0] = "tail";
	tail[1] = "-n";
	tail[2] = "3";
	tail[3] = NULL;
	return (tail);
}
t_box	*box_create()
{
	t_box	*block;

	block = (t_box *)malloc(sizeof(t_box));
	block->cat = cat_create();
	block->sort = sort_create();
	block->tail = tail_create();

	return (block);
}
