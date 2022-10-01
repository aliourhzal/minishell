#include "minishell.h"

char	**cd_files(void)
{
	DIR				*dir;
	struct dirent	*d_f;
	char	**files;

	files = 0;
	dir = opendir(".");
	if (dir)
	{
		d_f = readdir(dir);
		while (d_f)
		{
			if (d_f->d_name[0] != '.')
				files = insert_text(files, ft_strdup(d_f->d_name));
			d_f = readdir(dir);
		}
		closedir(dir);
	}
	return (files);
}

void	patterns(t_command *cmd)
{
	t_command *final_cmd;
	int	i;

	i = -1;
	final_cmd = malloc(sizeof(t_command));
	final_cmd->tokens = NULL;
	final_cmd->cmd = NULL;
	while (cmd->cmd[++i])
		construct_cmd(cmd->cmd[i], cmd->tokens[i], final_cmd);
	free_table(cmd->cmd);
	free(cmd->tokens);
	cmd->cmd = final_cmd->cmd;
	cmd->tokens = final_cmd->tokens;
	free(final_cmd);
}

void	wildcard_expansion(t_minishell *main)
{
	int	i;
	int	j;

	i = -1;
	
	while (++i < main->cmds_count)
	{
		j = -1;
		while(main->full_line[i].cmd[++j])
		{
			if (main->full_line[i].tokens[j] != SPACES
				&& ft_strchr(main->full_line[i].cmd[j], '*'))
				patterns(&main->full_line[i]);
		}
	}
}
