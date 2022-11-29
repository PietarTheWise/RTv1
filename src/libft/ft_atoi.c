/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:00:13 by pnoutere          #+#    #+#             */
/*   Updated: 2021/12/02 17:29:27 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	val;
	int	start;
	int	is_negative;

	val = 0;
	is_negative = 1;
	start = 0;
	while (str[start] == ' ' || str[start] == '\n' || str[start] == '\t'
		|| str[start] == '\v' || str[start] == '\r' || str[start] == '\f')
		start++;
	if (str[start] == '-' || str[start] == '+')
	{
		if (str[start] == '-')
			is_negative = -1;
		start++;
	}
	while (str[start] >= '0' && str[start] <= '9')
	{
		val = (val * 10) + (str[start] - 48);
		start++;
	}
	return (val * is_negative);
}
