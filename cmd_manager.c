#include "minishell.h"

int cmd_manager(char *cmd_word, char **args, t_minishell *main)
{
	if (!ft_strcmp(cmd_word, "echo"))
		echo_func(args, main);
	else if (!ft_strcmp(cmd_word, "pwd"))
		pwd_func(main);
	else if (!ft_strcmp(cmd_word, "cd"))
		cd_func(args, main);
	else if (!ft_strcmp(cmd_word, "unset"))
		unset_func(args, main);
	else if (!ft_strcmp(cmd_word, "export"))
		export_func(args, main);
	else
		return (0);
	dup2(main->save_std[1], 1);
	return (1);
}