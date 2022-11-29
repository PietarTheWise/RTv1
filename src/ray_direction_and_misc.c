/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_direction_and_misc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:01:56 by pnoutere          #+#    #+#             */
/*   Updated: 2022/09/29 16:29:26 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	put_pixel(void *data, int x, int y, int color)
{
	if (x >= 0 && x < 640 && y >= 0 && y < 480)
		*(unsigned int *)(data + (x + (y * 640)) * 4) = color;
}

void	light_plane_correction(t_util *utils)
{
	int	i;
	int	j;

	i = 0;
	while (i < utils->plane_amount)
	{
		j = 0;
		while (j < 3)
		{
			if (utils->planes[i].center.x == utils->light.origin.x)
				utils->light.origin.x += utils->planes[i].normal.x * 0.01;
			if (utils->planes[i].center.y == utils->light.origin.y)
				utils->light.origin.y += utils->planes[i].normal.y * 0.01;
			if (utils->planes[i].center.z == utils->light.origin.z)
				utils->light.origin.z += utils->planes[i].normal.z * 0.01;
			j++;
		}
		i++;
	}
}

t_vec	calculate_direction(t_util utils, float x, float y)
{
	t_vec	ray_direction;

	utils.alpha = 70.0;
	utils.img_ratio = 640.0 / 480.0;
	utils.ndc_x = (x + 0.5) / 640;
	utils.ndc_y = (y + 0.5) / 480;
	utils.pixel_screen_x = (((2 * utils.ndc_x) - 1)
			* utils.img_ratio) * tan(utils.alpha / 2);
	utils.pixel_screen_y = (1 - (2 * utils.ndc_y)) * tan(utils.alpha / 2.0);
	ray_direction.x = utils.pixel_screen_x;
	ray_direction.y = -utils.pixel_screen_y;
	ray_direction.z = 1.2;
	return (vec_normalize(ray_direction));
}

void	assign_object_mallocs_utils(t_util *utils)
{
	if (utils->sphere_amount)
	{
		utils->spheres = (t_sphere *)malloc(
				sizeof(t_sphere) * (utils->sphere_amount));
		if (!utils->spheres)
			exit(0);
	}
	if (utils->plane_amount)
	{
		utils->planes = (t_plane *)malloc(
				sizeof(t_plane) * (utils->plane_amount));
		if (!utils->planes)
			exit(0);
	}
}

void	assign_object_mallocs(t_util *utils)
{
	utils->camera_found = 0;
	utils->light_found = 0;
	assign_object_mallocs_utils(utils);
	if (utils->cone_amount)
	{
		utils->cones = (t_cone *)malloc(
				sizeof(t_cone) * (utils->cone_amount));
		if (!utils->cones)
			exit(0);
	}
	if (utils->cylinder_amount)
	{
		utils->cylinders = (t_cylinder *)malloc(
				sizeof(t_cylinder) * (utils->cylinder_amount));
		if (!utils->cylinders)
			exit(0);
	}
}
