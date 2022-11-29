/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_for_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:47:58 by pnoutere          #+#    #+#             */
/*   Updated: 2022/09/30 15:07:06 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	plane_assign(char *line, t_util *utils)
{
	static int	index;

	check_line(line + 6);
	utils->values = ft_strsplit(line, ' ');
	check_given_values(utils->values, 6);
	utils->center = ft_strsplit(utils->values[1], ',');
	utils->c_normal = ft_strsplit(utils->values[2], ',');
	utils->colors = ft_strsplit(utils->values[3], ',');
	read_rotations(utils->values[4], &utils->planes[index].rotation);
	utils->translation = ft_strsplit(utils->values[5], ',');
	if (!utils->values || !utils->center || !utils->c_normal
		|| !utils->colors || !utils->translation)
		exit(1);
	check_char_vector(utils->center);
	check_char_vector(utils->c_normal);
	check_char_vector(utils->translation);
	vector_assign(utils->center, 0, &utils->planes[index].center);
	vector_assign(utils->c_normal, 0, &utils->planes[index].normal);
	vector_assign(utils->translation, 0, &utils->planes[index].translation);
	utils->planes[index].normal = vec_normalize(utils->planes[index].normal);
	set_color(ft_atoi(utils->colors[0]), ft_atoi(utils->colors[1]),
		ft_atoi(utils->colors[2]), &utils->planes[index].color);
	index++;
	free_plane_str(utils);
}

void	cone_assign_utils(char **radius, t_util *utils,
	int *index, char **colors)
{
	if ((float)ft_atoi(radius[0]) < 0)
		utils->cones[*index].radius = (float)ft_atoi(radius[0])
			- (ft_atoi(radius[1]) / pow(10, ft_nbrlen(ft_atoi(radius[1]))));
	else
		utils->cones[*index].radius = (float)ft_atoi(radius[0])
			+ (ft_atoi(radius[1]) / pow(10, ft_nbrlen(ft_atoi(radius[1]))));
	set_color(ft_atoi(colors[0]), ft_atoi(colors[1]),
		ft_atoi(colors[2]), &utils->cones[*index].color);
	*index += 1;
}

void	cone_assign(char *line, t_util *utils)
{
	static int	index;

	check_line(line + 5);
	utils->values = ft_strsplit(line, ' ');
	check_given_values(utils->values, 7);
	utils->top = ft_strsplit(utils->values[1], ',');
	utils->bottom = ft_strsplit(utils->values[2], ',');
	utils->radius = ft_strsplit(utils->values[3], '.');
	utils->colors = ft_strsplit(utils->values[4], ',');
	read_rotations(utils->values[5], &utils->cones[index].rotation);
	utils->translation = ft_strsplit(utils->values[6], ',');
	if (!utils->values || !utils->top || !utils->bottom
		|| !utils->radius || !utils->colors || !utils->translation)
		exit(1);
	check_char_vector(utils->top);
	check_char_vector(utils->bottom);
	check_char_vector(utils->translation);
	check_float_vals(utils->radius[0], utils->radius[1]);
	vector_assign(utils->top, 0, &utils->cones[index].top);
	vector_assign(utils->bottom, 0, &utils->cones[index].bottom);
	vector_assign(utils->translation, 0, &utils->cones[index].translation);
	cone_assign_utils(utils->radius, utils, &index, utils->colors);
	free_cone_str(utils);
}

void	cylinder_assign_utils(char **radius, t_util *utils,
	int *index, char **colors)
{
	if ((float)ft_atoi(radius[0]) < 0)
		utils->cylinders[*index].radius = (float)ft_atoi(radius[0])
			- (ft_atoi(radius[1]) / pow(10, ft_nbrlen(ft_atoi(radius[1]))));
	else
		utils->cylinders[*index].radius = (float)ft_atoi(radius[0])
			+ (ft_atoi(radius[1]) / pow(10, ft_nbrlen(ft_atoi(radius[1]))));
	set_color(ft_atoi(colors[0]), ft_atoi(colors[1]),
		ft_atoi(colors[2]), &utils->cylinders[*index].color);
	*index += 1;
}

void	cylinder_assign(char *line, t_util *utils)
{
	static int	index;

	check_line(line + 9);
	utils->values = ft_strsplit(line, ' ');
	check_given_values(utils->values, 7);
	utils->top = ft_strsplit(utils->values[1], ',');
	utils->bottom = ft_strsplit(utils->values[2], ',');
	utils->radius = ft_strsplit(utils->values[3], '.');
	utils->colors = ft_strsplit(utils->values[4], ',');
	read_rotations(utils->values[5], &utils->cylinders[index].rotation);
	utils->translation = ft_strsplit(utils->values[6], ',');
	if (!utils->translation || !utils->values || !utils->top
		|| !utils->bottom || !utils->radius || !utils->colors)
		exit (1);
	check_char_vector(utils->top);
	check_char_vector(utils->bottom);
	check_char_vector(utils->translation);
	check_float_vals(utils->radius[0], utils->radius[1]);
	vector_assign(utils->top, 0, &utils->cylinders[index].top);
	vector_assign(utils->bottom, 0, &utils->cylinders[index].bottom);
	vector_assign(utils->translation, 0, &utils->cylinders[index].translation);
	cylinder_assign_utils(utils->radius, utils, &index, utils->colors);
	free_cylinder_str(utils);
}
