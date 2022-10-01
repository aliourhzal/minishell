#include "minishell.h"

int	tokenize_redirect(char *line, t_command *t_line)
{
	int i;

	i = 0;
	if (line[0] == '>')
	{
		while (line[i] == '>')
			i++;
		t_line->cmd = insert_text(t_line->cmd, dup_till_end(line, line[i]));
		if (line[1] == '>')
			t_line->tokens = insert_token(t_line->tokens, APPEND);
		else
			t_line->tokens = insert_token(t_line->tokens, REDIRECTION_OUT);
	}
	else if (line[0] == '<')
	{
		while (line[i] == '<')
			i++;
		t_line->cmd = insert_text(t_line->cmd, dup_till_end(line, line[i]));
		if (line[1] == '<')
			t_line->tokens = insert_token(t_line->tokens, HERDOC);
		else
			t_line->tokens = insert_token(t_line->tokens, REDIRECTION_IN);
	}
	return (i);
}

int    tokenize_quotes(char *line, t_command *t_line)
{
	int	i;

	i = 1;
	if (line[0] == '\'')
	{
		while(line[i] != '\'')
			i++;
		t_line->cmd = insert_text(t_line->cmd, dup_till_end(&line[1], line[i]));
		t_line->tokens = insert_token(t_line->tokens, WORD_S);
	}
	else if (line[0] == '\"')
	{
		while(line[i] != '\"')
			i++;
		t_line->cmd = insert_text(t_line->cmd, dup_till_end(&line[1], line[i]));
		t_line->tokens = insert_token(t_line->tokens, WORD_D);
	}
	return (++i);
}

int    tokenize_spaces(char *line, t_command *t_line)
{
	int	i;

	i = 0;
	while(line[i] && line[i] == ' ')
		i++;
	t_line->cmd = insert_text(t_line->cmd, ft_strdup(" "));
	t_line->tokens = insert_token(t_line->tokens, SPACES);
	return (i);
}

int    tokenize_text(char *line, t_command *t_line)
{
	int	i;

	i = 0;

	while(line[i] && line[i] != ' ' && line[i] != '<'
		&& line[i] != '>' && line[i] != '|' && line[i] != DBL_QU && line[i] != SNGL_QU)
		i++;
	t_line->cmd = insert_text(t_line->cmd, dup_till_end(line, line[i]));
	t_line->tokens = insert_token(t_line->tokens, WORD);
	return (i);
}

int	tokenize_pipe(char *line, t_command *t_line)
{
	t_line->cmd = insert_text(t_line->cmd, dup_till_end(&line[0], line[1]));
	t_line->tokens = insert_token(t_line->tokens, PIPE);
	return (1);
}