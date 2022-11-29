/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_inits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:35:45 by pnoutere          #+#    #+#             */
/*   Updated: 2022/10/04 16:50:00 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	default_cam_and_light(t_util *utils)
{
	if (!utils->camera_found)
	{
		ft_putendl("Camera origin not found, setting to default.");
		utils->ray.origin = vector(0.0, -3.0, 0.0);
	}
	if (!utils->light_found)
	{
		ft_putendl("Light origin not found, setting to default.");
		utils->light.origin = vector(10.0, -10.0, -60.0);
	}
}

void	check_each_line(t_util *utils, char *line)
{
	if (!ft_strncmp(line, "sphere:", 7))
		sphere_assign(line, utils);
	if (!ft_strncmp(line, "cone:", 5))
		cone_assign(line, utils);
	if (!ft_strncmp(line, "cylinder:", 9))
		cylinder_assign(line, utils);
	if (!ft_strncmp(line, "plane:", 6))
		plane_assign(line, utils);
	if (!ft_strncmp(line, "light:", 6))
		light_assign(line, utils);
	if (!ft_strncmp(line, "camera:", 6))
		camera_assign(line, utils);
}

void	assign_object_values(t_util *utils, char *file)
{
	int		fd;
	int		ret;
	int		i;
	char	*line;

	object_amount_util(&ret, &i, &fd, file);
	assign_object_mallocs(utils);
	while (ret)
	{
		ret = get_next_line(fd, &line);
		check_each_line(utils, line);
		if (ret == 0)
			break ;
		free(line);
		i++;
	}
	default_cam_and_light(utils);
}

void	init_objects(int argc, char **argv, t_util *utils)
{
	if (argc != 2)
	{
		ft_putendl("Wrong argument count.");
		exit(1);
	}
	if (!get_object_amount(utils, argv[1]))
		return ;
	assign_object_values(utils, argv[1]);
	utils->infinite = 1000000000000;
}
