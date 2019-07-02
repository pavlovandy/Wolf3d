/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:34:58 by apavlov           #+#    #+#             */
/*   Updated: 2019/02/05 17:34:59 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void			print_usage(void)
{
	ft_putstr("usage:\t./wolf3d [map]\n\
Maps is within folder named maps\n");
}

int				print_error_init(char *mess)
{
	ft_putstr("Troubles while init : ");
	ft_putstr(mess);
	ft_putchar('\n');
	return (0);
}

int				error_message(char *mess)
{
	ft_putstr(mess);
	ft_putchar('\n');
	return (0);
}

t_map			*print_error_input(void)
{
	ft_putstr("Hey, gimme right map\n");
	return (0);
}

void			print_keys(void)
{
	ft_putstr("			Fire - left mouse button\n");
	ft_putstr("			Skybox - 1, ceiling - 2, night - 3\n");
	ft_putstr("			Turn on / off music - E\n");
	ft_putstr("			Dark(dosent work with skybox) - F\n");
	ft_putstr("			Run - Left Shift\n");
}
