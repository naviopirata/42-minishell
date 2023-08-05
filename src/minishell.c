#include "../incl/minishell.h"

int	str_parse(char *lit)
{
	char **trim;
	trim = ft_split(lit, ' ');
	ft_printf("\n1: %s\n", trim[0]);
	ft_printf("2: %s\n", trim[1]);
	return 0;
}

int	main(void)
{
	char *str;
	char *lit;

	lit = "echo hi";
	// signals_init();
	// abstree_init();
	while (1)
	{
		str = readline("\nenter ");
		ft_printf("minishell$ %s", str);
		if (ft_strnstr(str, lit, 7))
			str_parse(lit);
	}
	return (0);
}
