/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:28:11 by pnoutere          #+#    #+#             */
/*   Updated: 2022/09/29 16:27:37 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	plane_hit(t_plane plane, const t_ray shadow,
	float shadow_length, t_util utils)
{
	t_vec	p0l0;
	float	denom;
	float	t;

	denom = dot_product(plane.normal, shadow.direction);
	if (denom > 0)
	{
		p0l0 = subtract(plane.center, shadow.origin);
		t = dot_product(p0l0, plane.normal) / denom;
		if (t >= 0.00000)
		{
			if (shadow_length > utils.infinite)
				return (0);
			if (t > shadow_length)
				return (0);
			return (1);
		}
	}
	return (0);
}

float	intersect_plane(t_plane plane, const t_ray ray, float t)
{
	t_vec	p0l0;
	float	denom;

	denom = dot_product(plane.normal, ray.direction);
	if (denom > 0)
	{
		p0l0 = subtract(plane.center, ray.origin);
		t = dot_product(p0l0, plane.normal) / denom;
		if (t >= 0.00001)
			return (t);
	}
	return (10000000000000);
}

void	calculate_light_cone(t_util *utils, int i, t_ray light)
{
	t_vec	v1;
	t_vec	v2;
	float	angle;
	float	distance;

	v1 = vec_normalize(subtract(utils->hit_point, utils->cones[i].top));
	v2 = vec_normalize(utils->cones[i].subtr_top_bot);
	angle = fabs(acos(dot_product(v1, v2)));
	distance = vec_len(subtract(utils->hit_point,
				utils->cones[i].top)) / cos(angle);
	v2 = vec_add(utils->cones[i].top, vec_scale(v2, distance));
	v2 = vec_normalize(subtract(utils->hit_point, v2));
	light.direction = vec_scale(vec_normalize(
				subtract(utils->hit_point, light.origin)), -1.0);
	utils->light_level = dot_product(v2, light.direction);
	if (utils->light_level < 0.0)
		utils->light_level = 0;
}

void	calculate_light_level_plane(t_util *utils,
	t_vec normal, t_ray light, float hit)
{
	utils->hit_point = vec_scale(utils->ray.direction, hit);
	utils->hit_point = vec_add(utils->ray.origin, utils->hit_point);
	light.direction = vec_scale(vec_normalize(
				subtract(utils->hit_point, light.origin)), -1.0);
	utils->light_level_plane = -dot_product(normal, light.direction);
	if (utils->light_level_plane < 0.0)
		utils->light_level_plane = 0;
}

void	check_planes(t_util utils, t_plane *plane, t_ray light, float hit)
{
	calculate_light_level_plane(&utils,
		plane->normal, light, hit);
	plane->light_level = utils.light_level_plane;
	plane->hit = utils.hit;
}
