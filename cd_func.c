
#include "minishell.h"

void	change_env(t_minishell *main)
{
	t_env	*pwd;
	t_env	*old_pwd;
	char	*f_pwd;

	f_pwd = NULL;
	pwd = search_env(main->envp, "PWD");
	old_pwd = search_env(main->envp, "OLDPWD");

	if (old_pwd->value)
		free(old_pwd->value);
	old_pwd->value = ft_strdup(pwd->value);
	if (pwd->value)
		free(pwd->value);
	f_pwd = getcwd(NULL, 0);
	pwd->value = ft_strdup(f_pwd);
	free(f_pwd);
}

int	cd_home(t_minishell *main)
{
	char	*home;
	int		x;

	home = extract_value("HOME", main);
	if (!home)
		return (ft_error("cd", "HOME not set.\n", 0, main));
	x = chdir(home);
	if (x == -1)
		return (ft_error("cd", "HOME", 1, main));
	change_env(main);
	free(home);
	return (0);
}

void	cd_func(char **args, t_minishell *main)
{
	int	fail;

	fail = 0;
	if (count_table(args) > 1)
	{
		fail = ft_error("cd", "too many arguments\n", 0, main);
		return ;
	}
	if (args && chdir(args[0]) < 0)
	{
		fail = ft_error("cd", args[0], 1, main);
		return ;
	}
	else if (!args)
		fail = cd_home(main);
	if (!fail)
	{
		if (args)
			change_env(main);
		main->exit_status = 0;
	}
}
