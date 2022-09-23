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

void	redirect_hundler(t_command *cmd, int *check)
{
	int	fd_files[2];
	int i;
	int	j;
	
	i = -1;
	fd_files[0] = -2;
	fd_files[1] = -2;
	while(cmd->cmd[++i])
	{
		j = i;
		if (is_redirection(cmd->tokens[i]))
		{
			if (cmd->tokens[i + 1] == SPACES)
				j = i + 1;
			j++;
			*check = 1;
		}
		if (cmd->tokens[i] == REDIRECTION_OUT)
			fd_files[1] = open(cmd->cmd[j], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
		else if (cmd->tokens[i] == APPEND)
			fd_files[1] = open(cmd->cmd[j], O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
		else if (cmd->tokens[i] == REDIRECTION_IN)
			fd_files[0] = open(cmd->cmd[j], O_RDONLY);
		//else if (cmd->tokens[i] == HERDOC)
		if (*check == 1)
			change_des(fd_files, cmd->cmd[j]);
	}
}

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

char	**append_args(char **args, char *new_arg)
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
}

char	**extract_args(t_command *cmd)
{
	int	i;
	char	**args;

	i = 0;
	args = NULL;
	while (cmd->tokens[i] == SPACES)
		i++;
	i++;
	while (cmd->tokens[i + 1] == SPACES)
		i++;
	while (cmd->cmd[++i])
	{
		if (cmd->tokens[i] == SPACES)
		{
			while (cmd->tokens[i] == SPACES)
				i++;
			if (cmd->tokens[i] == WORD)
				args = append_args(args, cmd->cmd[i - 1]);
			else if (!cmd->tokens[i])
				i--;
		}
		args = append_args(args, cmd->cmd[i]);
	}
	return (args);
}

void    execute_cmd(t_command *cmd, t_minishell *main, int i)
{
	char    *cmd_word;
	int		check;
	char	**args;

	check = 0;
	if (i + 1 < main->cmds_count)
	{
		dup2(main->fd[1], 1);
		close(main->fd[1]);
	}
	redirect_hundler(cmd, &check);
	if (check)
		cmd = remove_redirect(cmd);
	cmd_word = extract_cmd(cmd);
	args = extract_args(cmd);
	if (cmd_manager(cmd_word, args, main))
		return ;
}

void	executor(t_minishell   *main)
{
	//int	id;
	int i;
	int save_std[2];

	save_std[0] = dup(0);
	save_std[1] = dup(1);
	i = -1;
	while(++i < main->cmds_count)
	{
		if (i + 1 < main->cmds_count)
		{
			pipe(main->fd);
			dup2(main->fd[0], 0);
			close(main->fd[0]);
		}
		/*id = fork();
		if (id < 0)
			return (perror("fork"));
		if (id == 0)*/
			execute_cmd(&main->full_line[i], main, i);
		if (i + 1 >= main->cmds_count)
			close(0);
	}
	dup2(save_std[0], 0);
}

/*
	int x1 = -1;
	int x2;
	while(++x1 < main->cmds_count)
	{
		x2 = -1;
		while (main->full_line[x1].cmd[++x2])
			printf(".%s.\n", main->full_line[x1].cmd[x2]);
		printf("--------------------------\n");
	}
*/

/*int i;

	i = -1;
	while(cmd->cmd[++i])
	{
		printf("%s\n", cmd->cmd[i]);
	}
	printf("-----------------------------\n");*/

/* aaaa aaaaa< a > aa >> aaa  aaaa | bbb bbbb bb"bbb"'bbbb' | ccc ccc */
