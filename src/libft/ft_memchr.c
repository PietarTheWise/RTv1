/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:01:20 by pnoutere          #+#    #+#             */
/*   Updated: 2021/11/29 13:17:45 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	ch;
	unsigned char	*arr;
	size_t			i;

	ch = (unsigned char)c;
	arr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*arr == ch)
			return (arr);
		arr++;
		i++;
	}
	return (NULL);
}
