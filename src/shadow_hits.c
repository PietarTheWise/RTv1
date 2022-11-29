/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_hits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:58:20 by pnoutere          #+#    #+#             */
/*   Updated: 2022/10/04 16:06:44 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	sphere_hit_util(t_util *utils, t_sphere *sphere)
{
	utils->w = subtract(utils->shadow.origin, sphere->center);
	utils->a = dot_product(utils->shadow.direction, utils->shadow.direction);
	utils->b = 2 * dot_product(utils->shadow.direction, utils->w);
	utils->c = dot_product(utils->w, utils->w) - pow(sphere->radius, 2);
	sphere->discr = ((utils->b * utils->b) - (4 * utils->a * utils->c));
}

int	sphere_hit(t_util utils, t_sphere sphere)
{
	sphere_hit_util(&utils, &sphere);
	if (sphere.discr < 0)
	{
		sphere.t0 = utils.infinite;
		sphere.t1 = utils.infinite;
		return (0);
	}
	else if (sphere.discr == 0)
		return (0);
	else
	{
		if (utils.b > 0)
			utils.q = -0.5 * (utils.b + sqrt(sphere.discr));
		else
			utils.q = -0.5 * (utils.b - sqrt(sphere.discr));
		sphere.t0 = utils.q / utils.a;
		sphere.t1 = utils.c / utils.q;
		if (sphere.t0 > utils.infinite || sphere.t1 > utils.infinite)
			return (0);
		if (sphere.t0 > utils.shadow_length && sphere.t1 > utils.shadow_length)
			return (0);
		if (sphere.t0 < 0 && sphere.t1 < 0)
			return (0);
		return (sphere.t0 > 0);
	}
}

void	cone_hits_utils(t_util *utils, t_cone *cone)
{
	float	len;

	utils->w = subtract(utils->shadow.origin, cone->top);
	cone->subtr_top_bot = subtract(cone->bottom, cone->top);
	len = vec_len(cone->subtr_top_bot);
	rotation_xyz(&cone->subtr_top_bot, cone->rotation.x,
		cone->rotation.y, cone->rotation.z);
	cone->subtr_top_bot = vec_scale(cone->subtr_top_bot, len);
	cone->h = vec_normalize(cone->subtr_top_bot);
	cone->m = pow(cone->radius, 2) / pow(vec_len(cone->subtr_top_bot), 2);
	utils->a = dot_product(utils->shadow.direction, utils->shadow.direction)
		- (cone->m * pow(dot_product(utils->shadow.direction, cone->h), 2))
		- pow(dot_product(utils->shadow.direction, cone->h), 2);
	utils->b = 2 * (dot_product(utils->shadow.direction, utils->w)
			- (cone->m * (dot_product(utils->shadow.direction, cone->h)
					* dot_product(utils->w, cone->h)))
			- (dot_product(utils->shadow.direction, cone->h)
				* dot_product(utils->w, cone->h)));
	utils->c = dot_product(utils->w, utils->w)
		- (cone->m * pow(dot_product(utils->w, cone->h), 2))
		- pow(dot_product(utils->w, cone->h), 2);
	cone->discr = ((utils->b * utils->b) - (4 * utils->a * utils->c));
	cone->t0 = utils->infinite;
	cone->t1 = utils->infinite;
}

int	cone_hits(t_util utils, t_cone cone)
{
	cone_hits_utils(&utils, &cone);
	if (cone.discr < 0)
		return (0);
	else if (cone.discr == 0)
		return (0);
	else
	{
		if (utils.b > 0)
			utils.q = -0.5 * (utils.b + sqrt(cone.discr));
		else
			utils.q = -0.5 * (utils.b - sqrt(cone.discr));
		cone.t0 = utils.q / utils.a;
		cone.t1 = utils.c / utils.q;
		if (cone.t0 < 0 && cone.t1 < 0)
			return (0);
		if (cone.t1 > utils.shadow_length || cone.t0 > utils.shadow_length)
			return (0);
		return (cone.t0 > 0);
	}
}
