
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
			line = ft_strjoin(tmp->id, "=");
			line = ft_joinstr(line, ft_strdup(tmp->value));
		}
		if (line)
		{
			envp = insert_text(envp, ft_strdup(line));
			free(line);
		}
		tmp = tmp->next;
	}
	return (envp);
}

void	export_func(char **args, t_minishell *main)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = main->envp;
	if (!args[1])
	{
		while (tmp)
		{
			write(1, "declare -x ", 11);
			write(1, tmp->id, ft_strlen(tmp->id));
			write(1, "=\"", 2);
			write(1, tmp->value, ft_strlen(tmp->value));
			write(1, "\"", 1);
			write(1, "\n", 1);
			tmp = tmp->next;
		}
		return ;
	}
	while(args[++i])
	{
		if (check_id(args[i], main))
			update_prop(args[i], main);
	}
}
