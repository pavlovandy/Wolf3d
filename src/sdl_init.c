/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:34:21 by apavlov           #+#    #+#             */
/*   Updated: 2019/02/05 17:34:23 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

static void	delete_surface_of_textures(t_sdl *sdl)
{
	int i;

	i = -1;
	while (++i < COUNT_TEXTURES)
	{
		SDL_FreeSurface(sdl->textures.buff[i]);
		sdl->textures.buff[i] = 0;
	}
	SDL_FreeSurface(sdl->skybox);
	SDL_FreeSurface(sdl->gun.gun);
	sdl->skybox = 0;
	sdl->gun.gun = 0;
}

int			sdl_init(t_sdl **sdl)
{
	*sdl = (t_sdl*)malloc(sizeof(t_sdl));
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return (error_message((char *)SDL_GetError()));
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG))
		return (error_message((char *)SDL_GetError()));
	if (!((*sdl)->window = SDL_CreateWindow("WOLF", SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN)))
		return (error_message((char *)SDL_GetError()));
	if (!((*sdl)->surface = SDL_GetWindowSurface((*sdl)->window)))
		return (error_message((char *)SDL_GetError()));
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		return (error_message((char *)SDL_GetError()));
	if (TTF_Init() == -1)
		return (error_message((char *)SDL_GetError()));
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetWindowGrab((*sdl)->window, 1);
	SDL_SetRelativeMouseMode(1);
	(*sdl)->ceiling = 1;
	(*sdl)->fog = 1;
	return (1);
}

void		sdl_quit(t_sdl **sdl)
{
	SDL_FreeSurface((*sdl)->surface);
	(*sdl)->surface = 0;
	SDL_DestroyWindow((*sdl)->window);
	(*sdl)->window = 0;
	TTF_CloseFont((*sdl)->text_font);
	TTF_Quit();
	delete_surface_of_textures(*sdl);
	IMG_Quit();
	Mix_FreeMusic((*sdl)->music);
	Mix_FreeChunk((*sdl)->fire_snd);
	Mix_CloseAudio();
	SDL_Quit();
	if ((*sdl)->player)
		free((*sdl)->player);
	free(*sdl);
}
