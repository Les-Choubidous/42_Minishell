#include "../../includes/minishell.h"

// Fonction pour obtenir le nom de l'enum t_type en tant que chaîne
const char	*get_type_name(t_type type)
{
	switch (type)
	{
	case NOTHING:
		return ("NOTHING");
	case CMD:
		return ("CMD");
	case ARG:
		return ("ARG");
	case OUTPUT:
		return ("OUTPUT");
	case INPUT:
		return ("INPUT");
	case APPEND:
		return ("APPEND");
	case HEREDOC:
		return ("HEREDOC");
	case LIM:
		return ("LIM");
	case PIPE:
		return ("PIPE");
	case FLAG:
		return ("FLAG");
		// default: return ("UNKNOWN");
	}
}

void	print_tokens(t_token *token)
{
	const char	*color;
	t_token		*current;

	current = token;
	while (current)
	{
		if (current->type == CMD)
			color = BLUE;
		else if (current->type == ARG)
			color = GREEN;
		else if (current->type == PIPE)
			color = ROSE;
		else if (current->type == OUTPUT || current->type == INPUT)
			color = YELLOW;
		else if (current->type == NOTHING)
			color = RED;
		else
			color = RESET;
		printf("%sToken value: [%s]\n", color, current->value);
		printf("Token type: [%s]\n", get_type_name(current->type));
		printf("Token quote status: {%d}\n", current->quote);
		if (current->quote == 1)
			printf("Simple quotes\n");
		else if (current->quote == 2)
			printf("Double quotes\n");
		printf(RESET);
		printf("------------------\n");
		current = current->next;
	}
}

void	free_token_list(t_token *head)
{
	t_token	*current;
	t_token	*next_token;

	current = head;
	while (current)
	{
		next_token = current->next;
		free_token(current);
		current = next_token;
	}
}

void	free_token(t_token *token)
{
	if (token)
	{
		if (token->value)
		{
			free(token->value);
			token->value = NULL;
		}
		free(token);
		token = NULL;
	}
}
