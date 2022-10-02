#include "minishell.h"

void	read_till_delim(char *delimeter)
{
	int		fd;
	char	*line;

	fd = open("_HEREDOC_", O_CREAT | O_RDWR | O_TRUNC | O_APPEND, S_IWUSR | S_IRUSR);
	line = readline("> ");
	while (line && ft_strcmp(line, delimeter))
	{
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(fd);
}

void	redirect_hundler(t_command *cmd/*, int *check*/)
{
	int	fd_files[2];
	int i;
	int	j;
	int	check;
	
	i = -1;
	check = 0;
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
			/***/check = 1;
		}
		if (cmd->tokens[i] == REDIRECTION_OUT)
			fd_files[1] = open(cmd->cmd[j], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
		else if (cmd->tokens[i] == APPEND)
			fd_files[1] = open(cmd->cmd[j], O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
		else if (cmd->tokens[i] == REDIRECTION_IN)
			fd_files[0] = open(cmd->cmd[j], O_RDONLY);
		else if (cmd->tokens[i] == HERDOC)
		{
            read_till_delim(cmd->cmd[j]);
			fd_files[0] = open("_HEREDOC_", O_RDONLY);
		}
		if (/***/check == 1)
			change_des(fd_files, cmd->cmd[j]);
		i = j;
		fd_files[0] = -2;
		fd_files[1] = -2;
	}
}