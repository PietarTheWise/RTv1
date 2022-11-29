/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:28:11 by pnoutere          #+#    #+#             */
/*   Updated: 2022/09/28 15:35:20 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	discr_bigger_than_one(t_util utils, t_cone *cone)
{
	if (utils.b > 0)
		utils.q = -0.5 * (utils.b + sqrt(cone->discr));
	else
		utils.q = -0.5 * (utils.b - sqrt(cone->discr));
	cone->t0 = utils.q / utils.a;
	cone->t1 = utils.c / utils.q;
	if (cone->t0 < 0 && cone->t1 < 0)
	{
		cone->t0 = utils.infinite;
		cone->t1 = utils.infinite;
	}
	else if (cone->t1 < 0)
		cone->t1 = cone->t0;
}

void	discr_zero(t_util utils, t_cone *cone)
{
	float	prod;
	float	len;
	float	cosa;

	prod = dot_product(utils.ray.direction, cone->h);
	len = vec_len(cone->subtr_top_bot);
	cosa = (len / sqrt(pow(len, 2) + pow(cone->radius, 2)));
	if (fabs(prod) != cosa)
		cone->t1 = -0.5 * utils.b / utils.a;
}

void	initiate_cone_values(t_util *utils, t_cone *cone)
{
	float	len;

	cone->subtr_top_bot = subtract(cone->top, cone->bottom);
	len = vec_len(cone->subtr_top_bot);
	rotation_xyz(&cone->subtr_top_bot, cone->rotation.x,
		cone->rotation.y, cone->rotation.z);
	cone->subtr_top_bot = vec_scale(cone->subtr_top_bot, len);
	utils->w = subtract(utils->ray.origin, cone->top);
	cone->h = vec_normalize(cone->subtr_top_bot);
	cone->m = pow(cone->radius, 2) / pow(vec_len(cone->subtr_top_bot), 2);
}

void	cone_calculation(t_util utils, t_cone *cone)
{
	float	ray_dot_product;
	float	ray_dir_h;
	float	dot_w_h;

	ray_dot_product = dot_product(utils.ray.direction, utils.ray.direction);
	initiate_cone_values(&utils, cone);
	ray_dir_h = dot_product(utils.ray.direction, cone->h);
	dot_w_h = dot_product(utils.w, cone->h);
	utils.a = ray_dot_product - (cone->m * pow(ray_dir_h, 2))
		- pow(ray_dir_h, 2);
	utils.b = 2 * (dot_product(utils.ray.direction, utils.w)
			- (cone->m * (ray_dir_h * dot_w_h)) - (ray_dir_h * dot_w_h));
	utils.c = dot_product(utils.w, utils.w)
		- (cone->m * pow(dot_w_h, 2)) - pow(dot_w_h, 2);
	cone->discr = ((utils.b * utils.b) - (4 * utils.a * utils.c));
	cone->t0 = utils.infinite;
	cone->t1 = utils.infinite;
	if (cone->discr > 0)
		discr_bigger_than_one(utils, cone);
	else if (cone->discr == 0)
		discr_zero(utils, cone);
	else
		return ;
	cone->hit_point = vec_add(utils.ray.origin,
			vec_scale(utils.ray.direction, cone->t1));
}
