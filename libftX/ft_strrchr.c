/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:29:05 by ael-hadd          #+#    #+#             */
/*   Updated: 2021/11/15 13:47:38 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;
	int		j;
	int		i;

	temp = NULL;
	i = ft_strlen(s);
	j = 0;
	while (j <= i)
	{
		if (s[j] == (unsigned char) c)
			temp = (char *)&s[j];
		j++;
	}
	return (temp);
}
