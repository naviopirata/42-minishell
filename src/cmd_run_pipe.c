#include "../incl/minishell.h"

static void pipe_fd_close(int pipes_parent[], int pipes_child[])
{

	close(pipes_parent[READ_END]);
	close(pipes_parent[WRITE_END]);
	if (pipes_child)
	{
		close(pipes_child[READ_END]);
		close(pipes_child[WRITE_END]);
	}
	return ;
}

static void pipe_fd_dup2(int pipes[], int mode)
{
	if (mode == WRITE_END)
		dup2(pipes[WRITE_END], STDOUT_FILENO);
	else 
		dup2(pipes[READ_END], STDIN_FILENO);
	return ;
}

static int	run_cat(t_box *block)
{
	int	pid;
	char	*root;

	root = ft_strjoin("/bin/", block->cat[0]);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		pipe_fd_dup2(block->pipeone, WRITE_END);
		pipe_fd_close(block->pipeone, block->pipeone);
		execve(root, block->cat, NULL);
	}
	waitpid(pid, NULL, 0);
	free(root);
	return (0);
}

static int	run_sort(t_box *block)
{
	int	pid2;
	char	*root;

	root = ft_strjoin("/bin/", block->sort[0]);
	pid2 = fork();
	if (pid2 == -1)
		return (-1);
	if (pid2 == 0)
	{
		pipe_fd_dup2(block->pipeone, READ_END);
		pipe_fd_dup2(block->pipetwo, WRITE_END);
		pipe_fd_close(block->pipeone, block->pipetwo);
		execve(root, block->sort, NULL);
	}
	pipe_fd_close(block->pipeone, NULL);
	waitpid(pid2, NULL, 0);
	free(root);
	return (0);
}

static int	run_tail(t_box *block)
{
	int	pid3;
	char	*root;

	root = ft_strjoin("/bin/", block->tail[0]);
	pid3 = fork();
	if (pid3 == -1)
		return (-1);
	if (pid3 == 0)
	{
		pipe_fd_dup2(block->pipetwo, READ_END);
		pipe_fd_close(block->pipeone, block->pipetwo);
		execve(root, block->tail, NULL);
	}
	pipe_fd_close(block->pipeone, block->pipetwo);
	waitpid(pid3, NULL, 0);
	free(root);
	return (0);
}

int	pipe_exec(void)
{
	int	pid;
	t_box	*block;
	pid = fork();

	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		block = box_create();
		pipe(block->pipeone);
		pipe(block->pipetwo);
		run_cat(block);
		run_sort(block);
		run_tail(block);
		free(block);
	}
	waitpid(pid, NULL, 0);

	return (1);
}

int cmd_run_pipe(int cmdid)
{
	if (cmdid == 0)
		pipe_exec();
	// else if (cmdid == 1)
	// 	pipe_exec(sort);
	// else if (cmdid == 2)
	// 	pipe_exec(tail);
	// else if (cmdid == 3)
	// 	pipe_exec(grep);
	return (0);
}
