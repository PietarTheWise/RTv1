/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_and_camera_assign.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:49:55 by pnoutere          #+#    #+#             */
/*   Updated: 2022/10/04 15:00:00 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	light_assign(char *line, t_util *utils)
{
	char		**values;
	char		**origin;

	utils->light_found = 1;
	values = ft_strsplit(line, ' ');
	check_given_values(values, 3);
	origin = ft_strsplit(values[1], ',');
	utils->translation = ft_strsplit(values[2], ',');
	if (!values || !origin || !utils->translation)
		exit (1);
	check_char_vector(origin);
	check_char_vector(utils->translation);
	vector_assign(origin, 0, &utils->light.origin);
	vector_assign(utils->translation, 0, &utils->light_translation);
	utils->light.origin = vec_add(utils->light.origin,
			utils->light_translation);
	ft_free_array(values);
	ft_free_array(origin);
	ft_free_array(utils->translation);
}

void	camera_assign_free(char **values, char **origin,
	char **rotations, t_util *utils)
{
	ft_free_array(utils->translation);
	ft_free_array(values);
	ft_free_array(origin);
	ft_free_array(rotations);
}

void	camera_assign(char *line, t_util *utils)
{
	char		**values;
	char		**origin;
	char		**rotations;

	utils->camera_found = 1;
	utils->camera_angle_x = 0;
	utils->camera_angle_y = 0;
	utils->camera_angle_z = 0;
	values = ft_strsplit(line, ' ');
	check_given_values(values, 4);
	origin = ft_strsplit(values[1], ',');
	rotations = ft_strsplit(values[2], ',');
	utils->translation = ft_strsplit(values[3], ',');
	if (!values || !origin || !utils->translation || !rotations)
		exit (1);
	check_char_vector(utils->translation);
	utils->camera_angle_x = (float)atoi(rotations[0]);
	utils->camera_angle_y = (float)atoi(rotations[1]);
	utils->camera_angle_z = (float)atoi(rotations[2]);
	check_char_vector(origin);
	vector_assign(utils->translation, 0, &utils->camera_translation);
	vector_assign(origin, 0, &utils->ray.origin);
	utils->ray.origin = vec_add(utils->ray.origin, utils->camera_translation);
	camera_assign_free(values, origin, rotations, utils);
}

void	vector_assign_util(char **coords, int pre_point, int *index, int i)
{
	if ((coords[i] + ft_nbrlen(pre_point))[*index] == '0')
		*index += 1;
	if ((coords[i] + ft_nbrlen(pre_point))[*index] != '.')
	{
		ft_putendl("Information corrupted\n");
		exit(1);
	}
}

void	vector_assign(char **coords, int i, t_vec *xyz)
{
	float	coordinates[3];
	int		pre_point;
	int		post_point;
	int		index;

	i = 0;
	while (i < 3)
	{
		index = 0;
		pre_point = ft_atoi(coords[i]);
		vector_assign_util(coords, pre_point, &index, i);
		post_point = ft_atoi(coords[i] + ft_nbrlen(pre_point) + 1);
		if (pre_point < 0)
			coordinates[i] = (float)pre_point
				- (post_point / pow(10, ft_nbrlen(post_point)));
		else
			coordinates[i] = (float)pre_point
				+ (post_point / pow(10, ft_nbrlen(post_point)));
		i++;
	}
	xyz->x = coordinates[0];
	xyz->y = coordinates[1];
	xyz->z = coordinates[2];
}
