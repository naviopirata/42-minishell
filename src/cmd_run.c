#include "../incl/minishell.h"

// char **arr;
// arr[0] = "/bin/cat";
// arr[1] = "test.txt";
// arr[2] = NULL;
//

int	operator_eval(const char *operator)
{
	if (ft_strncmp(operator, ">", 1))
		return (1);
	return (0);
}

int	cmd_run(char *root, char *input)
{
	// char *target = "cat echoed.txt > void.txt | sort | tail -n 3 | grep pirate";
	char *seq = ">|||";

	(void)input;
	(void)root;

	while (*seq) {
		printf("Res: %c \n", *seq);
		seq++;
	
	}
	// int pid;
	// 
	// pid = fork();
	// if (pid == -1)
	// 	return (1);
	// if (pid == 0)
	// 	execve(root, input , NULL);
	// waitpid(pid, NULL, 0);
	return (0);
}
