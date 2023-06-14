#include "../incl/minishell.h"

int	main(void)
{
	char *str;

	str = NULL;
	while (1)
	{
		str = readline("enter ");
		ft_printf("minishell$ %s", str);
	}
	return (0);
}
