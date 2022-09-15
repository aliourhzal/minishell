/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:01:16 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/01/03 11:17:53 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_puthex(unsigned int n, char x)
{
	int	count;

	count = 0;
	if (n >= 16)
	{
		count += ft_puthex(n / 16, x);
		count += ft_puthex(n % 16, x);
	}
	else
	{
		if (n < 10)
			count += ft_putchar(n + 48);
		else
		{
			if (x == 'x')
				count += ft_putchar(n - 10 + 'a');
			else if (x == 'X')
				count += ft_putchar(n - 10 + 'A');
		}
	}
	return (count);
}
