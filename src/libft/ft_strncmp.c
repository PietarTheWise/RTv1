/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:58:15 by pnoutere          #+#    #+#             */
/*   Updated: 2021/12/02 17:10:35 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*src1;
	unsigned char	*src2;
	size_t			i;

	src1 = (unsigned char *)s1;
	src2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (src1[i] && src2[i] && n - 1 > i)
	{
		if (src1[i] > src2[i])
			return (1);
		if (src1[i] < src2[i])
			return (-1);
		i++;
	}
	if (src1[i] == src2[i])
		return (0);
	else if (src1[i] > src2[i])
		return (1);
	else
		return (-1);
}
