#include "minishell.h"

char *build_msg(char token)
{
	char *msg;

	if (token == REDIRECTION_IN)
		msg = ft_strjoin("Syntax error near unexpected token `", "<");
	else if (token == REDIRECTION_OUT)
		msg = ft_strjoin("Syntax error near unexpected token `", ">");
	else if (token == APPEND)
		msg = ft_strjoin("Syntax error near unexpected token `", ">>");
	else if (token == HERDOC)
		msg = ft_strjoin("Syntax error near unexpected token `", "<<");
	else if (token == PIPE)
		msg = ft_strjoin("Syntax error near unexpected token `", "|");
	else if (token == REDIRECTION_OUT)
		msg = ft_strjoin("Syntax error near unexpected token `", ">");
	return (ft_joinstr(msg, ft_strdup("'\n")));
}

int	token_errors(t_command *t_line, t_minishell *main)
{
	int	i;
	char *msg;

	i = -1;
	while(t_line->tokens[++i])
	{
		if (t_line->tokens[i] == REDIRECTION_IN || t_line->tokens[i] == REDIRECTION_OUT
			|| t_line->tokens[i] == APPEND || t_line->tokens[i] == HERDOC)
		{
			if (t_line->tokens[++i] == SPACES)
				i++;
			if (t_line->tokens[i] != WORD && t_line->tokens[i] != WORD_D && t_line->tokens[i] != WORD_S)
			{
				msg = build_msg(t_line->tokens[i]);
				ft_error(NULL, msg, 0, main);
				free(msg);
				return (1);
			}
		}
	}
	return (0);
}

void    tokenize_line(char *line, t_minishell *main)
{
	int i;
	t_command t_line;

	t_line.cmd = NULL;
	t_line.tokens = NULL;
	i = 0;
	while(line[i])
	{
		if (line[i] == '<' || line[i] == '>')
			i += tokenize_redirect(&line[i], &t_line);
		else if (line[i] == '\'' || line[i] == '\"')
			i += tokenize_quotes(&line[i], &t_line);
		else if (line[i] == '|')
			i += tokenize_pipe(&line[i], &t_line);
		else if (line[i] == ' ')
			i += tokenize_spaces(&line[i], &t_line);
		else
			i += tokenize_text(&line[i], &t_line);
	}
	if (token_errors(&t_line, main))
		return ;
	parser(&t_line, main);
    free_table(t_line.cmd);
    free(t_line.tokens);
}
