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

int	is_word(char token)
{
	if (token == WORD || token == WORD_D || token == WORD_S)
		return (1);
	return (0);
}

char	**fusion_word(char **cmd, int fusion_p)
{
	char	**new_cmd;
	int	i;
	int	j;

	i = -1;
	j = -1;
	new_cmd = malloc(count_table(cmd) * sizeof(char *));
	while(cmd[++i])
	{
		if (i == fusion_p)
		{
			new_cmd[++j] = ft_strjoin(cmd[i], cmd[i + 1]);
			i++;
		}
		else
			new_cmd[++j] = ft_strdup(cmd[i]);
	}
	new_cmd[++j] = NULL;
	free_table(cmd);
	return (new_cmd);
}

char	*fusion_token(char *tokens, int fusion_p)
{
	int		i;
	int		j;
	char	*new_token;

	i = -1;
	j = -1;
	new_token = malloc(ft_strlen(tokens) * sizeof(char));
	while(tokens[++i])
	{
		if (i == fusion_p)
		{
			new_token[++j] = WORD; 
			i++;
		}
		else
			new_token[++j] = tokens[i];
	}
	new_token[++j] = 0;
	free(tokens);
	return (new_token);
}

void	combine_words(t_minishell *main)
{
	int	i;
	int	j;

	i = -1;
	while(++i < main->cmds_count)
	{
		j = -1;
		while(main->full_line[i].cmd[++j])
		{
			if (is_word(main->full_line[i].tokens[j])
				&& is_word(main->full_line[i].tokens[j + 1]))
			{
				main->full_line[i].cmd = fusion_word(main->full_line[i].cmd, j);
				main->full_line[i].tokens = fusion_token(main->full_line[i].tokens, j);
				j--;
			}
		}
	}
}

void	lexer(t_minishell *main, char *line)
{
	int	i;

	i = 0;
	if (check_errors(line, main))
		return ;
	while (line[i] == ' ')
		i++;
	tokenize_line(&line[i], main);
	variable_expansion(&line[i], main);
	combine_words(main);
	// (void)line;
	/*int x1 = -1;
	int x2;
	while(++x1 < main->cmds_count)
	{
		x2 = -1;
		while (main->full_line[x1].cmd[++x2])
			printf(".%s.\n", main->full_line[x1].cmd[x2]);
		printf("--------------------------\n");
	}*/
	executor(main);
}