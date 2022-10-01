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

int ft_strstrn(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return (1);
	while (haystack[i] != '\0')
	{
		j = 0;
		while (needle[j] == haystack[i + j] && j < len)
		{
			if (needle[j + 1] == '\0')
				return (1);
			j++;
		}
		if (j == len)
			return (1);
		i++;
	}
	return (0);
}