/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:28:11 by pnoutere          #+#    #+#             */
/*   Updated: 2022/09/29 16:00:53 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	calculate_light_cylinder(t_util *utils,
	t_ray light, t_cylinder cylinder)
{
	t_vec	normal;
	t_vec	point_in_axis;
	float	distance;

	distance = dot_product(subtract(utils->hit_point,
				cylinder.bottom), cylinder.h);
	point_in_axis = vec_add(cylinder.bottom, vec_scale(cylinder.h, distance));
	normal = vec_normalize(subtract(utils->hit_point, point_in_axis));
	light.direction = vec_scale(vec_normalize(
				subtract(utils->hit_point, light.origin)), -1.0);
	utils->light_level = dot_product(normal, light.direction);
	if (utils->light_level < 0.0)
		utils->light_level = 0;
}

void	initiate_cylinder_vals(t_util *utils, t_cylinder *cyl)
{
	utils->w = subtract(utils->ray.origin, cyl->bottom);
	cyl->h = vec_normalize(subtract(cyl->top, cyl->bottom));
	rotation_xyz(&cyl->h, cyl->rotation.x, cyl->rotation.y, cyl->rotation.z);
	utils->a = dot_product(utils->ray.direction, utils->ray.direction)
		- pow(dot_product(utils->ray.direction, cyl->h), 2);
	utils->b = 2 * (dot_product(utils->ray.direction, utils->w)
			- (dot_product(utils->ray.direction, cyl->h)
				* dot_product(utils->w, cyl->h)));
	utils->c = dot_product(utils->w, utils->w)
		- pow(dot_product(utils->w, cyl->h), 2) - pow(cyl->radius, 2);
	cyl->discr = ((utils->b * utils->b) - (4 * utils->a * utils->c));
	cyl->t0 = utils->infinite;
	cyl->t1 = utils->infinite;
}

void	cylinder_calculation(t_util utils, t_cylinder *cyl)
{
	initiate_cylinder_vals(&utils, cyl);
	if (cyl->discr < 0)
		return ;
	else if (cyl->discr == 0)
	{
		if (fabs(dot_product(utils.ray.direction, cyl->h)) != 1.f)
			cyl->t0 = -0.5 * utils.b / utils.a;
	}
	else
	{
		if (utils.b > 0)
			utils.q = -0.5 * (utils.b + sqrt(cyl->discr));
		else
			utils.q = -0.5 * (utils.b - sqrt(cyl->discr));
		cyl->t0 = utils.q / utils.a;
		cyl->t1 = utils.c / utils.q;
		if (cyl->t0 < 0 && cyl->t1 < 0)
		{
			cyl->t0 = utils.infinite;
			cyl->t1 = utils.infinite;
		}
	}
	cyl->hit_point = vec_add(utils.ray.origin,
			vec_scale(utils.ray.direction, cyl->t1));
}
