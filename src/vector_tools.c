/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:10:33 by pnoutere          #+#    #+#             */
/*   Updated: 2022/09/27 19:28:43 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	subtract(t_vec v_one, t_vec v_two)
{
	v_one.x -= v_two.x;
	v_one.y -= v_two.y;
	v_one.z -= v_two.z;
	return (v_one);
}

t_vec	vec_add(t_vec v_one, t_vec v_two)
{
	v_one.x += v_two.x;
	v_one.y += v_two.y;
	v_one.z += v_two.z;
	return (v_one);
}

t_vec	vec_normalize(t_vec vector)
{
	float	len;

	len = vec_len(vector);
	vector.x /= len;
	vector.y /= len;
	vector.z /= len;
	return (vector);
}

t_vec	vec_scale(t_vec vector, float scaler)
{
	vector.x *= scaler;
	vector.y *= scaler;
	vector.z *= scaler;
	return (vector);
}

t_vec	vector(float x, float y, float z)
{
	t_vec	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}
