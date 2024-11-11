# include "../includes/minishell.h"

void launch_minishell(t_data *data)
{   
    while (1)
    {
        affiche le prompt (miniishell $)
        read line 
        renviie vers lexer
        decompose par parser
        execute
    }
}

void exit_minishell(t_data *data, int exit_status)
{   
    ft_printf_colour(RED, "Exiting minishell 👋\n");
    if ()

    free_all_memory(data);
    rl_clear_history(); // Le sujet dit d'avoir un working history, nous on le clean entre chaque execution
    exit(exit_status);
}

int main(int ac, char **av, char **env)
{
    t_data  data;

    if (ac != 1)
    {
        errno = EINVAL;
        perror("Error main");
        exit(EXIT_FAILURE);
    }
    ft_memset(&data, 0, sizeof(t_data));
    if (/*init data a fail*/)
        exit_minishell(&data, EXIT_FAILURE);
    launch_minishell(&data);
    return (EXIT_SUCCESS);
}

// int main()
// {
//    printf(PROMPT0 PROMPT1);
// }
