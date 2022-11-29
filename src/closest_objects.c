/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:48:19 by pnoutere          #+#    #+#             */
/*   Updated: 2022/09/29 16:16:27 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	closest_plane(t_plane *planes, t_util *utils)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < utils->plane_amount)
	{
		planes[i].intersect = intersect_plane(planes[i], utils->ray, 0.0);
		planes[i].hit_point = vec_add(utils->ray.origin,
				vec_scale(utils->ray.direction, planes[i].intersect));
		check_planes(*utils, &utils->planes[i],
			utils->light, planes[i].intersect);
		if (i > 0 && planes[j].intersect > planes[i].intersect)
			j = i;
		else if (i == 0)
			j = 0;
		i++;
	}
	return (j);
}

int	closest_sphere(t_util *utils)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < utils->sphere_amount)
	{
		utils->spheres[i].camera_to_center
			= subtract(utils->spheres[i].center, utils->ray.origin);
		sphere_calculation(*utils, &utils->spheres[i]);
		check_spheres(*utils, &utils->spheres[i], utils->light);
		if (utils->spheres[j].t1 > utils->spheres[i].t1)
			j = i;
		else if (i == 0)
			j = 0;
		i++;
	}
	return (j);
}

int	closest_cone(t_util *utils)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < utils->cone_amount)
	{
		cone_calculation(*utils, &utils->cones[i]);
		utils->cones[i].dot_product
			= dot_product(subtract(utils->cones[i].hit_point,
					utils->cones[i].top), utils->cones[i].h);
		utils->hit_point = utils->cones[i].hit_point;
		calculate_light_cone(utils, i, utils->light);
		utils->cones[i].light_level = utils->light_level;
		if (utils->cones[j].t1 > utils->cones[i].t1)
			j = i;
		else if (i == 0)
			j = 0;
		i++;
	}
	return (j);
}

int	closest_cylinder(t_util *utils)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < utils->cylinder_amount)
	{
		cylinder_calculation(*utils, &utils->cylinders[i]);
		utils->hit_point = utils->cylinders[i].hit_point;
		calculate_light_cylinder(utils,
			utils->light, utils->cylinders[i]);
		utils->cylinders[i].light_level = utils->light_level;
		utils->cylinders[i].dot_product
			= dot_product(subtract(utils->cylinders[i].hit_point,
					utils->cylinders[i].top), utils->cylinders[i].h);
		if (utils->cylinders[j].t1 >= utils->cylinders[i].t1)
			j = i;
		else if (i == 0)
			j = 0;
		i++;
	}
	return (j);
}
