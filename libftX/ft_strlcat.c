/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:17:13 by ael-hadd          #+#    #+#             */
/*   Updated: 2021/11/13 15:33:26 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	d_len;
	size_t	s_len;

	i = 0;
	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	j = d_len;
	if (d_len > dstsize)
		return (s_len + dstsize);
	else if (d_len < dstsize)
	{
		while (j < dstsize - 1 && src[i] != '\0')
			dst[j++] = src[i++];
		dst[j] = '\0';
	}
	return (s_len + d_len);
}
