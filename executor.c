#include "minishell.h"

char	*find_path(char *cmd_word, t_minishell *main)
{
	int		i;
	char	**paths;
	char	*ap_cmd;

	i = -1;
	paths = ft_split(extract_value("PATH", main), ':');
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		paths[i] = add_slash(paths[i]);
		ap_cmd = ft_strjoin(paths[i], cmd_word);
		if (!ap_cmd)
			return (NULL);
		if (is_accessible(ap_cmd))
			break ;
		else if (!access(ap_cmd, F_OK) && access(ap_cmd, X_OK))
			ft_error(ap_cmd, NULL, 1, main);
		free(ap_cmd);
	}
	if (!paths[i])
		ap_cmd = NULL;
	free_table(paths);
	return (ap_cmd);
}

void	execute_outsiders(char *cmd_word, char **args, t_minishell *main)
{
	char	*ap_cmd;

	if (!access(cmd_word, F_OK))
	{
		if (!access(cmd_word, X_OK))
			execve(cmd_word, args, NULL);
		else
			ft_error(cmd_word, NULL, 1, main);
	}
	else
	{
		ap_cmd = find_path(cmd_word, main);
		if (!ap_cmd)
			ft_error(cmd_word, "command not found\n", 0, main);
		execve(ap_cmd, args, NULL);

	}
	free(ap_cmd);
}

void    execute_cmd(t_command *cmd, t_minishell *main, int i)
{
	char    *cmd_word;
	//int		check;
	char	**args;

	//check = 0;
	if (i + 1 < main->cmds_count)
	{
		dup2(main->fd[1], 1);
		close(main->fd[1]);
	}
	redirect_hundler(cmd/*, &check*/);
	/*if (check)
		cmd = remove_redirect(cmd);*/
	cmd_word = extract_cmd(cmd);
	args = extract_args(cmd);
	if (!cmd_manager(cmd_word, args, main))
		execute_outsiders(cmd_word, args, main);
	free_table(args);
	free(cmd_word);
}

void	executor(t_minishell   *main)
{
	int i;
	int	id;

	i = -1;
	while(++i < main->cmds_count)
	{
		if (i + 1 < main->cmds_count)
			pipe(main->fd);
		id = fork();
		if (id < 0)
			ft_error("fork", NULL, 1, main);
		if (id == 0)
			execute_cmd(&main->full_line[i], main, i);
		if (i + 1 < main->cmds_count)
		{
			dup2(main->fd[0], 0);
			close(main->fd[0]);
		}
		else
			close(0);
	}
}
