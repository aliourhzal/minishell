
#include "minishell.h"

int	is_special(char c, char cpo)
{
	if (c == '+' && cpo == '=')
		return (1);
	if (ft_isalpha(c) || ft_isdigit(c) || c == ' ')
		return (1);
	if (c == '=')
		return (1);
	return (0);
}

int	check_id(char *args, t_minishell *main)
{
	int	i;

	i = 0;
	if (!ft_isalpha(args[0]))
	{
		ft_error("export", "not a valid identifier\n", 0, main);
		return (0);
	}
	while (args[++i])
	{
		if (!is_special(args[i], args[i + 1]))
		{
			ft_error("export", "not a valid identifier\n", 0, main);
			return (0);
		}
	}
	return (1);
}

char	*find_value(char *arg, int i, int *operation)
{
	char	*value;

	if (arg[i] == '=')
	{
		value = dup_till_end(&arg[i + 1], '\0');
		*operation = 0;
	}
	else if (arg[i] == '+')
	{
		*operation = 1;
		value = dup_till_end(&arg[i + 2], '\0');
	}
	else if (!arg[i] && arg[i - 1] == '=')
	{
		*operation = 0;
		value = dup_till_end(&arg[i], '\0');
	}
	else if (!arg[i])
		value = NULL;
	return (value);	
}

void	update_exist(t_env *new, int operation, char *value)
{
	if (new)
	{
		if (operation == 1)
			new->value = ft_joinstr(new->value, value);
		else if (operation == 0)
		{
			if (new->value)
				free(new->value);
			new->value = value;
		}
	}
}

void	update_prop(char *arg, t_minishell *main)
{
	int	i;
	char	*id;
	char	*value;
	t_env	*new;
	int		operation;
	
	i = 0;
	operation = -1;
	while (arg[i] && (arg[i] != '=' && arg[i] != '+'))
		i++;
	id = dup_till_end(arg, arg[i]);
	value = find_value(arg, i, &operation);
	new = search_env(main->envp, id);
	update_exist(new, operation, value);
	if (!new)
	{
		new = new_env(id, value);
		add_env(&main->envp, new);
		free(id);
		if (value)
			free(value);
	}
}

char	**add_line(char **table, char *new_line)
{
	int	i;
	char	**new_envp;

	i = 0;
	new_envp = malloc((count_table(table) + 2) * sizeof(char *));
	while(table && table[i])
	{
		new_envp[i] = table[i];
		i++;
	}
	new_envp[i++] = new_line;
	new_envp[i] = 0;
    if (table)
	    free(table);
	return (new_envp);
}

char	**envp_table(t_minishell *main)
{
	t_env *tmp;
	char	**envp;
	char	*line;

	tmp = main->envp;
	envp = NULL;
	while (tmp)
	{
		if (!tmp->value)
			line = ft_strdup(tmp->id);
		else
		{
			line = ft_strjoin(tmp->id, "=\"");
			line = ft_joinstr(line, ft_strdup(tmp->value));
			line = ft_joinstr(line, ft_strdup("\""));
		}
		if (line)
		{
			envp = add_line(envp, ft_strdup(line));
			free(line);
		}
		tmp = tmp->next;
	}
	return (envp);
}

void	export_func(char **args, t_minishell *main)
{
	int		i;
	char	**envp;

	i = -1;
	if (!args[1])
	{
		envp = envp_table(main);
		while (envp[++i])
		{
			write(1, "declare -x ", 11);
			write(1, envp[i], ft_strlen(envp[i]));
			write(1, "\n", 1);
		}
		free_table(envp);
		return ;
	}
	i = 0;
	while(args[++i])
	{
		if (check_id(args[i], main))
			update_prop(args[i], main);
	}
}
