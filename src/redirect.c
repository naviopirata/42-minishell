#include "../incl/minishell.h"

// char **arr;
// arr[0] = "/bin/cat";
// arr[1] = "test.txt";
// arr[2] = NULL;

int	redirect(char *root, char **input)
{
	int pid;
	
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		execve(root, input , NULL);
	waitpid(pid, NULL, 0);
	return (0);
}
