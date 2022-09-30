#include "minishell.h"

int	ft_revncmp(char *s, char *to_find)
{
    int i;
    int j;

    i = ft_strlen(s) - 1;
    j = ft_strlen(to_find) - 1;
    if (j > i)
    {
        return (1);
    }
	while (i > 0 && j > 0 && s[i] == to_find[j])
	{
		i--;
        j--;
	}
    if (s[i] == to_find[j])
    {
        return (0);
    }
	return (s[i] - to_find[j]);
}