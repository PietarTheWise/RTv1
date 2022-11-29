/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:06:40 by pnoutere          #+#    #+#             */
/*   Updated: 2021/12/02 13:30:35 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while ((unsigned char)s1[i])
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1);
		i++;
	}
	if ((unsigned char)s1[i] == '\0' && (unsigned char)s2[i] == '\0')
		return (0);
	else if ((unsigned char)s1[i] == '\0')
		return (-1);
	else
		return (1);
}
