/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 15:57:48 by apavlov           #+#    #+#             */
/*   Updated: 2019/02/09 15:57:50 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

static	void	init_values(t_dda *d, t_player *p)
{
	d->camera_x = 2 * d->x / (double)WIN_WIDTH - 1;
	d->ray_dir_x = p->dir_x + p->plane_x * d->camera_x;
	d->ray_dir_y = p->dir_y + p->plane_y * d->camera_x;
	d->map_x = (int)p->pos_x;
	d->map_y = (int)p->pos_y;
	d->delta_dist_x = d->ray_dir_x == 0 ? MAX_DOUBLE : fabs(1 / d->ray_dir_x);
	d->delta_dist_y = d->ray_dir_y == 0 ? MAX_DOUBLE : fabs(1 / d->ray_dir_y);
	d->hit = 0;
}

static	void	prepar_to_dda(t_player *p, t_dda *d)
{
	if (d->ray_dir_x < 0)
	{
		d->step_x = -1;
		d->side_dist_x = (p->pos_x - d->map_x) * d->delta_dist_x;
	}
	else
	{
		d->step_x = 1;
		d->side_dist_x = (d->map_x + 1 - p->pos_x) * d->delta_dist_x;
	}
	if (d->ray_dir_y < 0)
	{
		d->step_y = -1;
		d->side_dist_y = (p->pos_y - d->map_y) * d->delta_dist_y;
	}
	else
	{
		d->step_y = 1;
		d->side_dist_y = (d->map_y + 1 - p->pos_y) * d->delta_dist_y;
	}
}

static	void	choose_side_and_tex(t_dda *d)
{
	d->tex_x = (int)(d->wall_x * TEX_WIDTH);
	if (d->side == 0 && (d->ray_dir_x > 0))
		d->tex_x = TEX_WIDTH - d->tex_x - 1;
	else if (d->side == 1 && (d->ray_dir_y < 0))
	{
		d->tex_x = TEX_WIDTH - d->tex_x - 1;
		d->side = 3;
	}
	if ((d->side == 0) && (d->ray_dir_x < 0))
		d->side = 2;
}

static	void	choose_side_and_calculate_distances(t_dda *d, t_player *p)
{
	if (d->side == 0)
		d->perp_wall_dist = \
		(d->map_x - p->pos_x + (1 - d->step_x) / 2) / d->ray_dir_x;
	else
		d->perp_wall_dist = \
		(d->map_y - p->pos_y + (1 - d->step_y) / 2) / d->ray_dir_y;
	d->line_height = (int)(WIN_HEIGHT / d->perp_wall_dist) * LINE_HEIGHT;
	d->draw_start = -(d->line_height) / 2 + WIN_HEIGHT / 2;
	if (d->draw_start < 0)
		d->draw_start = 0;
	d->draw_end = d->line_height / 2 + WIN_HEIGHT / 2;
	if (d->draw_end >= WIN_HEIGHT)
		d->draw_end = WIN_HEIGHT - 1;
	d->wall_x = (!d->side) ? (p->pos_y + d->perp_wall_dist * d->ray_dir_y) \
	: (p->pos_x + d->perp_wall_dist * d->ray_dir_x);
	d->wall_x = d->wall_x - (int)d->wall_x;
	choose_side_and_tex(d);
}

void			dda(t_sdl *s, t_dda *d)
{
	init_values(d, s->player);
	prepar_to_dda(s->player, d);
	while (!d->hit)
	{
		if (d->side_dist_x < d->side_dist_y)
		{
			d->side_dist_x += d->delta_dist_x;
			d->map_x += d->step_x;
			d->side = 0;
		}
		else
		{
			d->side_dist_y += d->delta_dist_y;
			d->map_y += d->step_y;
			d->side = 1;
		}
		if (s->map->map[(int)d->map_y][(int)d->map_x] != 0)
			d->hit = 1;
	}
	choose_side_and_calculate_distances(d, s->player);
}
