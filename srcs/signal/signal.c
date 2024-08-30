#include "../../incs/minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	rl_redisplay();
	printf("  \b");
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler(void)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;
	
	sigint.sa_handler = handle_sigint;
	sigemptyset(&sigint.sa_mask);
	sigint.sa_flags = 0;
	sigaction(SIGINT, &sigint, NULL);
	sigquit.sa_handler = SIG_IGN;
	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_flags = 0;
	sigaction(SIGQUIT, &sigquit, NULL);
}