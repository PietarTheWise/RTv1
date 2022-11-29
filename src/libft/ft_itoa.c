/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:12:30 by pnoutere          #+#    #+#             */
/*   Updated: 2021/11/29 13:18:00 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_loop(char *str, long k, long n)
{
	int	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		str[i] = '-';
		n = n * (-1);
		i++;
	}
	while (k > 0)
	{
		str[i] = (((n - (n % k)) / k) % 10) + 48;
		k = k / 10;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int nb)
{
	int		i;
	long	k;
	long	temp_nb;
	long	n;
	char	*str;

	n = nb;
	i = 0;
	k = 1;
	if (n < 0)
		temp_nb = n * (-1);
	else
		temp_nb = n;
	while (temp_nb >= 10)
	{
		temp_nb = temp_nb / 10;
		k = k * 10;
		i++;
	}
	if (n < 0)
		str = (char *)malloc(sizeof(char) * (i + 3));
	else
		str = (char *)malloc(sizeof(char) * (i + 2));
	return (ft_loop(str, k, n));
}
