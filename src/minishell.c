#include "../incl/minishell.h"

char	**str_parse(char *exp_input)
{
	char **trim;
	trim = ft_split(exp_input, ' ');
	ft_printf("\n1: %s\n", trim[0]);
	ft_printf("2: %s\n", trim[1]);
	return trim;
}

int	main(void)
{
	char *user_input;
	char *exp_input;

	exp_input = "test";
	while (1)
	{
		ft_printf("minishell$ ");
		user_input = readline("");
		if (ft_strnstr(user_input, exp_input, ft_strlen(exp_input)))
		{
			cmd_run(exp_input, exp_input);
			break ;
		}
		ft_printf("Error: Invalid command...\nTry: cat echoed.txt\n");
	}
}
