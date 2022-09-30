#include "minishell.h"

char	**cd_files(void)
{
	DIR				*dir;
	struct dirent	*d_f;
	char	**files;

	files = 0;
	dir = opendir(".");
	if (dir)
	{
		d_f = readdir(dir);
		while (d_f)
		{
			if (d_f->d_name[0] != '.')
				files = add_line(files, d_f->d_name);
			d_f = readdir(dir);
		}
		closedir(dir);
	}
	return (files);
}

char	**extract_pat(char *word, char **pat)
{
	int	i;
	int	j;

	i = 0;
	if (word[0] != '*')
	{
		while (word[i] != '*')
			i++;
		pat = add_line(pat, dup_till_end(word, word[i + 1]));
	}
	while (word[i])
	{
		j = ++i;
		while (word[j] && word[j] != '*')
			j++;
		if (!word[j])
			break ;
		pat = add_line(pat, ft_joinstr(ft_strdup("*"), dup_till_end(&word[i], word[j + 1])));
		i = j;
	}
	if (word[i - 1] == '*')
		pat = add_line(pat, dup_till_end(&word[i - 1], '\0'));
	return (pat);
}

char	**match_astr(char *word, char **files)
{
	char	**pat;
	char	**new_files;
	int		i;
	int		j;

	i = -1;
	pat = NULL;
	pat = extract_pat(word, pat);
	new_files = NULL;
	if (!ft_strcmp(word, "*"))
		return (files);
	while(pat[++i])
	{
		j = -1;
		if (pat[i][0] == '*' && pat[i][ft_strlen(pat[i]) - 1] != '*')
		{
			while (files[++j])
				if (!ft_revncmp(files[j], &pat[i][1]))
					new_files = add_line(new_files, files[j]);
		}
		else if (pat[i][0] != '*' && pat[i][ft_strlen(pat[i]) - 1] == '*')
		{
			while (files[++j])
				if (!ft_strncmp(files[j], pat[i], ft_strlen(pat[i]) - 1))
					new_files = add_line(new_files, files[j]);
		}
		else if (pat[i][0] == '*' && pat[i][ft_strlen(pat[i]) - 1] == '*')
		{
			while (files[++j])
				if (!ft_strnstr(files[j], &pat[i][1], ft_strlen(pat[i]) - 1))
					new_files = add_line(new_files, files[j]);
		}
	}
	int	x = -1;
	while (new_files[++x])
		printf("file: %s\n", new_files[x]);
	return (new_files);
}

void patterns(char **words, char *tokens)
{
	//t_command *final_cmd;
	int	i;
	char	**files;
    (void)tokens;
	i = -1;
	//final_cmd = malloc(sizeof(t_command));
	files = cd_files();
	while (words[++i])
	{	
		if (ft_strchr(words[i], '*'))
		{
			files = match_astr(words[i], files);
		}
	}	
}

/*files = */

void	wildcard_expansion(t_minishell *main)
{
	int	i;
	int	j;

	i = -1;
	
	while (++i < main->cmds_count)
	{
		j = -1;
		while(main->full_line[i].cmd[++j])
		{
			if (main->full_line[i].tokens[j] != SPACES
				&& ft_strchr(main->full_line[i].cmd[j], '*'))
				patterns(main->full_line[i].cmd, main->full_line[i].tokens);
		}
	}
}
