/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 14:30:12 by apavlov           #+#    #+#             */
/*   Updated: 2019/02/09 14:30:13 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int			check_map(t_map *map)
{
	int			i;
	const int	reduced_map_height = map->height - 1;
	const int	reduced_map_width = map->width - 1;

	i = -1;
	if (map->height > MAX_MAP_SIZE | map->width > MAX_MAP_SIZE)
		return (error_message("MAP IS TOO BIG"));
	while (++i < map->width)
		if (map->map[0][i] != 1)
			return (error_message("Top edge isn't correct"));
		else if (map->map[reduced_map_height][i] != 1)
			return (error_message("Bottom edge isn't correct"));
	i = -1;
	while (++i < map->height)
		if (map->map[i][0] != 1)
			return (error_message("Left edge isn't correct"));
		else if (map->map[i][reduced_map_width] != 1)
			return (error_message("Right edge isn't correct"));
	return (1);
}

int			player_start_coord(t_map *map, t_sdl *sdl)
{
	int			i;
	int			j;
	t_player	*p;

	i = 0;
	if (!(p = (t_player*)malloc(sizeof(t_player))))
		return (0);
	sdl->player = p;
	p->flag = 0;
	while (++i < map->width - 1)
	{
		j = 0;
		while (++j < map->height - 1)
			if (map->map[j][i] == PLAYER && !p->flag)
			{
				p->pos_x = i + 0.5;
				p->pos_y = j + 0.5;
				map->map[j][i] = 0;
				p->flag++;
			}
			else if (map->map[j][i] == PLAYER && p->flag)
				return (error_message("There are 2 players at the map"));
	}
	return (p->flag ? 1 : error_message("There are no players at the map"));
}

static int	count_words_and_check(char **arr_str)
{
	int	i;
	int	j;

	i = -1;
	while (arr_str[++i])
	{
		j = 0;
		if (!ft_isdigit(arr_str[i][j]))
			return (0);
		while (ft_isdigit(arr_str[i][j]))
			j++;
	}
	return (i);
}

static int	check_width(t_lst *lst_rows)
{
	int		previ_lenght;
	int		curr_lenght;

	curr_lenght = count_words_and_check(lst_rows->row);
	if (curr_lenght == 0)
		return (0);
	while (lst_rows->next)
	{
		previ_lenght = curr_lenght;
		lst_rows = lst_rows->next;
		curr_lenght = count_words_and_check(lst_rows->row);
		if (previ_lenght != curr_lenght)
			return (0);
	}
	return (curr_lenght);
}

int			get_map_from_list(t_lst *head, t_map **map_)
{
	int		i;
	int		j;
	t_map	*map;

	map = *map_;
	if (!(map->width = check_width(head)))
		return (0);
	if (!(map->map = (int**)ft_memalloc(sizeof(int*) * map->height)))
		return (0);
	i = -1;
	while (++i < map->height)
		if (!(map->map[i] = (int*)ft_memalloc(sizeof(int) * map->width)))
			return (0);
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (head->row[++j])
			map->map[i][j] = ft_atoi(head->row[j]);
		head = head->next;
	}
	return (1);
}
