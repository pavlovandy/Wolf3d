/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:31:49 by apavlov           #+#    #+#             */
/*   Updated: 2019/02/05 17:31:50 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

static t_lst	*create_list_rows(char **arr)
{
	t_lst *lst_rows;

	lst_rows = (t_lst*)malloc(sizeof(t_lst));
	if (!lst_rows)
		return (0);
	lst_rows->row = arr;
	lst_rows->next = 0;
	return (lst_rows);
}

static int		free_lst_rows(t_lst **lst_rows)
{
	t_lst	*next;
	int		i;

	if (!*lst_rows || !lst_rows)
		return (1);
	while (*lst_rows)
	{
		i = -1;
		next = (*lst_rows)->next;
		while ((*lst_rows)->row[++i])
			free((*lst_rows)->row[i]);
		free((*lst_rows)->row);
		free(*lst_rows);
		(*lst_rows) = next;
	}
	ft_memdel((void**)lst_rows);
	return (1);
}

static t_lst	*fill_lst_rows(int fd, t_map *map)
{
	char	*line;
	t_lst	*lst_rows;
	t_lst	*previ;
	t_lst	*head;

	if (get_next_line(fd, &line) < 1)
		return (0);
	lst_rows = create_list_rows(ft_strsplit(line, ' '));
	map->height++;
	previ = lst_rows;
	head = lst_rows;
	lst_rows = lst_rows->next;
	free(line);
	while (get_next_line(fd, &line) > 0)
	{
		lst_rows = create_list_rows(ft_strsplit(line, ' '));
		map->height++;
		previ->next = lst_rows;
		previ = lst_rows;
		lst_rows = lst_rows->next;
		free(line);
	}
	return (head);
}

int				del_map(t_map **map)
{
	int		i;

	if (!map || !*map)
		return (1);
	i = -1;
	if ((*map)->map)
	{
		while (++i < (*map)->height)
			free((*map)->map[i]);
		free((*map)->map);
	}
	free(*map);
	return (1);
}

int				read_file(char *file, t_map **map_)
{
	t_lst	*list;
	t_map	*map;
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (error_message("No such file"));
	if (read(fd, NULL, 0) == -1)
		return (error_message("This is not a readable file"));
	if (!(map = ft_memalloc(sizeof(t_map))))
		return (error_message("Map wasnt allocated"));
	*map_ = map;
	map->height = 0;
	if (!(list = fill_lst_rows(fd, map)))
		return (!del_map(&map));
	if (!get_map_from_list(list, &map))
		return (!(del_map(&map) && free_lst_rows(&list)));
	free_lst_rows(&list);
	return (1);
}
