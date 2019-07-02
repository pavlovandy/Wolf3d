/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 18:28:42 by apavlov           #+#    #+#             */
/*   Updated: 2019/02/05 18:28:44 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		movement(t_sdl *s, t_player *p, int dir)
{
	float	x;
	float	y;

	x = p->pos_x + p->dir_x * (p->msps + MAX_RANGE_TO_WALL) * dir;
	y = p->pos_y + p->dir_y * (p->msps + MAX_RANGE_TO_WALL) * dir;
	if (x < s->map->width - 1 && x > 1)
		if (!s->map->map[(int)(p->pos_y)][(int)x])
			p->pos_x += p->dir_x * p->msps * dir;
	if (y < s->map->height - 1 && y > 1)
		if (!s->map->map[(int)y][(int)(p->pos_x)])
			p->pos_y += p->dir_y * p->msps * dir;
}

int			get_color_value(Uint32 start, Uint32 end, double perc)
{
	int		r;
	int		g;
	int		b;

	r = line_point((start >> 16) & 0xFF, (end >> 16) & 0xFF, perc);
	g = line_point((start >> 8) & 0xFF, (end >> 8) & 0xFF, perc);
	b = line_point(start & 0xFF, end & 0xFF, perc);
	return ((r << 16) | (g << 8) | b);
}

int			config_start_var(t_sdl *sdl)
{
	sdl->player->dir_x = 1;
	sdl->player->dir_y = 0;
	sdl->player->plane_x = 0;
	sdl->player->plane_y = 0.66;
	sdl->player->ms = START_MOVE;
	sdl->player->rs = START_ROTATION;
	sdl->player->msps = 0.2;
	sdl->player->rsps = 0.1;
	sdl->time = 0;
	sdl->prev_time = 0;
	sdl->quit = 0;
	return (1);
}

void		rotations(double rsps, t_player *p)
{
	double prev_dir_x;
	double prev_plane_x;

	prev_dir_x = p->dir_x;
	p->dir_x = prev_dir_x * cos(rsps) - p->dir_y * sin(rsps);
	p->dir_y = prev_dir_x * sin(rsps) + p->dir_y * cos(rsps);
	prev_plane_x = p->plane_x;
	p->plane_x = prev_plane_x * cos(rsps) - p->plane_y * sin(rsps);
	p->plane_y = prev_plane_x * sin(rsps) + p->plane_y * cos(rsps);
}

void		draw_fps(t_sdl *sdl, int fps)
{
	static char	str[COUNT_FPS_NUMBERS];
	int			i;
	SDL_Surface	*message;

	i = -1;
	while (++i < 3)
	{
		str[2 - i] = fps % 10 + 48;
		fps /= 10;
	}
	message = TTF_RenderText_Solid(sdl->text_font, str, sdl->text_color);
	SDL_BlitSurface(message, NULL, sdl->surface, &sdl->text_rect);
	SDL_FreeSurface(message);
}
