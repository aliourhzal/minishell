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
}	t_command;

typedef struct s_minishell
{
	t_env *envp;
	t_command *full_line;
	char	**args;
	char	**env;
	int	*fd;
	int	cmds_count;
	int exit;
	int exit_status;
	int	save_std[2];
}	t_minishell;


void    	tokenize_line(char *line, t_minishell *main);
void    	lexer(t_minishell   *main, char *line);
void    	parser(t_command *t_line, t_minishell *main);
void		executor(t_minishell   *main);
void		variable_expansion(t_minishell   *main);
int			cmd_manager(char *cmd_word, char **args, t_minishell *main);
void		wildcard_expansion(t_minishell *main);
int			ft_revncmp(char *s, char *to_find);
int			ft_strstrn(const char *haystack, const char *needle, size_t len);
char		**envp_table(t_minishell *main);

//variable utils
char		*name_value(char *cmd_word, t_minishell *main);
char		*extract_value(char *name, t_minishell *main);

//cmd path utils
char		*extract_cmd(t_command *cmd);
char		**append_args(char **args, char *new_arg);
char		**extract_args(t_command *cmd);
int			is_accessible(char *file);
char		*add_slash(char *path);

//redirect utils
int			is_redirection(char token);
char		**skip_redirect(t_command	*cmd);
char		*skip_tokens(char *tokens);
t_command	*remove_redirect(t_command	*cmd);
void		change_des(int *fd_files, char *file);

// redirect hundler
void		redirect_hundler(t_command *cmd/*, int *check*/);

//wildcard utils
char		**extract_pat(char *word, char **pat);
char		**filter_files(char **files, char *pat);
char		**match_astr(char *word, char **files);
void		construct_cmd(char *word, char token, t_command *final_cmd);
char		**cd_files(void);

//tokenize utils
int			tokenize_redirect(char *line, t_command *t_line);
int			tokenize_quotes(char *line, t_command *t_line);
int			tokenize_pipe(char *line, t_command *t_line);
int			tokenize_spaces(char *line, t_command *t_line);
int			tokenize_text(char *line, t_command *t_line);

//general utils
char    	*dup_till_end(char *start, char end);
char		**insert_text(char **table, char *new_line);
char    	*insert_token(char *token_table, char new_token);
void		free_table(char **table);
int			count_table(char **table);

//error check
int			ft_error(char *cmd, char *msg1, int x, t_minishell *main);
int			quote_state(int	*st, char *line, int i);
int			quotes_checker(char	*line, t_minishell *main);
int			pipe_checker(char	*line, t_minishell *main);
int			check_errors(char *line, t_minishell *main);

//envp
t_env		*new_env(char *id, char *value);
t_env		*last_env(t_env *lst);
void		add_env(t_env **lst, t_env *new);
t_env		*search_env(t_env *envp, char *id);
int			del_env(t_env *lst, char *id);

// commands
void		echo_func(char **args, t_minishell *main);
void		pwd_func(t_minishell *minishell);
void		cd_func(char **args, t_minishell *main);
void		unset_func(char **args, t_minishell *main);
void		export_func(char **args, t_minishell *main);