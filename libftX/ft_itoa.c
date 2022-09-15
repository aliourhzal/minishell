/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:53:20 by ael-hadd          #+#    #+#             */
/*   Updated: 2021/11/12 21:39:46 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static	size_t	n_len(int n)
{
	int				len;
	unsigned int	nb;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	len = 1;
	while (nb > 9)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			len;
	unsigned int	tmp;

	len = n_len(n);
	tmp = n;
	if (n < 0)
	{
		tmp = -n;
		len += 1;
	}
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		str[len - 1] = tmp % 10 + '0';
		tmp /= 10;
		len--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
