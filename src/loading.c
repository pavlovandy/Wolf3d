/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 18:55:43 by apavlov           #+#    #+#             */
/*   Updated: 2019/02/09 18:55:44 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int			loading_textures(t_sdl *sdl)
{
	if (!(sdl->textures.buff[0] = IMG_Load("pics/redbrick.png")) | \
		!(sdl->textures.buff[4] = IMG_Load("pics/mossy.png")) | \
		!(sdl->textures.buff[2] = IMG_Load("pics/greystone.png")) | \
		!(sdl->textures.buff[3] = IMG_Load("pics/colorstone.png")) | \
		!(sdl->textures.buff[5] = IMG_Load("pics/stones.png")) | \
		!(sdl->textures.buff[1] = IMG_Load("pics/grey_bricks.png")) | \
		!(sdl->textures.buff[6] = IMG_Load("pics/pillar.png")) | \
		!(sdl->textures.buff[7] = IMG_Load("pics/barrel.png")) | \
		!(sdl->textures.buff[8] = IMG_Load("pics/greenlight.png")) | \
		!(sdl->gun.gun = IMG_Load("pics/gun_anim.png")) | \
		!(sdl->skybox = IMG_Load("pics/skybox.png")))
	{
		return (error_message((char *)IMG_GetError()));
	}
	if (!(sdl->text_font = TTF_OpenFont("fonts/doom.ttf", 28)))
		return (error_message((char *)IMG_GetError()));
	sdl->text_color = (SDL_Color){255, 255, 255, 0};
	SDL_SetColorKey(sdl->gun.gun, SDL_TRUE, \
		SDL_MapRGB(sdl->gun.gun->format, 0, 0xFF, 0xFF));
	return (1);
}

int			loading_sounds(t_sdl *sdl)
{
	if (!(sdl->music = Mix_LoadMUS("sounds/doom_music.wav")) | \
		!(sdl->fire_snd = Mix_LoadWAV("sounds/fire.wav")))
		return (error_message((char *)Mix_GetError()));
	return (1);
}

static int	set_gun_param(t_gun *g)
{
	g->w = g->gun->w;
	g->h = g->gun->h;
	g->x = WIN_WIDTH / 2 - g->gun->w / 2 + WIN_WIDTH / 5;
	g->y = WIN_HEIGHT - g->gun->h + 20;
	return (1);
}

int			set_rectangles(t_sdl *sdl)
{
	sdl->text_rect.x = 20;
	sdl->text_rect.y = 20;
	sdl->text_rect.w = 50;
	sdl->text_rect.h = 10;
	sdl->gun.run_anim.x = 0;
	sdl->gun.run_anim.y = 0;
	sdl->gun.run_anim.w = sdl->gun.gun->w / 2;
	sdl->gun.run_anim.h = sdl->gun.gun->h / 2;
	sdl->gun.fire_anim[0].x = sdl->gun.gun->w / 2;
	sdl->gun.fire_anim[0].y = 0;
	sdl->gun.fire_anim[0].y = sdl->gun.gun->w / 2;
	sdl->gun.fire_anim[0].h = sdl->gun.gun->h / 2;
	sdl->gun.fire_anim[1].x = 0;
	sdl->gun.fire_anim[1].y = sdl->gun.gun->h / 2;
	sdl->gun.fire_anim[1].w = sdl->gun.gun->w / 2;
	sdl->gun.fire_anim[1].h = sdl->gun.gun->h / 2;
	sdl->gun.fire_anim[2].x = sdl->gun.gun->w / 2;
	sdl->gun.fire_anim[2].y = sdl->gun.gun->h / 2;
	sdl->gun.fire_anim[2].w = sdl->gun.gun->w / 2;
	sdl->gun.fire_anim[2].h = sdl->gun.gun->h / 2;
	return (set_gun_param(&sdl->gun));
}
