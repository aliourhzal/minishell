#include "minishell.h"

void    set_envp(t_minishell    *main, char **envp)
{
	int	i;
	char **p;

	p = ft_split(envp[0], '=');
	main->envp = new_env(p[0], p[1]);
	i = -1;
	while(envp[++i])
	{
		p = ft_split(envp[i], '=');
		add_env(&main->envp, new_env(p[0], p[1]));
		free_table(p);
	}
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
	main.save_std[0] = dup(0);
	main.save_std[1] = dup(1);
	main.fd = malloc(2 * sizeof(int));
	set_envp(&main, env);
	readcmd(&main);
}