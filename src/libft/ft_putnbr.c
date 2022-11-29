/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:59:55 by pnoutere          #+#    #+#             */
/*   Updated: 2021/11/29 13:17:26 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nb)
{
	long int	new;
	long int	n;

	n = nb;
	if (n < 0)
	{
		ft_putchar('-');
		n = n * (-1);
	}
	new = n % 10;
	if (n > 9)
	{
		n = (n - new) / 10;
		ft_putnbr(n);
	}
	ft_putchar(new + 48);
	return ;
}
