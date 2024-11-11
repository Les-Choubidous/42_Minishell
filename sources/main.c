#include "messages.h"
#include "minishell.h"

int	main ()
{
	char	*mini_shell;

	mini_shell = readline("minishell$ ");
	while(mini_shell)
	{
		if (strcmp(mini_shell, "exit") == 0)
		{
			printf(CYAN "Ciaaaao minishell" RESET);
			printf(MAGENTA "$\n" RESET);
			break;
		}
		//analyser les "arguments" saisies par l'utilisateur : parsing?
		//si ok ex? 
		add_history(mini_shell);
		free (mini_shell);
	}
	rl_clear_history();
	return(0);
}
