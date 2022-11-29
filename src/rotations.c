/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:45:48 by pnoutere          #+#    #+#             */
/*   Updated: 2022/09/30 15:41:45 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	read_rotations(char *rotate_str, t_vec *rotation)
{
	char	**rotations;

	rotations = ft_strsplit(rotate_str, ',');
	if (!rotations)
		exit(1);
	rotation->x = (float)atoi(rotations[0]);
	rotation->y = (float)atoi(rotations[1]);
	rotation->z = (float)atoi(rotations[2]);
	ft_free_array(rotations);
}

void	rotation_xyz(t_vec *direction, float angle_x,
			float angle_y, float angle_z)
{
	rotation_x(direction, angle_x);
	rotation_y(direction, angle_y);
	rotation_z(direction, angle_z);
}

void	rotation_x(t_vec *direction, float angle)
{
	float	sin_b;
	float	cos_b;
	float	temp_y;

	angle *= (M_PI / 180);
	sin_b = sin(angle);
	cos_b = cos(angle);
	temp_y = direction->y;
	direction->y = (direction->y * cos_b) - (direction->z * sin_b);
	direction->z = (temp_y * sin_b) + (direction->z * cos_b);
	*direction = vec_normalize(*direction);
}

void	rotation_y(t_vec *direction, float angle)
{
	float	sin_b;
	float	cos_b;
	float	temp_x;

	angle *= (M_PI / 180);
	sin_b = sin(angle);
	cos_b = cos(angle);
	temp_x = direction->x;
	direction->x = (direction->x * cos_b) + (direction->z * sin_b);
	direction->z = (direction->z * cos_b) - (temp_x * sin_b);
	*direction = vec_normalize(*direction);
}

void	rotation_z(t_vec *direction, float angle)
{
	float	sin_b;
	float	cos_b;
	float	temp_x;

	angle *= (M_PI / 180);
	sin_b = sin(angle);
	cos_b = cos(angle);
	temp_x = direction->x;
	direction->x = (direction->x * cos_b) - (direction->y * sin_b);
	direction->y = (temp_x * sin_b) + (direction->y * cos_b);
	*direction = vec_normalize(*direction);
}
