/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:31:23 by apavlov           #+#    #+#             */
/*   Updated: 2019/02/05 17:31:24 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int		events_loop(t_sdl *s)
{
	while (!s->quit && SDL_PollEvent(&s->event))
		if (s->event.type == SDL_QUIT)
			s->quit = 1;
		else if (s->event.type == SDL_KEYDOWN)
		{
			standart_keys(s);
			optional_keys(s);
		}
		else if (s->event.type == SDL_MOUSEMOTION)
			handle_mause_motion(s);
		else if (s->event.type == SDL_MOUSEBUTTONDOWN && \
				s->event.button.button == SDL_BUTTON_LEFT)
			s->gun.fire = 1;
	return (1);
}

int		main_loop(t_sdl *sdl)
{
	config_start_var(sdl);
	print_keys();
	while (!sdl->quit)
	{
		keys(sdl, sdl->player);
		render(sdl);
		timing(sdl);
		events_loop(sdl);
		animate_gun(sdl);
		SDL_UpdateWindowSurface(sdl->window);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_sdl	*sdl;

	if (argc > 1)
	{
		if (!sdl_init(&sdl))
			return (print_error_init("SDL") + 1);
		if (!(read_file(argv[1], &(sdl->map))))
			return (print_error_init("Map error") + 1);
		else if (!(check_map(sdl->map) && player_start_coord(sdl->map, sdl)))
			return (print_error_init("Map error") + 1);
		else if (!(loading_textures(sdl) | loading_sounds(sdl)))
			return (print_error_init("Textures loading") + 1);
		set_rectangles(sdl);
		main_loop(sdl);
		del_map(&sdl->map);
		sdl_quit(&sdl);
	}
	else
		print_usage();
	return (0);
}
