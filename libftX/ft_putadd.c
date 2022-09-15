/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:42:38 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/01/03 11:17:58 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static	int	get_into_hex(unsigned long long n, char x)
{
	int	count;

	count = 0;
	if (n >= 16)
	{
		count += get_into_hex(n / 16, x);
		count += get_into_hex(n % 16, x);
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

int	ft_putadd(void *ptr)
{
	int	count;

	count = 0;
	count += write(1, "0x", 2);
	count += get_into_hex((unsigned long long)ptr, 'x');
	return (count);
}
