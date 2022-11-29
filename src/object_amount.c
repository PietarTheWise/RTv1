/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_amount.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:44:18 by pnoutere          #+#    #+#             */
/*   Updated: 2022/10/04 16:50:46 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	object_amount_util(int *ret, int *i, int *fd, char *file)
{
	*ret = 1;
	*i = 0;
	*fd = open(file, O_RDWR);
	if (*fd == -1)
	{
		perror("Error");
		exit(1);
	}
}

int	get_object_amount(t_util *utils, char *file)
{
	int		fd;
	int		ret;
	char	*line;

	object_amount_util(&ret, &utils->x, &fd, file);
	while (ret)
	{
		ret = get_next_line(fd, &line);
		if (ret != 0 && ret > -1)
		{
			if (!ft_strncmp(line, "sphere:", 7))
				utils->sphere_amount += 1;
			if (!ft_strncmp(line, "cone:", 5))
				utils->cone_amount += 1;
			if (!ft_strncmp(line, "cylinder:", 9))
				utils->cylinder_amount += 1;
			if (!ft_strncmp(line, "plane:", 6))
				utils->plane_amount += 1;
		}
		if (ret == 0)
			return (utils->x);
		free(line);
		utils->x += 1;
	}
	return (0);
}
