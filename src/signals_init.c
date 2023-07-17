#include "../incl/minishell.h"

//TODO: config signals
//TODO: block signals
//TODO: review sa_flags

static	void	signal_handler(int signal, siginfo_t *siginfo, void *context)
{

	(void)context;
	ft_printf("signal: %s\n", strsignal(signal));
	kill(siginfo->si_pid, SIGUSR1);
	return ;
}

void	signals_init(void) 
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(sigaction));
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = signal_handler;
	sigemptyset(&act.sa_mask);
	//TODO: implement SIGINT SIGQUIT 
	// if (sigaction(SIGINT, &act, 0) < 0)
	// 	ft_printf("Fatal: CTRL+C setting failed!%c\n", 0);
}
