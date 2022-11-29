/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:49:44 by pnoutere          #+#    #+#             */
/*   Updated: 2022/09/30 15:16:44 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	free_cylinder_str(t_util *utils)
{	
	ft_free_array(utils->translation);
	ft_free_array(utils->values);
	ft_free_array(utils->top);
	ft_free_array(utils->colors);
	ft_free_array(utils->bottom);
	ft_free_array(utils->radius);
}

void	free_plane_str(t_util *utils)
{
	ft_free_array(utils->translation);
	ft_free_array(utils->values);
	ft_free_array(utils->center);
	ft_free_array(utils->colors);
	ft_free_array(utils->c_normal);
}

void	free_cone_str(t_util *utils)
{
	ft_free_array(utils->values);
	ft_free_array(utils->top);
	ft_free_array(utils->colors);
	ft_free_array(utils->bottom);
	ft_free_array(utils->radius);
	ft_free_array(utils->translation);
}
