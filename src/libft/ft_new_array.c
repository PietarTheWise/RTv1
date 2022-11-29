/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kceder <kceder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:23:09 by kceder            #+#    #+#             */
/*   Updated: 2022/02/07 17:30:54 by kceder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_new_array(char **array, int len)
{
	int	i;

	i = 0;
	array = (char **)malloc(sizeof(char *) * len);
	while (i < len)
	{
		array[i] = NULL;
		i++;
	}
	return (array);
}
