/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_read_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:51:14 by pnoutere          #+#    #+#             */
/*   Updated: 2022/09/30 15:07:50 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	check_float_vals(char *predot, char *postdot)
{
	int	i;

	i = 0;
	if (predot[i] == '-')
		i++;
	while (predot[i])
	{
		if (!isdigit(predot[i]))
		{
			ft_putendl("Forbidden characters amidst data");
			exit (1);
		}
		i++;
	}
	i = 0;
	while (postdot[i])
	{
		if (!isdigit(postdot[i]))
		{
			ft_putendl("Forbidden characters amidst data");
			exit (1);
		}
		i++;
	}
}

void	check_char_utils(char **coords)
{
	int		j;

	j = 0;
	while (coords[j])
		j++;
	if (j != 2)
	{
		ft_putendl("float problem");
		exit(1);
	}
	check_float_vals(coords[0], coords[1]);
	if (ft_strlen(coords[1]) > 10)
	{
		ft_putendl("floating point precision too high");
		exit (1);
	}
}

void	check_char_vector(char **xyz)
{
	char	**coords;
	int		i;

	i = 0;
	while (xyz[i])
	{
		coords = ft_strsplit(xyz[i], '.');
		if (!coords)
			exit (1);
		check_char_utils(coords);
		ft_free_array(coords);
		i++;
	}
	if (i != 3)
	{
		ft_putendl("Not enough numbers for a single vector");
		exit (1);
	}
}

void	check_given_values(char **values, int needed_amount)
{
	int	i;

	i = 0;
	while (values[i])
		i++;
	if (i != needed_amount)
	{
		ft_putendl("Check your data\n");
		exit (1);
	}
}

void	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isalpha(line[i]))
		{
			ft_putendl("Alphabets found in the data");
			exit (1);
		}
		if (!ft_isdigit(line[i]) && (line[i] != ','
				&& line[i] != '.' && line[i] != ' ' && line[i] != '-'))
		{
			ft_putendl("Forbidden characters found in the data");
			exit (1);
		}
		i++;
	}
}
