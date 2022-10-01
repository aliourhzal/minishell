#include "minishell.h"

char    *dup_till_end(char *start, char end)
{
	char    *chunk;
	int     i;

	i = 0;
	while(start[i] != end)
		i++;
	chunk = malloc((i + 1) * sizeof(char));
	i = 0;
	while(start[i] != end)
	{
		chunk[i] = start[i];
		i++;
	}
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