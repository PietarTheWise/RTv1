/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objects_and_draw.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:06:08 by pnoutere          #+#    #+#             */
/*   Updated: 2022/10/04 15:06:14 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	draw_plane(void *data, t_util *utils)
{
	if (utils->planes[utils->closest_plane].intersect > 0.0
		&& utils->planes[utils->closest_plane].intersect < 9999999827968.000000)
	{
		put_pixel(data, utils->x, utils->y,
			level_color(utils->planes[utils->closest_plane].color,
				utils->planes[utils->closest_plane].light_level));
		utils->shadow_hit_point
			= utils->planes[utils->closest_plane].hit_point;
		check_for_shadows(data, *utils, PLANE);
	}
}

void	draw_sphere(void *data, t_util *utils)
{
	if (utils->spheres[utils->closest_sphere].discr > 0)
	{
		put_pixel(data, utils->x, utils->y, level_color(
				utils->spheres[utils->closest_sphere].color,
				utils->spheres[utils->closest_sphere].light_level));
		utils->shadow_hit_point
			= utils->spheres[utils->closest_sphere].hit_point;
		check_for_shadows(data, *utils, SPHERE);
	}
}

void	draw_cone(void *data, t_util *utils)
{
	t_vec	subt;
	float	ans;
	float	length;

	subt = subtract(utils->cones[utils->closest_cone].hit_point,
			utils->cones[utils->closest_cone].top);
	ans = dot_product(subt, utils->cones[utils->closest_cone].h);
	length = vec_len(utils->cones[utils->closest_cone].subtr_top_bot);
	utils->shadow_hit_point = utils->cones[utils->closest_cone].hit_point;
	if (ans > 0 && ans <= length)
		put_pixel(data, utils->x, utils->y,
			level_color(utils->cones[utils->closest_cone].color,
				utils->cones[utils->closest_cone].light_level));
	else if (ans > length)
		put_pixel(data, utils->x, utils->y,
			level_color(utils->cones[utils->closest_cone].color,
				utils->cones[utils->closest_cone].light_level));
	else if (ans < 0)
		put_pixel(data, utils->x, utils->y,
			level_color(utils->cones[utils->closest_cone].color,
				utils->cones[utils->closest_cone].light_level));
	check_for_shadows(data, *utils, CONE);
}

void	draw_cylinder(void *data, t_util *utils)
{
	if (utils->cylinders[utils->closest_cylinder].discr > 0)
	{
		put_pixel(data, utils->x, utils->y, level_color(
				utils->cylinders[utils->closest_cylinder].color,
				utils->cylinders[utils->closest_cylinder].light_level));
		utils->shadow_hit_point
			= utils->cylinders[utils->closest_cylinder].hit_point;
		check_for_shadows(data, *utils, CYLINDER);
	}
}

void	check_objects_and_draw(void *data, t_util *utils)
{
	look_for_closest(utils);
	if (utils->closest == PLANE && utils->plane_amount)
		draw_plane(data, utils);
	else if (utils->closest == SPHERE && utils->sphere_amount)
		draw_sphere(data, utils);
	else if (utils->closest == CONE && utils->cone_amount)
		draw_cone(data, utils);
	else if (utils->closest == CYLINDER && utils->cylinder_amount)
		draw_cylinder(data, utils);
}
