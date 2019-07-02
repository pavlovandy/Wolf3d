/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_add_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 15:57:59 by apavlov           #+#    #+#             */
/*   Updated: 2019/02/09 15:58:00 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		draw_vertical_lines(t_sdl *s, t_dda *d)
{
	int			y;
	Uint32		*pixels;

	y = d->draw_start;
	pixels = (Uint32 *)(s->surface->pixels);
	d->pixels = (Uint32 *)(s->textures.buff[d->side]->pixels);
	if (s->fog)
		d->perc = d->perp_wall_dist / MAX_RANGE;
	while (y < d->draw_end)
	{
		d->y256 = y * 256 - WIN_HEIGHT * 128 + d->line_height * 128;
		d->tex_y = ((d->y256 * TEX_HEIGHT) / d->line_height) / 256;
		d->color = d->pixels[TEX_HEIGHT * d->tex_y + d->tex_x];
		if (s->ceiling == 1)
			d->color = get_color_value(d->color, GREY, \
				fabs(WALL_MID_LINE - (float)d->tex_y / TEX_HEIGHT));
		if (s->fog)
		{
			pixels[y++ * s->surface->w + d->x] = get_color_value(d->color, \
				BLACK, (d->perc > 1 ? 1 : d->perc));
		}
		else
			pixels[y++ * s->surface->w + d->x] = d->color;
	}
}

void		timing(t_sdl *s)
{
	double	frame_time;

	s->prev_time = s->time;
	s->time = SDL_GetTicks();
	frame_time = (s->time - s->prev_time) / 1000.0;
	draw_fps(s, (int)(1.0 / frame_time));
	s->player->msps = s->player->ms * frame_time;
	s->player->rsps = s->player->rs * frame_time;
}

static void	draw_floor_ceiling_2(t_player *p, t_dda *d, int y, t_sdl *s)
{
	d->current_dist = WIN_HEIGHT / (2.0 * y - WIN_HEIGHT);
	d->weight = d->current_dist / d->perp_wall_dist;
	d->current_floor_x = d->weight * (d->floor_x - p->pos_x) + p->pos_x;
	d->current_floor_y = d->weight * (d->floor_y - p->pos_y) + p->pos_y;
	d->floor_tex_x = ((int)(d->current_floor_x * TEX_WIDTH)) % TEX_WIDTH;
	d->floor_tex_y = ((int)(d->current_floor_y * TEX_HEIGHT)) % TEX_HEIGHT;
	d->perc = s->fog ? (1 - (double)y / WIN_HEIGHT) * 2.5 : 0;
}

static void	draw_floor_ceiling_1(t_sdl *s, t_dda *d)
{
	int		y;
	Uint32	*pixels;
	Uint32	*ceil;
	Uint32	*floor;
	Uint32	color;

	pixels = (Uint32 *)s->surface->pixels;
	floor = (Uint32 *)s->textures.buff[4]->pixels;
	ceil = (Uint32 *)s->textures.buff[5]->pixels;
	y = d->draw_end < 0 ? WIN_HEIGHT : d->draw_end;
	while (++y < WIN_HEIGHT)
	{
		draw_floor_ceiling_2(s->player, d, y, s);
		color = floor[TEX_WIDTH * d->floor_tex_y + d->floor_tex_x];
		pixels[y * s->surface->w + d->x] = get_color_value(color, BLACK, \
			(d->perc > 1 ? 1 : d->perc));
		if (s->ceiling == 1)
			pixels[(WIN_HEIGHT - y) * s->surface->w + d->x] = \
				get_color_value(ceil[TEX_WIDTH * d->floor_tex_y + \
					d->floor_tex_x], BLACK, (d->perc > 1 ? 1 : d->perc));
	}
}

void		draw_floor_ceiling(t_sdl *s, t_dda *d)
{
	if (d->side == 0)
	{
		d->floor_x = d->map_x;
		d->floor_y = d->map_y + d->wall_x;
	}
	else if (d->side == 2)
	{
		d->floor_x = d->map_x + 1.0;
		d->floor_y = d->map_y + d->wall_x;
	}
	else if (d->side == 1)
	{
		d->floor_x = d->map_x + d->wall_x;
		d->floor_y = d->map_y;
	}
	else
	{
		d->floor_x = d->map_x + d->wall_x;
		d->floor_y = d->map_y + 1.0;
	}
	draw_floor_ceiling_1(s, d);
}
