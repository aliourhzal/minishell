#include "minishell.h"

int cmd_manager(char *cmd_word, char **args, t_minishell *main)
{
    (void)main;
    if (!ft_strcmp(cmd_word, "echo"))
        echo_func(args);
    return (1);
}