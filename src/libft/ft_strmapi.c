/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:14:43 by pnoutere          #+#    #+#             */
/*   Updated: 2021/11/15 13:14:43 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new_str;

	i = 0;
	new_str = NULL;
	if (s && f)
	{
		new_str = (char *)malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
		if (!new_str)
			return (NULL);
		while (s[i])
		{
			new_str[i] = f(i, s[i]);
			i++;
		}
		new_str[i] = '\0';
	}
	return (new_str);
}
