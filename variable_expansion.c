#include "minishell.h"

char	*extrat_value(char *name, t_minishell *main)
{
	char	**p;
	char	*value;
	int	i;

	i = -1;
	while(main->envp[++i])
	{
		p = ft_split(main->envp[i], '=');
		if (!ft_strcmp(p[0], name))
		{
			value = ft_strdup(p[1]);
			free_table(p);
			return(value);
		}
		free_table(p);
	}
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

char	*extract_name(char *cmd_word, t_minishell *main)
{
	printf("before: %s\n", cmd_word);

	int 	i;
	int		j;
	char	*name;
	char	*value;

	i = -1;
	name = NULL;
	while (cmd_word[++i])
	{
		if (cmd_word[i] == '$')
		{
			j = i + 1;
			while(ft_isalpha(cmd_word[j]) || ft_isalnum(cmd_word[j]))
				j++;
			name = dup_till_end(&cmd_word[i + 1], cmd_word[j]);
			value = extrat_value(name, main);
			cmd_word = var_replace(value, cmd_word, i, j);
		}
	}
	printf("after: %s\n", cmd_word);
	return (cmd_word);
}


void	variable_expansion( char *line, t_minishell   *main)
{
	int i;
	int j;
	(void)line;

	i = -1;
	while(++i < main->cmds_count)
	{
		j = -1;
		while(main->full_line[i].cmd[++j])
			if (main->full_line[i].tokens[j] == WORD || main->full_line[i].tokens[j] == WORD_D)
				main->full_line[i].cmd[j] = extract_name(main->full_line[i].cmd[j], main);
	}
	/*(void)line;
	int x = -1;
	int y;
	while(++x < main->cmds_count)
	{
		y = -1;
		while (main->full_line[x].cmd[++y])
			printf(".%s.\n", main->full_line[x].cmd[y]);
		printf("--------------------------\n");
	}*/
}