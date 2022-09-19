#include "minishell.h"

char    *dup_till_end(char *start, char end)
{
	char    *chunk;
	int     i;

	i = 0;
	while(start[i] != end)
		i++;
	chunk = malloc((i + 1) * sizeof(char));
	i = -1;
	while(start[++i] != end)
		chunk[i] = start[i];
	chunk[i] = '\0';
	return (chunk);
}

char **insert_text(char **table, char *new_line)
{
	int len;
	char **new_table;
	int i;

	len = 0;
	if (table)
		len = count_table(table);
	new_table = malloc((len + 2) * sizeof(char *));
	i = 0;
	while(table && table[i])
	{
		new_table[i] = table[i];
		i++;
	}
	new_table[i++] = new_line;
	new_table[i] = NULL;
	if (table)
		free(table);
	return (new_table);
}

char    *insert_token(char *token_table, char new_token)
{
	int len;
	char    *new_Ttable;
	int i;

	i = 0;
	len = 0;
	if (token_table)
		len = ft_strlen(token_table);
	new_Ttable = malloc((len + 2) * sizeof(char));
	while(token_table && token_table[i])
	{
		new_Ttable[i] = token_table[i];
		i++;
	}
	new_Ttable[i++] = new_token;
	new_Ttable[i] = '\0';
	if (token_table)
		free(token_table);
	return (new_Ttable);
}

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
		&& line[i] != '>'&& line[i] != '|')
		i++;
	t_line->cmd = insert_text(t_line->cmd, dup_till_end(line, line[i]));
	t_line->tokens = insert_token(t_line->tokens, WORD);
	return (i);
}

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

int	tokenize_pipe(char *line, t_command *t_line)
{
	t_line->cmd = insert_text(t_line->cmd, dup_till_end(&line[0], line[1]));
	t_line->tokens = insert_token(t_line->tokens, PIPE);
	return (1);
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
}