#include "minishell.h"

char	*extract_value(char *name, t_minishell *main)
{
	t_env *head;

	if (!name)
		return (NULL);
	if (name[0] == '?')
		return (ft_itoa(main->exit_status));
	head = main->envp;
	while(head && ft_strcmp(name, head->id))
		head = head->next;
	if (head)
		return(ft_strdup(head->value));
	return (NULL);
}

char	*no_variable(char *cmd_word, int start, int end)
{
	char	*new_word;
	int	x;
	int	y;

	x = -1;
	y = 0;
	new_word = malloc((ft_strlen(cmd_word) - end + start + 1) * sizeof(char));
	if (!new_word)
		return (NULL);
	while (cmd_word[++x])
	{
		if (x == start)
			x = end;
		new_word[y++] = cmd_word[x];
	}
	new_word[y] = 0;
	return (new_word);
}

char	*var_replace(char *value, char *cmd_word, int i, int j)
{
	char *new_word;

	if (value)
	{
		new_word = ft_joinstr(dup_till_end(cmd_word, cmd_word[i]), value);
		new_word = ft_joinstr(new_word, ft_strdup(&cmd_word[j]));
	}
	else
		new_word = no_variable(cmd_word, i, j);
	free(cmd_word);
	return (new_word);
}

char    *extract_name(char *cmd_word, int *i, int *j)
{
	char	*name;

	if (cmd_word[*j] >= '0' && cmd_word[*j] <= '9')
	{
		name = dup_till_end(&cmd_word[*i + 1], cmd_word[*j + 1]);
		*j += 1;
	}
	else if (cmd_word[*j] == '?')
	{
		name = ft_strdup("?");
		*j += 1;
	}
	else
	{
		while (ft_isalpha(cmd_word[*j]) || ft_isalnum(cmd_word[*j]))
			*j += 1;
		name = dup_till_end(&cmd_word[*i + 1], cmd_word[*j]);
	}
	return (name);
}

char	*name_value(char *cmd_word, t_minishell *main)
{
	int 	i;
	int		j;
	char	*name;

	i = -1;
	while (cmd_word[++i])
	{
		if (cmd_word[i] == '$' && cmd_word[i + 1])
		{
			j = i + 1;
            name = extract_name(cmd_word, &i, &j);
			cmd_word = var_replace(extract_value(name, main), cmd_word, i, j);
		}
	}
	return (cmd_word);
}