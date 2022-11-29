/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_unit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:09:08 by pnoutere          #+#    #+#             */
/*   Updated: 2022/09/28 16:01:59 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	translation_unit_spheres(t_util *utils)
{
	int	i;

	i = 0;
	if (utils->sphere_amount)
	{
		while (i < utils->sphere_amount)
		{
			utils->spheres[i].center = vec_add(
					utils->spheres[i].center, utils->spheres[i].translation);
			i++;
		}
	}
}

void	translation_unit_planes(t_util *utils)
{
	int	i;

	i = 0;
	if (utils->plane_amount)
	{
		while (i < utils->plane_amount)
		{
			utils->planes[i].center = vec_add(
					utils->planes[i].center, utils->planes[i].translation);
			i++;
		}
	}
}

void	translation_unit_cones(t_util *utils)
{
	int	i;

	i = 0;
	if (utils->cone_amount)
	{
		while (i < utils->cone_amount)
		{
			utils->cones[i].bottom = vec_add(
					utils->cones[i].bottom, utils->cones[i].translation);
			utils->cones[i].top = vec_add(
					utils->cones[i].top, utils->cones[i].translation);
			i++;
		}
	}
}

void	translation_unit_cylinders(t_util *utils)
{
	int	i;

	i = 0;
	if (utils->cylinder_amount)
	{
		while (i < utils->cylinder_amount)
		{
			utils->cylinders[i].bottom = vec_add(
					utils->cylinders[i].bottom,
					utils->cylinders[i].translation);
			utils->cylinders[i].top = vec_add(
					utils->cylinders[i].top, utils->cylinders[i].translation);
			i++;
		}
	}
}

void	translation_unit(t_util *utils)
{
	translation_unit_cylinders(utils);
	translation_unit_cones(utils);
	translation_unit_planes(utils);
	translation_unit_spheres(utils);
}
