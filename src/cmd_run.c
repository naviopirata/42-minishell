#include "../incl/minishell.h"

static int	operator_eval(const char *operator)
{
	if (ft_strncmp(operator, ">", 1))
		return (OPER_WRITE);
	if (ft_strncmp(operator, "|", 1))
		return (OPER_PIPE);
	return (0);
}

int	cmd_run(char *root, char *input)
{
	// char *target = "cat echoed.txt > void.txt | sort | tail -n 3 | grep pirate";
	char	*seq = ">|";
	int	operator;
	int	aux_pipe;

	(void)input;
	(void)root;

	operator = operator_eval(seq);
	aux_pipe = 0;
	while (*seq) {
		if (operator == OPER_WRITE)
			cmd_run_redirect();
		else if (operator == OPER_PIPE)
			cmd_run_pipe(aux_pipe);
		seq++;
		aux_pipe++;
	}
	return (0);
}
