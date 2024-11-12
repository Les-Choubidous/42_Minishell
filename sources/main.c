# include "../includes/minishell.h"

void exit_minishell(t_data *data, int exit_status);
void launch_minishell(t_data *data);

void launch_minishell(t_data *data)
{   
    while (1)  
    {
        signal_interactive();
        data->line = readline(PROMPT0 PROMPT1);
        if (data->line == NULL)
            exit_minishell(data, EXIT_SUCCESS); 
        signal_non_interacitve();
        if (ft_strlen(data->line))
            add_history(data->line);
        /*if (data->line[0] != '\0')
            add_history(data->line);
        if (lexer(data) == EXIT_FAILURE ||
            parser(data) == EXIT_FAILURE || 
            executor(data) == EXIT_FAILURE)
        {
            free_mem_between_cmd(data);
            continue ;
        }
        free_mem_between_cmd(data);*/
    }
}

void exit_minishell(t_data *data, int exit_status)
{   
    ft_printf_colour(RED, "Exiting minishell 👋\n");
    /*if (ft_getenv("HISTFILE=", data))
		write_history(ft_getenv("HISTFILE=", data) + 9);
    free_all_memory(data);*/
    rl_clear_history(); // Le sujet dit d'avoir un working history, nous on le clean entre chaque execution
    exit(exit_status);
}

int main(int ac, char **av, char **env)
{
    t_data  data;

    (void)av;
    if (ac != 1)
    {
        errno = EINVAL;
        perror("Error main");
        exit(EXIT_FAILURE);
    }
    ft_memset(&data, 0, sizeof(t_data));
    /*if (init_data(&data, env) == EXIT_FAILURE)
        exit_minishell(&data, EXIT_FAILURE);*/
    launch_minishell(&data);
    return (EXIT_SUCCESS);
}
