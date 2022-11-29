/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:15:09 by pnoutere          #+#    #+#             */
/*   Updated: 2022/09/28 16:46:35 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	rotate_planes(t_util *utils)
{
	int	i;

	i = 0;
	if (utils->plane_amount)
	{
		while (i < utils->plane_amount)
		{
			rotation_xyz(&utils->planes[i].normal,
				utils->planes[i].rotation.x,
				utils->planes[i].rotation.y,
				utils->planes[i].rotation.z);
			i++;
		}
	}
}

int	ray_trace_helpers(t_util *utils)
{
	translation_unit(utils);
	light_plane_correction(utils);
	rotate_planes(utils);
	if (!check_if_inside(*utils))
		return (0);
	return (1);
}

void	ray_trace(void *data, t_util *utils)
{
	int				x;
	int				y;

	if (!ray_trace_helpers(utils))
		return ;
	x = 0;
	while (x < 640)
	{
		y = 0;
		while (y < 480)
		{
			utils->x = x;
			utils->y = y;
			utils->ray.direction
				= calculate_direction(*utils, (float)x, (float)y);
			rotation_x(&utils->ray.direction, utils->camera_angle_x);
			rotation_y(&utils->ray.direction, utils->camera_angle_y);
			rotation_z(&utils->ray.direction, utils->camera_angle_z);
			check_objects_and_draw(data, utils);
			y++;
		}
		x++;
	}
}

int	main(int argc, char **argv)
{
	t_sdl	sdl;
	t_util	utils;

	sdl_init(&sdl);
	init_objects(argc, argv, &utils);
	SDL_LockTexture(sdl.buffer, NULL, &sdl.data, &sdl.pitch);
	ray_trace(sdl.data, &utils);
	sdl_buffer(sdl);
	while (1)
	{
		if (sdl.event.type == SDL_QUIT
			|| sdl.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		{
			SDL_Quit();
			break ;
		}
		else if (sdl.event.type == SDL_WINDOWEVENT)
			if (sdl.event.window.event == SDL_WINDOWEVENT_EXPOSED)
				sdl_buffer(sdl);
		SDL_WaitEvent(&sdl.event);
	}
	SDL_DestroyRenderer(sdl.renderer);
	SDL_DestroyWindow(sdl.win);
	return (0);
}
