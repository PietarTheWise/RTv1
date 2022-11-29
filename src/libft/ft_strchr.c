/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:11:06 by pnoutere          #+#    #+#             */
/*   Updated: 2021/11/29 13:17:20 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (s[i])
	{
		if ((char)s[i] == (char)c)
		{
			found = 1;
			break ;
		}
		i++;
	}
	if (c == '\0' || found == 1)
		return ((char *)s + i);
	return (NULL);
}
