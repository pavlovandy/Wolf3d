/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:31:29 by apavlov           #+#    #+#             */
/*   Updated: 2019/02/05 17:31:30 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		keys(t_sdl *s, t_player *p)
{
	const Uint8 *state = SDL_GetKeyboardState(0);

	if ((state[SDL_SCANCODE_UP] | state[SDL_SCANCODE_W]) && \
	state[SDL_SCANCODE_LSHIFT])
		movement(s, p, 2);
	else if ((state[SDL_SCANCODE_UP] | state[SDL_SCANCODE_W]) && \
	!state[SDL_SCANCODE_LSHIFT])
		movement(s, p, 1);
	if ((state[SDL_SCANCODE_S] | state[SDL_SCANCODE_DOWN]) && \
	state[SDL_SCANCODE_LSHIFT])
		movement(s, p, -2);
	else if ((state[SDL_SCANCODE_S] | state[SDL_SCANCODE_DOWN]) && \
		!state[SDL_SCANCODE_LSHIFT])
		movement(s, p, -1);
	if (state[SDL_SCANCODE_A] | state[SDL_SCANCODE_LEFT])
		rotations(-p->rsps, p);
	if (state[SDL_SCANCODE_D] | state[SDL_SCANCODE_RIGHT])
		rotations(p->rsps, p);
}

void		standart_keys(t_sdl *s)
{
	if (s->event.key.keysym.sym == ESC_KEY)
		s->quit = 1;
}

void		optional_keys(t_sdl *s)
{
	if (s->event.key.keysym.sym == E_KEY)
	{
		if (Mix_PlayingMusic() == 0)
			Mix_PlayMusic(s->music, -1);
		else
		{
			if (Mix_PausedMusic() == 1)
				Mix_ResumeMusic();
			else
				Mix_PauseMusic();
		}
	}
	else if (s->event.key.keysym.sym == NUM_0 + 1)
	{
		s->ceiling = 0;
		s->fog = 0;
	}
	else if (s->event.key.keysym.sym == NUM_0 + 2)
		s->ceiling = 1;
	else if (s->event.key.keysym.sym == NUM_0 + 3)
		s->ceiling = 2;
	else if (s->event.key.keysym.sym == F_KEY && s->ceiling != 0)
		s->fog = s->fog == 1 ? 0 : 1;
}

void		handle_mause_motion(t_sdl *s)
{
	SDL_GetRelativeMouseState(&s->mice.x, NULL);
	if (s->mice.x < 0)
		rotations(s->player->rsps * s->mice.x / 20, s->player);
	else if (s->mice.x > 0)
		rotations(s->player->rsps * s->mice.x / 20, s->player);
}
