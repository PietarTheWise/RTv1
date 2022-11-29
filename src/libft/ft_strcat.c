/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:20:13 by pnoutere          #+#    #+#             */
/*   Updated: 2021/11/29 13:17:22 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int	i;
	int	s1_length;

	s1_length = 0;
	while (s1[s1_length])
		s1_length++;
	i = 0;
	while (s2[i] != '\0')
	{
		s1[s1_length + i] = s2[i];
		i++;
	}
	s1[s1_length + i] = '\0';
	return (s1);
}
