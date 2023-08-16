#include "../incl/minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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
	int pid;
	char **inputs;
	char *arr[3];

	inputs = str_parse(exp_input);
	arr[0] = inputs[0];
	arr[1] = inputs[1];
	arr[2] = NULL;
	pid = fork();
	if (pid == 0)
	{
		ft_printf("\nChild pid: %d\n", pid);
		execve("/bin/cat", arr , NULL);
	}
	else
	{
		wait(NULL);
		ft_printf("Parent scope!...\n", pid);
	}
	free(inputs);
}

int	main(void)
{
	char *user_input;
	char *exp_input;

	exp_input = "cat echoed.txt";
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
	return (0);
}
