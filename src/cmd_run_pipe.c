#include "../incl/minishell.h"

static void pipe_close_child(t_box *block, int scene)
{
	if (scene == 1)
	{
		close(block->pipeone[READ_END]);
		close(block->pipeone[WRITE_END]);
		return ;
	}
	close(block->pipeone[READ_END]);
	close(block->pipeone[WRITE_END]);
	close(block->pipetwo[READ_END]);
	close(block->pipetwo[WRITE_END]);
	return ;
}

static void pipe_close(t_box *block, int scene)
{
	if (scene == 1)
		return ;
	else if(scene == 2)
	{
		close(block->pipeone[READ_END]);
		close(block->pipeone[WRITE_END]);
		return ;
	}
	close(block->pipeone[READ_END]);
	close(block->pipeone[WRITE_END]);
	close(block->pipetwo[READ_END]);
	close(block->pipetwo[WRITE_END]);
	return ;
}

static void	pipe_fd_dup2(int pipes[], int mode)
{
	if (mode == WRITE_END)
		dup2(pipes[WRITE_END], STDOUT_FILENO);
	else 
		dup2(pipes[READ_END], STDIN_FILENO);
	return ;
}

static void	pipe_handle(t_box *block, int scene)
{
	if (scene == 1)
	{
		pipe_fd_dup2(block->pipeone, WRITE_END);
		return ;
	}
	else if (scene == 2)
	{
		pipe_fd_dup2(block->pipeone, READ_END);
		pipe_fd_dup2(block->pipetwo, WRITE_END);
		return ;
	}
	pipe_fd_dup2(block->pipetwo, READ_END);
	return ;
}

static int	cmd_exec(t_box *block, char *cmd[], int scene)
{
	int	pid;
	char	*root;

	root = ft_strjoin("/bin/", cmd[0]);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		pipe_handle(block, scene);
		pipe_close_child(block, scene);
		execve(root, cmd, NULL);
	}
	pipe_close(block, scene);
	waitpid(pid, NULL, 0);
	free(root);
	return (0);
}

int	pipe_exec(void)
{
	t_box	*block;

	block = box_create();
	pipe(block->pipeone);
	pipe(block->pipetwo);
	cmd_exec(block, block->cat, 1);
	cmd_exec(block, block->sort, 2);
	cmd_exec(block, block->tail, 3);
	free(block);

	return (1);
}

int cmd_run_pipe(int cmdid)
{
	if (cmdid == 0)
		pipe_exec();
	return (0);
}
