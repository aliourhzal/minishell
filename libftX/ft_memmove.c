/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elix <elix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:09:18 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/09/14 12:04:36 by elix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s_ptr;
	char	*d_ptr;

	if (!src && !dst)
		return (NULL);
	s_ptr = (char *)src;
	d_ptr = (char *)dst;
	if (s_ptr < d_ptr)
	{
		while (len > 0)
		{
			len--;
			d_ptr[len] = s_ptr[len];
		}
	}
	else
		ft_memcpy(d_ptr, s_ptr, len);
	return (dst);
}
