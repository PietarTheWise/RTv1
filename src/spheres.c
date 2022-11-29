/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:28:11 by pnoutere          #+#    #+#             */
/*   Updated: 2022/09/30 14:45:07 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	sphere_assign_util(char **radius, char **colors,
	t_util *utils, int *index)
{
	if ((float)ft_atoi(radius[0]) < 0)
		utils->spheres[*index].radius = (float)ft_atoi(radius[0])
			- (ft_atoi(radius[1]) / pow(10, ft_nbrlen(ft_atoi(radius[1]))));
	else
		utils->spheres[*index].radius = (float)ft_atoi(radius[0])
			+ (ft_atoi(radius[1]) / pow(10, ft_nbrlen(ft_atoi(radius[1]))));
	set_color(ft_atoi(colors[0]), ft_atoi(colors[1]),
		ft_atoi(colors[2]), &utils->spheres[*index].color);
	*index += 1;
}

void	sphere_assign(char *line, t_util *utils)
{
	static int	index;

	check_line(line + 7);
	utils->values = ft_strsplit(line, ' ');
	check_given_values(utils->values, 5);
	utils->center = ft_strsplit(utils->values[1], ',');
	utils->radius = ft_strsplit(utils->values[2], '.');
	utils->colors = ft_strsplit(utils->values[3], ',');
	utils->translation = ft_strsplit(utils->values[4], ',');
	if (!utils->values || !utils->center || !utils->radius
		|| !utils->colors || !utils->translation)
		exit(1);
	check_char_vector(utils->center);
	check_char_vector(utils->translation);
	check_float_vals(utils->radius[0], utils->radius[1]);
	vector_assign(utils->translation, 0, &utils->spheres[index].translation);
	vector_assign(utils->center, 0, &utils->spheres[index].center);
	sphere_assign_util(utils->radius, utils->colors, utils, &index);
	ft_free_array(utils->translation);
	ft_free_array(utils->values);
	ft_free_array(utils->center);
	ft_free_array(utils->radius);
	ft_free_array(utils->colors);
}

void	check_spheres(t_util utils, t_sphere *sphere, t_ray light)
{
	calculate_light_level(&utils, sphere->t1, sphere->center, light);
	sphere->light_level = utils.light_level;
}

void	sphere_calculation(t_util utils, t_sphere *sphere)
{
	utils.w = subtract(utils.ray.origin, sphere->center);
	utils.a = dot_product(utils.ray.direction, utils.ray.direction);
	utils.b = 2 * dot_product(utils.ray.direction, utils.w);
	utils.c = dot_product(utils.w, utils.w) - pow(sphere->radius, 2);
	sphere->discr = ((utils.b * utils.b) - (4 * utils.a * utils.c));
	if (sphere->discr < 0)
	{
		sphere->t0 = utils.infinite;
		sphere->t1 = utils.infinite;
		return ;
	}
	else if (sphere->discr == 0)
		sphere->t0 = -0.5 * utils.b / utils.a;
	else
	{
		if (utils.b > 0)
			utils.q = -0.5 * (utils.b + sqrt(sphere->discr));
		else
			utils.q = -0.5 * (utils.b - sqrt(sphere->discr));
		sphere->t0 = utils.q / utils.a;
		sphere->t1 = utils.c / utils.q;
	}
	sphere->hit_point = vec_add(utils.ray.origin,
			vec_scale(utils.ray.direction, sphere->t1));
}
