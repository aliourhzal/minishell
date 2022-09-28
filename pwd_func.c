#include "minishell.h"

void	pwd_func(t_minishell *main)
{
	char	*path;

	path = extract_value("PWD", main);
    write(1, path, ft_strlen(path));
	write(1, "\n", 1);
    free(path);
	main->exit_status = 0;
}
