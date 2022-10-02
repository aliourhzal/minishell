#include "minishell.h"

int is_redirection(char token)
{
	if (token == REDIRECTION_IN || token == REDIRECTION_OUT
		|| token == APPEND || token == HERDOC)
		return (1);
	return (0);
}

char	**skip_redirect(t_command	*cmd)
{
	char	**new_words;
	int	i;
	int	j;

	i = -1;
	j = -1;
	new_words = malloc((count_table(cmd->cmd) - 1) * sizeof(char *));
	if (!new_words)
		return (NULL);
	while(cmd->cmd[++i])
	{
		if (is_redirection(cmd->tokens[i]))
		{
			if (cmd->tokens[i + 1] == SPACES)
				new_words[++j] = ft_strdup(cmd->cmd[++i]);
			i += 2;
		}
		new_words[++j] = ft_strdup(cmd->cmd[i]);
	}
	new_words[++j] = NULL;
	return (new_words);
}

char	*skip_tokens(char *tokens)
{
	char	*new_tokens;
	int	i;
	int	j;

	i = -1;
	j = -1;
	new_tokens = malloc((ft_strlen(tokens) - 1) * sizeof(char));
	if (!new_tokens)
		return (NULL);
	while (tokens[++i])
	{

		if (is_redirection(tokens[i]))
		{
			if (tokens[i + 1] == SPACES)
				new_tokens[++j] = tokens[++i];
			i += 2;
		}
		new_tokens[++j] = tokens[i];
	}
	new_tokens[++j] = 0;
	return (new_tokens);
}

t_command	*remove_redirect(t_command	*cmd)
{
	t_command	*new_cmd;
	
	new_cmd = malloc(sizeof(t_command));
	new_cmd->cmd = skip_redirect(cmd);
	new_cmd->tokens = skip_tokens(cmd->tokens);
	/*fatal error function must be implemented*/
	free(cmd->tokens);
	free_table(cmd->cmd);
	free(cmd);
	return (new_cmd);
}

void	change_des(int *fd_files, char *file)
{
	if (fd_files[0] > 0)
	{
		dup2(fd_files[0], 0);
		close(fd_files[0]);
	}
	else if (fd_files[1] > 0)
	{
		dup2(fd_files[1], 1);
		close(fd_files[1]);
	}
	else
		perror(file);
}
