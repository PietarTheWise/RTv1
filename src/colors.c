/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:21:47 by pnoutere          #+#    #+#             */
/*   Updated: 2022/10/04 14:31:26 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	calculate_light_level(t_util *utils,
	float t0, t_vec center, t_ray light)
{
	t_vec	normal;

	utils->hit_point = vec_add(utils->ray.origin,
			vec_scale(utils->ray.direction, t0));
	normal = vec_normalize(subtract(utils->hit_point, center));
	light.direction = vec_scale(vec_normalize(
				subtract(utils->hit_point, light.origin)), -1.0);
	utils->light_level = dot_product(normal, light.direction);
	if (utils->light_level < 0.0)
		utils->light_level = 0;
}

void	set_color(int r, int g, int b, union u_colour *color)
{
	color->channels[0] = b;
	color->channels[1] = g;
	color->channels[2] = r;
	color->channels[3] = 255;
}

int	level_color(union u_colour color, float light_level)
{
	int	r;
	int	b;
	int	g;

	r = (int)color.channels[0] * light_level;
	b = (int)color.channels[1] * light_level;
	g = (int)color.channels[2] * light_level;
	if (r > 255)
		color.channels[0] = 255;
	else
		color.channels[0] *= light_level;
	if (b > 255)
		color.channels[1] = 255;
	else
		color.channels[1] *= light_level;
	if (g > 255)
		color.channels[2] = 255;
	else
		color.channels[2] *= light_level;
	return (color.number);
}
