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
	i = -1;
	while(table[++i])
		new_table[i] = table[i];
	new_table[i++] = new_line;
	new_table[i] = NULL;
	return (new_table);
}

char    *insert_token(char *token_table, char new_token)
{
	int len;
	char    *new_Ttable;
	int i;

	i = -1;
	len = 0;
	if (token_table)
		len = ft_strlen(token_table);
	new_Ttable = malloc((len + 2) * sizeof(char));
	while(token_table[++i])
		new_Ttable[i] = token_table[i];
	new_Ttable[i++] = new_token;
	new_Ttable[i] = '\0';
	return (new_Ttable);
}

void    tokenize_redirect(char *line, t_command *t_line)
{
	int i;

	i = 0;
	if (line[0] == '>')
	{
		while (line[i] == '>')
			i++;
		t_line->cmd = insert_text(t_line->cmd, dup_till_end(line, line[i]));
		t_line->tokens = insert_token(t_line->tokens, REDIRECTION_OUT);
	}
	else if (line[0] == '<')
	{
		while (line[i] == '<')
			i++;
		t_line->cmd = insert_text(t_line->cmd, dup_till_end(line, line[i]));
		t_line->tokens = insert_token(t_line->tokens, REDIRECTION_IN);
	}
}

void    tokenize_line(char *line, t_minishell *main)
{
	int i;
	t_command t_line;   

	i = -1;
	while(line[++i])
	{
		if (line[i] == '<' || line[i] == '>')
			tokenize_redirect(&line[i], &t_line);
	}
}