/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:28:42 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/04/12 11:16:07 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <math.h>
# include <stdio.h>
# include <errno.h>

# define Z_KEY			122
# define Q_KEY			113
# define S_KEY			115
# define D_KEY			100
# define LEFT_ARROW		65361
# define RIGHT_ARROW	65363
# define ESC			65307

# define KEY_PRESS		2
# define KEY_RELEASE	3

# define SPACE			"\t\v\f "
# define TILES			"012NSEW "
# define COLLIDERS		"1"
# define ENTITY			"2"
# define TILE_SIZE		64
# define MAP_RATIO		5
# define T_COUNT		5

# define SPEED			6
# define TURN_SPEED		0.02
# define PLAYER_SIZE	5
# define FOV			1.0471976667

# define ARG_EXISTS		201
# define PARAM_INVALID	202
# define TXT_ERROR		203
# define ARG_INVALID	204
# define EMPTY_FILE		205
# define WRONG_TILE		206
# define MAP_LEAKING	207
# define PLAYER_ERROR	208
# define MAP_BLANK_LINE	209

typedef struct			s_crd
{
	int					x;
	int					y;
}						t_crd;

typedef struct			s_fcrd
{
	float				x;
	float				y;
}						t_fcrd;

typedef struct			s_mlx
{
	void				*ptr;
	void				*win;
}						t_mlx;

typedef struct			s_frame
{
	void				*ptr;
	int					*addr;
	int					bpp;
	int					line_length;
	int					endian;
}						t_frame;

typedef struct			s_player
{
	t_fcrd				pos;
	float				angle;
	int					health;
}						t_player;

typedef struct			s_ray
{
	float				angle;
	t_fcrd				hit;
	float				distance;
	int					horizontal;
	char				tile;
}						t_ray;

typedef struct			s_event
{
	int					front;
	int					side;
	int					turn;
}						t_event;

typedef struct			s_cfg
{
	int					error;
	t_crd				r;
	char				*textures[T_COUNT];
	int					f;
	char				*f_str;
	int					c;
	char				*c_str;
	t_list				*map_lst;
	char				**map;
	char				**map_tmp;
	t_crd				map_size;
}						t_cfg;

typedef	struct			s_texture
{
	void				*ptr;
	int					*addr;
	int					bpp;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_texture;

typedef	struct			s_strip
{
	float				perp_distance;
	float				plane_distance;
	int					height;
	int					top;
	int					tmp_top;
	int					bottom;
	float				ratio;
	int					color;
}						t_strip;

typedef	struct			s_entity
{
	t_fcrd				pos;
	float				distance;
	float				angle;
	int					visible;
	float				size;
	float				top;
	float				real_top;
	float				bottom;
	float				sprite_left;
	float				sprite_right;
	float				ratio;
}						t_entity;

typedef struct			s_data
{
	t_mlx				mlx;
	t_frame				frame;
	t_player			player;
	t_ray				*rays;
	t_event				event;
	t_cfg				cfg;
	t_texture			textures[T_COUNT];
	t_list				*entities;
	int					save;
	char				*line;
	char				*rest[256];
	int					fd;
}						t_data;

void					save(t_data *data);

int						parse(t_data *data, char *file);
void					parse_map(char **params, t_data *data);
int						arg_exists(char **params, t_data *data);
int						cfg_filled(t_data *data);
void					map_to_mat(t_data *data);
int						is_map_leaking(int x, int y, t_data *data);
void					parse_player(t_data *data);
float					get_angle(char direction);
void					error_params(t_data *data, char **params, char *error);
void					free_params(char **params);
int						ft_issuffix(char *s1, char *s2);

void					init(t_data *data);
void					init_textures(t_data *data);
void					init_entities(t_data *data);

void					update(t_data *data);
void					update_player(t_data *data);
void					update_rays(t_data *data);
void					update_entities(t_data *data);

void					draw(t_data *data);
void					draw_world(t_data *data);
void					draw_entities(t_data *data);
void					draw_player(t_data *data);
void					draw_map(t_data *data);
void					draw_hud_entities(t_data *data);
void					ft_entityiter(t_data *data, t_list *lst,
							void (*f)(t_data *, t_entity *));

void					handle_events(t_data *data);

float					normalize_angle(float angle);
int						params_count(char **params);
int						is_wall(t_data *data, float x, float y);
float					hit_distance(float p1_x, float p1_y,
							float p2_x, float p2_y);
void					print_matrix(t_data *data);
t_crd					ft_lstpop(t_list **lst);
t_crd					*point_create(t_data *data, int x, int y);

void					exit_failure(t_data *data, char *error);

#endif
