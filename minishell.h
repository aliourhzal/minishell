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

typedef	struct s_env
{
	char *id;
	char *value;
	struct s_env *next;
	struct s_env *prev;
}	t_env;

typedef struct s_command
{
	char **cmd;
	char *tokens;
} t_command;

typedef struct s_minishell
{
	t_env *envp;
	t_command *full_line;
	int	*fd;
	int	cmds_count;
	int exit;
	int exit_status;
	int	save_std[2];
} t_minishell;

void	free_table(char **table);
int		count_table(char **table);
void    tokenize_line(char *line, t_minishell *main);
void    lexer(t_minishell   *main, char *line);
void    parser(t_command *t_line, t_minishell *main);
int		ft_error(char *cmd, char *msg1, int x, t_minishell *main);
void	executor(t_minishell   *main);
void	variable_expansion(t_minishell   *main);
char    *dup_till_end(char *start, char end);
int		cmd_manager(char *cmd_word, char **args, t_minishell *main);
char	*extract_value(char *name, t_minishell *main);

//envp
t_env	*new_env(char *id, char *value);
t_env	*last_env(t_env *lst);
void	add_env(t_env **lst, t_env *new);
t_env	*search_env(t_env *envp, char *id);
int		del_env(t_env *lst, char *id);
// commands
void	echo_func(char **args, t_minishell *main);
void	pwd_func(t_minishell *minishell);
void	cd_func(char **args, t_minishell *main);
void	unset_func(char **args, t_minishell *main);
void	export_func(char **args, t_minishell *main);