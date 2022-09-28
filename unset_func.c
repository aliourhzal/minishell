
#include "minishell.h"

void	unset_func(char **args, t_minishell *main)
{
	int	i;

	i = 0;
	while (args[++i])
		del_env(main->envp, args[i]);
	main->exit_status = 0;
}
