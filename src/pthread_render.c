/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:43:18 by apavlov           #+#    #+#             */
/*   Updated: 2019/02/15 19:43:19 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		animate_gun(t_sdl *sdl)
{
	int				i;
	const int		reduced_x = sdl->surface->w / 2;
	const int		reduced_y = sdl->surface->h / 2;
	Uint32 *const	pixels = (Uint32 *const)sdl->surface->pixels;

	if (!sdl->gun.fire)
		SDL_BlitScaled(sdl->gun.gun, &sdl->gun.run_anim, sdl->surface,
		&(SDL_Rect) {sdl->gun.x, sdl->gun.y, sdl->gun.w, sdl->gun.h});
	else
	{
		if (sdl->gun.fire > 0)
		{
			Mix_PlayChannel(-1, sdl->fire_snd, 0);
			SDL_BlitScaled(sdl->gun.gun, \
				&sdl->gun.fire_anim[sdl->gun.fire], sdl->surface, \
				&(SDL_Rect) {sdl->gun.x, sdl->gun.y, sdl->gun.w, sdl->gun.h});
			sdl->gun.fire = (sdl->gun.fire + 1) % 3;
		}
	}
	i = -X_SIZE - 1;
	while (++i < X_SIZE)
	{
		pixels[reduced_y * sdl->surface->w + reduced_x + i] = X_COLOR;
		pixels[(reduced_y + i) * sdl->surface->w + reduced_x] = X_COLOR;
	}
}

void		set_pixel(t_sdl *s, t_render_skybox *sky)
{
	sky->pixels_dst[sky->j * s->surface->w + sky->i] = \
		sky->pixels_src[(int)sky->y * s->skybox->w + (int)sky->x];
}

void		draw_skybox(t_sdl *s)
{
	t_render_skybox	sky;

	sky.x = s->skybox->w * ((cmplx_arg(s->player->dir_x, \
		s->player->dir_y) / M_PI + 1) / 2);
	sky.i = 0;
	sky.step_y = (double)s->skybox->h / WIN_HEIGHT;
	sky.step_x = (double)s->skybox->w / WIN_WIDTH / M_PI;
	sky.pixels_dst = (Uint32 *)s->surface->pixels;
	sky.pixels_src = (Uint32 *)s->skybox->pixels;
	while (sky.i < WIN_WIDTH)
	{
		sky.y = 0;
		sky.j = 0;
		while (sky.j < WIN_HEIGHT / 2)
		{
			set_pixel(s, &sky);
			sky.j++;
			sky.y += sky.step_y;
		}
		sky.i++;
		sky.x += sky.step_x;
	}
}

int			thread_rend(void *data)
{
	t_param	*const	param = (t_param*)data;
	int				i;

	i = param->start_x;
	while (i < param->end_x)
	{
		param->dda.x = i;
		dda(param->sdl, &param->dda);
		draw_vertical_lines(param->sdl, &param->dda);
		draw_floor_ceiling(param->sdl, &param->dda);
		i++;
	}
	return (0);
}

int			render(t_sdl *s)
{
	int					i;
	static const int	slice = WIN_WIDTH / COUNT_THREADS;

	ft_bzero(s->surface->pixels, WIN_HEIGHT * s->surface->pitch);
	i = -1;
	if (s->ceiling == 0)
		draw_skybox(s);
	while (++i < COUNT_THREADS)
	{
		s->p[i].sdl = s;
		s->p[i].start_x = slice * i;
		s->p[i].end_x = slice * (i + 1);
		s->threads[i] = SDL_CreateThread(thread_rend, NULL, s->p + i);
	}
	i = -1;
	while (++i < COUNT_THREADS)
		SDL_WaitThread(s->threads[i], NULL);
	return (0);
}
