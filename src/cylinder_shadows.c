/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_shadows.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:27:00 by pnoutere          #+#    #+#             */
/*   Updated: 2022/10/04 16:00:13 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	cylinder_hit_utils(t_util *utils, t_cylinder *cyl)
{
	utils->w = subtract(utils->shadow.origin, cyl->bottom);
	cyl->h = vec_normalize(subtract(cyl->bottom, cyl->top));
	rotation_xyz(&cyl->h, cyl->rotation.x, cyl->rotation.y, cyl->rotation.z);
	utils->a = dot_product(utils->shadow.direction, utils->shadow.direction)
		- pow(dot_product(utils->shadow.direction, cyl->h), 2);
	utils->b = 2 * (dot_product(utils->shadow.direction, utils->w)
			- (dot_product(utils->shadow.direction, cyl->h)
				* dot_product(utils->w, cyl->h)));
	utils->c = dot_product(utils->w, utils->w)
		- pow(dot_product(utils->w, cyl->h), 2) - pow(cyl->radius, 2);
	cyl->discr = ((utils->b * utils->b) - (4 * utils->a * utils->c));
	cyl->t0 = utils->infinite;
	cyl->t1 = utils->infinite;
}

int	cylinder_hit_discr_zero(t_util utils, t_cylinder cyl)
{
	if (fabs(dot_product(utils.shadow.direction, cyl.h)) != 1.f)
		cyl.t0 = -0.5 * utils.b / utils.a;
	if (cyl.t0 > utils.shadow_length || cyl.t1 > utils.shadow_length)
		return (0);
	if (cyl.t0 > utils.infinite)
		return (0);
	if (cyl.t0 < 0)
		return (0);
	return (1);
}

int	cylinder_hit(t_util utils, t_cylinder cyl)
{
	cylinder_hit_utils(&utils, &cyl);
	if (cyl.discr < 0)
		return (0);
	else if (cyl.discr == 0)
		return (cylinder_hit_discr_zero(utils, cyl));
	else
	{
		if (utils.b > 0)
			utils.q = -0.5 * (utils.b + sqrt(cyl.discr));
		else
			utils.q = -0.5 * (utils.b - sqrt(cyl.discr));
		cyl.t0 = utils.q / utils.a;
		cyl.t1 = utils.c / utils.q;
		if (cyl.t0 > utils.infinite || cyl.t1 > utils.infinite)
			return (0);
		if (cyl.t0 > utils.shadow_length || cyl.t1 > utils.shadow_length)
			return (0);
		if (cyl.t0 < 0 && cyl.t1 < 0)
			return (0);
		return (cyl.t0 > 0);
	}
}
