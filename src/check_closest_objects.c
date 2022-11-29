/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closest_objects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:46:24 by pnoutere          #+#    #+#             */
/*   Updated: 2022/09/30 15:09:42 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	check_closest_plane(t_util *utils)
{
	float	closest;

	if (utils->plane_amount)
	{
		utils->closest_plane = closest_plane(utils->planes, utils);
		closest = utils->planes[utils->closest_plane].intersect;
	}
	else
	{
		closest = utils->infinite;
	}
	return (closest);
}

float	check_closest_sphere(t_util *utils)
{
	float	closest;

	if (utils->sphere_amount)
	{
		utils->closest_sphere = closest_sphere(utils);
		closest = utils->spheres[utils->closest_sphere].t1;
	}
	else
		closest = utils->infinite;
	return (closest);
}

float	check_closest_cone(t_util *utils)
{
	float	closest;

	if (utils->cone_amount)
	{
		utils->closest_cone = closest_cone(utils);
		closest = utils->cones[utils->closest_cone].t1;
	}
	else
		closest = utils->infinite;
	return (closest);
}

float	check_closest_cylinder(t_util *utils)
{
	float	closest;

	if (utils->cylinder_amount)
	{
		utils->closest_cylinder = closest_cylinder(utils);
		closest = utils->cylinders[utils->closest_cylinder].t1;
	}
	else
		closest = utils->infinite;
	return (closest);
}

void	look_for_closest(t_util *utils)
{
	float	closests[4];
	int		i;
	int		k;

	closests[0] = check_closest_plane(utils);
	closests[1] = check_closest_sphere(utils);
	closests[2] = check_closest_cone(utils);
	closests[3] = check_closest_cylinder(utils);
	i = 0;
	k = 0;
	while (i < 4)
	{
		if (closests[i] < closests[0])
		{
			closests[0] = closests[i];
			k = i;
		}
		i++;
	}
	utils->closest = k;
}
