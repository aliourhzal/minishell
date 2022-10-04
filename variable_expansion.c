#include "minishell.h"

void	variable_expansion(t_minishell   *main)
{
	int i;
	int j;

	i = -1;
	while(++i < main->cmds_count)
	{
		j = -1;
		while(main->full_line[i].cmd[++j])
			if ((main->full_line[i].tokens[j] == WORD
				|| main->full_line[i].tokens[j] == WORD_D)
				&& ft_strcmp(main->full_line[i].cmd[j], "$"))
				main->full_line[i].cmd[j] = name_value(main->full_line[i].cmd[j], main);
	}
}
