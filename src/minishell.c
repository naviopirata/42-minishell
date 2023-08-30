
#include "../incl/minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ_END 0 
#define WRITE_END 1

char	**str_parse(char *exp_input)
{
	char **trim;
	trim = ft_split(exp_input, ' ');
	ft_printf("\n1: %s\n", trim[0]);
	ft_printf("2: %s\n", trim[1]);
	return trim;
}

void	cmd_run(char *exp_input)
{
	int pid1;
	int pid2;
	char **inputs;
	char *arr[3];
	int pipedes[2];

	inputs = str_parse(exp_input);
	arr[0] = inputs[0];
	arr[1] = inputs[1];
	free(inputs);
	arr[2] = NULL;
	arr[0] = "cat";
	arr[1] = "test.txt";
	pipe(pipedes);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(pipedes[WRITE_END], STDOUT_FILENO);
		close(pipedes[READ_END]);
		close(pipedes[WRITE_END]);
		execve("/bin/cat", arr , NULL);
	}
	arr[0] = "grep";
	arr[1] = "pirate";
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipedes[READ_END], STDIN_FILENO);
		close(pipedes[READ_END]);
		close(pipedes[WRITE_END]);
		execve("/bin/grep", arr , NULL);
	}
	close(pipedes[READ_END]);
	close(pipedes[WRITE_END]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	ft_printf("Success!\n");
}

int	main(void)
{
	char *user_input;
	char *exp_input;

	exp_input = "cat test.txt | grep pirate";
	while (1)
	{
		ft_printf("minishell$ ");
		user_input = readline("");
		if (ft_strnstr(user_input, exp_input, ft_strlen(exp_input)))
		{
			cmd_run(exp_input);
			break ;
		}
		ft_printf("Error: Invalid command...\nTry: cat echoed.txt\n");
	}


