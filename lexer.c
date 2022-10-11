#include "minishell.h"

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
	int	status;

	i = 0;
	if (check_errors(line, main))
		return ;
	while (line[i] == ' ')
		i++;
	if (!line[i])
		return ;
	tokenize_line(&line[i], main);
	variable_expansion(main);
	combine_words(main);
	wildcard_expansion(main);
	executor(main);
	wait(&status);
	main->exit_status = WEXITSTATUS(status);
	dup2(main->save_std[0], 0);
}
