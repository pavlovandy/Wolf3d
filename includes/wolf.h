/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:25:09 by apavlov           #+#    #+#             */
/*   Updated: 2019/01/18 16:25:09 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <fcntl.h>
# include "../libft/libft.h"
# include <math.h>
# include <pthread.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <SDL_mixer.h>
# include "./key_defines.h"

# define MAX_MAP_SIZE 1000
# define NUM_OF_THRD 10
# define WIN_HEIGHT 800
# define WIN_WIDTH 1200
# define PLAYER 10
# define START_MOVE 2
# define START_ROTATION 2
# define MAX_DOUBLE 1.79769e+308
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define LINE_HEIGHT 1
# define COUNT_TEXTURES 9
# define COUNT_THREADS 8
# define COUNT_FPS_NUMBERS 3
# define X_COLOR 0x8B008B
# define X_SIZE 13
# define MAX_RANGE 5
# define BLACK 0x000000
# define MAX_RANGE_TO_WALL 0.2
# define GREY 0x181818
# define WALL_MID_LINE 0.6

typedef struct s_sdl	t_sdl;

typedef struct			s_lst
{
	char			**row;
	struct s_lst	*next;
}						t_lst;

typedef struct			s_map
{
	int				**map;
	int				width;
	int				height;
}						t_map;

typedef struct			s_player
{
	double			pos_y;
	double			pos_x;
	double			plane_x;
	double			plane_y;
	double			dir_x;
	double			dir_y;
	int				ms;
	int				rs;
	double			msps;
	double			rsps;
	int				flag : 2;
}						t_player;

typedef struct			s_dda
{
	int				floor_tex_x;
	int				floor_tex_y;
	double			weight;
	double			current_floor_x;
	double			current_floor_y;
	double			floor_x;
	double			floor_y;
	double			dist_wall;
	double			dist_player;
	double			current_dist;
	Uint32			color;
	Uint32			*pixels;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	int				x;
	int				y256;
	double			rot_speed;
	double			move_speed;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				step_x;
	int				step_y;
	int				hit : 2;
	int				side : 4;
	double			perc;
}						t_dda;

typedef struct			s_textures
{
	SDL_Surface		*(buff[COUNT_TEXTURES]);
}						t_textures;

typedef struct			s_render_skybox
{
	double			x;
	double			y;
	int				i;
	int				j;
	double			step_x;
	double			step_y;
	Uint32			*pixels_dst;
	Uint32			*pixels_src;
}						t_render_skybox;

typedef struct			s_mice
{
	int				x;
	int				last_x;
}						t_mice;

typedef struct			s_param
{
	t_sdl			*sdl;
	int				start_x;
	int				end_x;
	t_dda			dda;
}						t_param;

typedef struct			s_gun
{
	SDL_Surface		*gun;
	SDL_Rect		run_anim;
	SDL_Rect		fire_anim[3];
	int				w;
	int				h;
	int				x;
	int				y;
	int				fire : 3;
}						t_gun;

struct					s_sdl
{
	t_textures		textures;
	t_map			*map;
	t_mice			mice;
	t_player		*player;
	Uint32			time;
	Uint32			prev_time;
	SDL_Event		event;
	SDL_Window		*window;
	SDL_Surface		*surface;
	int				quit : 2;
	Mix_Music		*music;
	SDL_Thread		*threads[COUNT_THREADS];
	t_param			p[COUNT_THREADS];
	TTF_Font		*text_font;
	SDL_Color		text_color;
	SDL_Rect		text_rect;
	int				ceiling;
	SDL_Surface		*skybox;
	t_gun			gun;
	Mix_Chunk		*fire_snd;
	int				fog : 2;
};

t_map					*print_error_input(void);
void					print_usage(void);
int						print_error_init(char *mess);
int						error_message(char *mess);
void					print_keys(void);
int						check_map(t_map *map);
int						sdl_init(t_sdl **sdl);
void					sdl_quit(t_sdl **sdl);
int						read_file(char *file, t_map **map_);
int						del_map(t_map **map_);
int						get_map_from_list(t_lst *list, t_map **map_);
int						player_start_coord(t_map *map, t_sdl *sdl);
void					ft_printsplit(char **str);
int						config_start_var(t_sdl *sdl);
void					standart_keys(t_sdl *s);
void					optional_keys(t_sdl *s);
void					handle_mause_motion(t_sdl *s);
void					rotations(double rot_speed, t_player *p);
void					draw_vertical_lines(t_sdl *s, t_dda *d);
void					timing(t_sdl *s);
int						render(t_sdl *s);
void					draw_floor_ceiling(t_sdl *s, t_dda *d);
int						loading_textures(t_sdl *sdl);
int						loading_sounds(t_sdl *sdl);
int						thread_rend(void *data);
void					dda(t_sdl *s, t_dda *d);
void					draw_fps(t_sdl *sdl, int fps);
int						set_rectangles(t_sdl *sdl);
void					animate_gun(t_sdl *sdl);
int						get_color_value(Uint32 start, Uint32 end, double perc);
void					movement(t_sdl *s, t_player *p, int dir);
void					keys(t_sdl *s, t_player *p);

#endif
