#include "../incl/minishell.h"

static void pipe_fd_close(int pipes1[], int pipes2[])
{
	close(pipes1[READ_END]);
	close(pipes1[WRITE_END]);
	close(pipes2[READ_END]);
	close(pipes2[WRITE_END]);
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

static int	child_run()
{
	int	pid1;
	int	pid2;
	int	pid3;
	int	pipes[2];
	int	pipez[2];

	pipe(pipes);
	pipe(pipez);
	pid1 = fork();
	if (pid1 == -1)
		return (-1);
	if (pid1 == 0)
	{
		char	*cat[3];
		cat[0] = "cat";
		cat[1] = "echoed.txt";
		cat[2] = NULL;
		pipe_fd_dup2(pipes, WRITE_END);
		pipe_fd_close(pipes, pipez);
		execve("/bin/cat", cat, NULL);
	}

	pid2 = fork();
	if (pid2 == -1)
		return (-1);
	if (pid2 == 0)
	{
		char	*sort[2];
		sort[0] = "sort";
		sort[1] = NULL;
		pipe_fd_dup2(pipes, READ_END);
		pipe_fd_dup2(pipez, WRITE_END);
		pipe_fd_close(pipes, pipez);
		execve("/bin/sort", sort, NULL);
	}

	pid3 = fork();
	if (pid3 == -1)
		return (-1);
	if (pid3 == 0)
	{
		char	*tail[4];
		tail[0] = "tail";
		tail[1] = "-n";
		tail[2] = "3";
		tail[3] = NULL;
		pipe_fd_dup2(pipez, READ_END);
		pipe_fd_close(pipes, pipez);
		execve("/bin/tail", tail, NULL);
	}
	pipe_fd_close(pipes, pipez);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	waitpid(pid3, NULL, 0);
	return (0);
}

int	pipe_exec(void)
{
	int	pid;
	pid = fork();

	if (pid == -1)
		return (-1);
	if (pid == 0)
		child_run();
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
