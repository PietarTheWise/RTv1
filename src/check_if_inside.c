/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_inside.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:06:08 by pnoutere          #+#    #+#             */
/*   Updated: 2022/09/29 16:24:35 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	spheres(t_util utils)
{
	int	i;

	i = 0;
	if (utils.sphere_amount)
	{
		while (i < utils.sphere_amount)
		{
			if (vec_len(subtract(utils.spheres[i].center, utils.ray.origin))
				< utils.spheres[i].radius)
				return (0);
			i++;
		}
	}
	return (1);
}

static int	cones(t_util utils)
{
	int		i;
	t_vec	cone_direction;
	float	cone_angle;
	float	angle;

	i = 0;
	if (utils.cone_amount)
	{
		while (i < utils.cone_amount)
		{
			cone_direction = vec_normalize(subtract(utils.cones[i].bottom,
						utils.cones[i].top));
			cone_angle = utils.cones[i].radius / vec_len(subtract(
						utils.cones[i].top, utils.cones[i].bottom));
			angle = dot_product(cone_direction, vec_normalize(
						subtract(utils.cones[i].top, utils.ray.origin)));
			if (acos(angle) > M_PI - atan(cone_angle))
				return (0);
			else if (acos(angle) < atan(cone_angle))
				return (0);
			i++;
		}
	}
	return (1);
}

static int	cylinders(t_util utils)
{
	int		i;
	float	distance;
	float	len;
	t_vec	cylinder_direction;
	t_vec	point_in_axis;

	i = 0;
	if (utils.cylinder_amount)
	{
		while (i < utils.cylinder_amount)
		{
			cylinder_direction = vec_normalize(subtract(
						utils.cylinders[i].bottom, utils.cylinders[i].top));
			distance = dot_product(subtract(utils.ray.origin,
						utils.cylinders[i].bottom), cylinder_direction);
			point_in_axis = vec_add(utils.cylinders[i].bottom,
					vec_scale(cylinder_direction, distance));
			len = vec_len(subtract(utils.ray.origin, point_in_axis));
			if (len < utils.cylinders[i].radius)
				return (0);
			i++;
		}
	}
	return (1);
}

int	check_if_inside(t_util utils)
{
	if (!spheres(utils) || !cylinders(utils)
		|| !cones(utils) || !cylinders(utils))
	{
		ft_putendl("Inside a solid object");
		return (0);
	}
	return (1);
}
