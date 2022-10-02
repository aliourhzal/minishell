#include "minishell.h"

int	ft_error(char *cmd, char *msg1, int x, t_minishell *main)
{
	main->exit_status = 1;
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (cmd)
		ft_putstr_fd(": ", 2);
	if (x)
		perror(msg1);
	else
		ft_putstr_fd(msg1, 2);
	return (1);
}

int	quote_state(int	*st, char *line, int i)
{
	int	j;

	*st = OPEN;
	j = i + 1;
	while (line[j] != line[i] && line[j])
		j++;
	if (line[j] == line[i])
		*st = CLOSE;
	i = j;
	return (i);
}

int	quotes_checker(char	*line, t_minishell *main)
{
	int		i;
	int		st;

	i = 0;
	while (line[i] == ' ')
		i++;
	st = -1;
	while (line[i])
	{
		if (line[i] == DBL_QU || line[i] == SNGL_QU)
			i = quote_state(&st, line, i);
		i++;
	}
	if (st == OPEN)
		return (ft_error(NULL, "Syntax error: Unclosed quote.\n", 0, main));
	return (0);
}

int	pipe_checker(char	*line, t_minishell *main)
{
	int	i;

	i = 0;
	while(line[i] == ' ')
		i++;
	if (line[i] == '|')
	{
		ft_error(NULL, "Syntax error: near unexpected token `|'\n", 0, main);	
		return (1);
	}
	while(line[++i])
	{
		if (line[i] == '|')
		{
			++i;
			while(line[i] == ' ' && line[i])
				i++;
			if (line[i] == '|' || !line[i])
			{
				ft_error(NULL, "Syntax error: near unexpected token `|'\n", 0, main);
				return (1);
			}
		}
	}
	return (0);
}

int	check_errors(char *line, t_minishell *main)
{
	if (quotes_checker(line, main))
		return (1);
	if (pipe_checker(line, main))
		return (1);
	return (0);
}