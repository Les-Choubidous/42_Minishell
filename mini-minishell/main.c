#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

# define CYAN "\e[1;96m"
# define MAGENTA "\e[1;95m"
# define RESET "\e[0m"

int	main ()
{
	char	*mini_shell;

	while((mini_shell = readline("minishell> ")) != NULL)
	{
			if (strcmp(mini_shell, "exit") == 0)
		{
			printf(CYAN "Ciaaaao minishell" RESET);
			printf(MAGENTA "$\n" RESET);
			break;
		}
		add_history(mini_shell);
		free (mini_shell);
	}
	rl_clear_history();
	return(0);
}
