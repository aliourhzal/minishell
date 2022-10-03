#include "minishell.h"

char	*extract_cmd(t_command    *cmd)
{
	int i;
	char	*word_cmd;

	i = 0;
	while (cmd->tokens[i] != WORD && cmd->tokens[i] != WORD_D
		&& cmd->tokens[i] != WORD_S)
		i++;
	if (cmd->tokens[i + 1] == WORD_D || cmd->tokens[i + 1] == WORD_S)
		word_cmd = ft_strjoin(cmd->cmd[i], cmd->cmd[i + 1]);
	else
		word_cmd = ft_strdup(cmd->cmd[i]);
	return (word_cmd);
}

/*char	**append_args(char **args, char *new_arg)
{
	int	i;
	char	**args_table;

	i = -1;
	args_table = malloc((count_table(args) + 2) * sizeof(char *));
	if (!args_table)
		return (NULL);
	if (args)
		while (args[++i])
			args_table[i] = ft_strdup(args[i]);
	if (i == -1)
		i++;
	args_table[i++] = ft_strdup(new_arg);
	args_table[i] = NULL;
	free_table(args);
	return (args_table);
}*/

char	**extract_args(t_command *cmd)
{
	int	i;
	char	**args;

	i = 0;
	args = NULL;
	while (cmd->tokens[i] == SPACES)
		i++;
	while (cmd->cmd[i])
	{
		if (is_redirection(cmd->tokens[i]))
		{
			i++;
			if (cmd->tokens[i] == SPACES)
				i++;
			i++;
		}
		if (cmd->tokens[i] != SPACES)
			args = insert_text(args, cmd->cmd[i]);
		i++;
	}
	return (args);
}

int	is_accessible(char *file)
{
	if (!access(file, F_OK))
		if (!access(file, X_OK))
			return (1);
	return (0);
}

char	*add_slash(char *path)
{
	char	*cmd;

	cmd = ft_strjoin(path, "/");
	free(path);
	return (cmd);
}