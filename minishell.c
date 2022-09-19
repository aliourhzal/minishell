#include "minishell.h"

int count_table(char **table)
{
	int i;

	i = 0;
	while(table[i])
		i++;
	return (i);
}

void    free_table(char **table)
{
	int i;

	i = 0;
	while(table[i])
		free(table[i++]);
	free(table);
}

void    set_envp(t_minishell    *main, char **envp)
{
	int i;
	int len;

	i = -1;
	len = count_table(envp);
	main->envp = malloc((len + 1) * sizeof(char *));
	while(++i < len)
		main->envp[i] = ft_strdup(envp[i]);
	main->envp[i] = NULL;
}

void    readcmd(t_minishell *main)
{
	char		*line;
	char		*prompt;

	prompt = "🐵"BOLDBLUE" Minishell$> " RESET;
	line = readline(prompt);
	while (line)
	{
		add_history(line);
		if (line[0])
			lexer(main, line);
		if (main->exit == 1)
			break ;
		free(line);
		line = readline(prompt);
	}
	free(line);
}

int main(int ac, char** av, char **env)
{
	t_minishell main;

	(void)  ac;
	(void)  av;

	main.full_line = NULL;
	set_envp(&main, env);
	readcmd(&main);
}