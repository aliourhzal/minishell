/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 08:21:06 by ael-hadd          #+#    #+#             */
/*   Updated: 2021/11/13 14:44:27 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*d_ptr;
	char	*s_ptr;

	i = 0;
	d_ptr = (char *)dst;
	s_ptr = (char *)src;
	if (!d_ptr && !s_ptr)
		return (NULL);
	while (i < n)
	{
		d_ptr[i] = s_ptr[i];
		i++;
	}
	return (dst);
}
