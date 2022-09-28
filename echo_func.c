#include "minishell.h"

void	echo_printer(char **args, int	n_line)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		write(1, args[i], ft_strlen(args[i]));
		write(1, " ", 1);
	}
	if (!n_line)
		write(1, "\n", 1);
}

int	is_flag(char *flag)
{
	int	i;

	i = 0;
	if (!ft_strncmp(flag, "-n", 2))
	{
		while (flag[++i])
			if (flag[i] != 'n')
				break;
		if (!flag[i])
			return (1);
		else
			return (0);
	}
	return (0);
}

void	echo_func(char **args, t_minishell *main)
{
	int	i;
	int	n_line;

	i = -1;
	n_line = 0;
	if (args)
	{
		while(args[++i][0] == '-')
		{
			if (is_flag(args[i]))
			{
				n_line = 1;
				i++;
			}
			else
				break;
		}
		echo_printer(&args[i], n_line);
	}
	else
		write(1, "\n", 1);
	main->exit_status = 0;
}