#include "../incl/minishell.h"
#include <unistd.h>
#include <sys/wait.h>

int	str_parse(char *lit)
{
	char **trim;
	trim = ft_split(lit, ' ');
	ft_printf("\n1: %s\n", trim[0]);
	ft_printf("2: %s\n", trim[1]);
	return 0;
}

void	cmd_run(void)
{
	int pid;
	char *arr[] = {"cat", "echoed.txt", NULL};

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
	return ;
}

int	main(void)
{
	char *str;
	char *lit;

	lit = "echo hi";
	// signals_init();
	// abstree_init();
	// while (1)
	// {
		ft_printf("Enter your command:");
		str = readline("");
		ft_printf("minishell$ %s", str);
		if (ft_strnstr(str, lit, 7))
			str_parse(lit);
		cmd_run();
	// }
	return (0);
}
