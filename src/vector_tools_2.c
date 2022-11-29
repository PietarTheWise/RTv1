/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tools_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:40:00 by pnoutere          #+#    #+#             */
/*   Updated: 2022/09/27 14:40:20 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	vec_len(t_vec vector)
{
	return (sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2)));
}

float	dot_product(t_vec v_one, t_vec v_two)
{
	return (v_one.y * v_two.y + v_one.x * v_two.x + v_one.z * v_two.z);
}
