#include "minishell.h"

char	**extract_pat(char *word, char **pat)
{
	int	i;
	int	j;

	i = 0;
	if (word[0] != '*')
	{
		while (word[i] != '*')
			i++;
		pat = insert_text(pat, insert_token(dup_till_end(word, word[i]), '*'));
	}
	while (word[i])
	{
		while (word[i] == '*')
			i++;
		j = i;
		while (word[j] && word[j] != '*')
			j++;
		if (!word[j])
			break ;
		pat = insert_text(pat, ft_joinstr(ft_strdup("*"), insert_token(dup_till_end(&word[i], word[j]), '*')));
		while(word[j + 1] == '*')
			j++;
		i = j;
	}
	if (word[i] && word[i - 1] == '*')
		pat = insert_text(pat, dup_till_end(&word[i - 1], '\0'));
	return (pat);
}

char	**filter_files(char **files, char *pat)
{
	int	j;
	char	**new_files;

	j = -1;
	new_files = NULL;
	if (pat[0] == '*' && pat[ft_strlen(pat) - 1] != '*')
	{
		while (files[++j])
			if (!ft_revncmp(files[j], &pat[1]))
				new_files = insert_text(new_files, ft_strdup(files[j]));
	}
	else if (pat[0] != '*' && pat[ft_strlen(pat) - 1] == '*')
	{
		while (files[++j])
			if (!ft_strncmp(files[j], pat, ft_strlen(pat) - 1))
				new_files = insert_text(new_files, ft_strdup(files[j]));
	}
	else if (pat[0] == '*' && pat[ft_strlen(pat) - 1] == '*')
	{
		while (files[++j])
			if (ft_strstrn(files[j], &pat[1], ft_strlen(pat) - 2))
				new_files = insert_text(new_files, ft_strdup(files[j]));
	}
	free_table(files);
	return (new_files);
}

char	**match_astr(char *word, char **files)
{
	char	**pat;
	int		i;

	i = -1;
	pat = NULL;
	pat = extract_pat(word, pat);
	if (!pat)
		return (files);
	while(pat[++i])
	{
		files = filter_files(files, pat[i]);
		if (!files)
			break ;
	}
	return (files);
}

void	construct_cmd(char *word, char token, t_command *final_cmd)
{
	int	j;
	char	**files;

	files = cd_files();
	if (ft_strchr(word, '*'))
	{
		j = -1;
		files = match_astr(word, files);
		while(files && files[++j])
		{
			final_cmd->cmd = insert_text(final_cmd->cmd, files[j]);
			final_cmd->tokens = insert_token(final_cmd->tokens, WORD);
		}
		if (!files)
		{
			final_cmd->cmd = insert_text(final_cmd->cmd, ft_strdup(word));
			final_cmd->tokens = insert_token(final_cmd->tokens, token);
		}
	}
	else
	{
		final_cmd->cmd = insert_text(final_cmd->cmd, ft_strdup(word));
		final_cmd->tokens = insert_token(final_cmd->tokens, token);
	}
}