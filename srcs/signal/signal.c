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

void	signal_handler_interactive(void)
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

static void	print_newline(int sig)
{
	(void)sig;
	rl_on_new_line();
}

void	signal_handler_non_interactive(void)
{
	struct sigaction	sig;

	sig.sa_handler = print_newline;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGQUIT, &sig, NULL);
	sigaction(SIGINT, &sig, NULL);
}