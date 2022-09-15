/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:02:24 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/01/03 11:18:49 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	fucking_conversion(va_list args, char c)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (c == 'p')
		return (ft_putadd(va_arg(args, void *)));
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (c == 'u')
		return (ft_putnbr(va_arg(args, unsigned int)));
	if (c == 'x')
		return (ft_puthex(va_arg(args, unsigned int), 'x'));
	if (c == 'X')
		return (ft_puthex(va_arg(args, unsigned int), 'X'));
	if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *form, ...)
{
	static int	count;
	va_list		args;
	int			i;

	va_start(args, form);
	i = 0;
	count = 0;
	while (form[i])
	{
		if (form[i] != '%')
			count += ft_putchar(form[i]);
		else
		{
			count += (fucking_conversion(args, form[i + 1]));
			i++;
		}
		i++;
	}
	return (count);
}
