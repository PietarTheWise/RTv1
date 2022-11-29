/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:20:13 by pnoutere          #+#    #+#             */
/*   Updated: 2021/12/02 16:15:17 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;
	size_t			dst_len;
	size_t			src_len;

	i = 0;
	j = 0;
	i = ft_strlen((char *)dst);
	src_len = ft_strlen((char *)src);
	dst_len = i;
	if (dstsize < dst_len)
		return (src_len + dstsize);
	while (src[j] && i < dstsize - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	if (dstsize < dst_len)
		return (src_len + dstsize);
	else
		return (dst_len + src_len);
}
