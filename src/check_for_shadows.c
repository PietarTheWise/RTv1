/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_shadows.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:06:08 by pnoutere          #+#    #+#             */
/*   Updated: 2022/10/04 15:19:17 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	sphere_shadow(void *data, t_util utils, int flag, int shadow_color)
{
	int	i;

	i = 0;
	while (i < utils.sphere_amount)
	{
		if (flag == SPHERE)
		{
			if (sphere_hit(utils, utils.spheres[i])
				&& i != utils.closest_sphere)
				put_pixel(data, utils.x, utils.y, shadow_color);
		}
		else if (sphere_hit(utils, utils.spheres[i]))
			put_pixel(data, utils.x, utils.y, shadow_color);
		i++;
	}
}

void	cone_shadow(void *data, t_util utils, int flag, int shadow_color)
{
	int	i;

	i = 0;
	while (i < utils.cone_amount)
	{
		if (flag == CONE)
		{
			if (cone_hits(utils, utils.cones[i]) && utils.closest_cone != i)
				put_pixel(data, utils.x, utils.y, shadow_color);
		}
		else if (cone_hits(utils, utils.cones[i]))
			put_pixel(data, utils.x, utils.y, shadow_color);
		i++;
	}
}

void	cylinder_shadow(void *data, t_util utils, int flag, int shadow_color)
{
	int	i;

	i = 0;
	while (i < utils.cylinder_amount)
	{
		if (flag == CYLINDER)
		{
			if (cylinder_hit(utils, utils.cylinders[i])
				&& utils.closest_cylinder != i)
				put_pixel(data, utils.x, utils.y, shadow_color);
		}
		else if (cylinder_hit(utils, utils.cylinders[i]))
			put_pixel(data, utils.x, utils.y, shadow_color);
		i++;
	}
}

void	plane_shadow(void *data, t_util utils, int flag, int shadow_color)
{
	int	i;

	i = 0;
	while (i < utils.plane_amount)
	{
		if (flag == PLANE)
		{
			if (plane_hit(utils.planes[i], utils.shadow, utils.shadow_length,
					utils) && utils.closest_plane != i)
				put_pixel(data, utils.x, utils.y, shadow_color);
		}
		else if (plane_hit(utils.planes[i], utils.shadow,
				utils.shadow_length, utils))
			put_pixel(data, utils.x, utils.y, shadow_color);
		i++;
	}
}

void	check_for_shadows(void *data, t_util utils, int flag)
{
	int	shadow_color;

	shadow_color = 0;
	utils.shadow.origin = utils.shadow_hit_point;
	utils.shadow.direction = vec_normalize(
			subtract(utils.light.origin, utils.shadow.origin));
	utils.shadow_length = vec_len(subtract(
				utils.shadow.origin, utils.light.origin));
	sphere_shadow(data, utils, flag, shadow_color);
	cone_shadow(data, utils, flag, shadow_color);
	cylinder_shadow(data, utils, flag, shadow_color);
	plane_shadow(data, utils, flag, shadow_color);
}
