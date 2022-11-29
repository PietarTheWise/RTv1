/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoutere <pnoutere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:44:09 by pnoutere          #+#    #+#             */
/*   Updated: 2022/09/29 12:03:35 by pnoutere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	sdl_init(t_sdl *sdl)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(640, 480, 0, &sdl->win, &sdl->renderer);
	sdl->buffer = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, 640, 480);
}

void	sdl_buffer(t_sdl sdl)
{
	SDL_UnlockTexture(sdl.buffer);
	SDL_RenderCopy(sdl.renderer, sdl.buffer, NULL, NULL);
	SDL_RenderPresent(sdl.renderer);
	SDL_RenderClear(sdl.renderer);
}
