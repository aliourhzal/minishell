#pragma once

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <term.h>
# include "libftX/libft.h"
# include "color.h"

# define    OPEN    1
# define    CLOSE   0

# define    DBL_QU '\"'
# define    SNGL_QU '\''

# define    REDIRECTION_OUT 'a' 
# define    REDIRECTION_IN 'b'
# define    APPEND 'c'
# define    PIPE 'd'
# define    HERDOC 'e'
# define    WORD 'f'
# define    WORD_D 'g'
# define    WORD_S 'h'
# define    SPACES 'i'

typedef struct s_command
{
	char **cmd;
	int *tokens;
} t_command;

typedef struct s_minishell
{
	char **envp;
	t_command *full_line;
	int exit;
	int exit_status;
} t_minishell;

void	free_table(char **table);
int		count_table(char **table);


