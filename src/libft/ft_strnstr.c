/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:05:24 by pnoutere          #+#    #+#             */
/*   Updated: 2021/11/29 13:16:38 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		j;
	size_t		length;
	const char	*temp;

	if (needle[0] == '\0')
		return ((char *)haystack);
	length = ft_strlen((char *)needle);
	j = 0;
	temp = haystack;
	while (j < len && haystack[j])
	{
		if (needle[0] == haystack[j] && !ft_strncmp((char *)&needle[0],
				(char *)&haystack[j], length) && j + length <= len)
		{
			return ((char *)(temp + j));
		}
		j++;
	}
	return (NULL);
}
