/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:28:42 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/22 21:01:26 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CUB3D_H__
# define __CUB3D_H__

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <string.h>
# include <math.h>
# include <stdio.h>
# include <errno.h>

# define Z_KEY					13
# define Q_KEY					0
# define S_KEY					1
# define D_KEY					2
# define LEFT_ARROW				123
# define RIGHT_ARROW			124

# define KEY_PRESS				2
# define KEY_RELEASE			3

# define SPACE					"\t\v\f "
# define TILES					"012NSEW "
# define COLLIDERS				"1"
# define SPRITE					"2"
# define TILE_SIZE				256
# define MAP_RATIO				3

# define SPEED					20
# define TURN_SPEED				0.03
# define PLAYER_SIZE			32
# define FOV					(M_PI / 3)

# define ARG_EXISTS				201
# define PARAM_INVALID			202
# define TXT_ERROR				203
# define ARG_INVALID			204
# define EMPTY_FILE				205
# define WRONG_TILE				206
# define MAP_LEAKING			207
# define PLAYER_ERROR			208
# define MAP_BLANK_LINE			209

typedef int			t_bool;

typedef struct		s_crd
{
	int				x;
	int				y;
}					t_crd;

typedef struct		s_fcrd
{
	float			x;
	float			y;
}					t_fcrd;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
}					t_mlx;

typedef struct		s_frame
{
	void			*ptr;
	int				*addr;
	int				bpp;
	int				line_length;
	int				endian;
}					t_frame;

typedef struct		s_player
{
	t_fcrd			pos;
	float			angle;
}					t_player;

typedef struct		s_ray
{
	float			angle;
	t_fcrd			hit;
	float			distance;
	int				horizontal;
	char			tile;
}					t_ray;

typedef struct		s_event
{
	int				front;
	int				side;
	int				turn;
}					t_event;

typedef struct		s_cfg
{
	int				error;
	t_crd			r;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*s;
	int				f;
	char			*f_str;
	int				c;
	char			*c_str;
	t_list			*map_lst;
	char			**map;
	t_crd			map_size;
}					t_cfg;

typedef	struct		s_texture
{
	void			*ptr;
	int				*addr;
	int				bpp;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_texture;

typedef	struct		s_strip
{
	float			perp_distance;
	float			plane_distance;
	int				height;
	int				top;
	int				tmp_top;
	int				bottom;
	float			ratio;
	int				color;
}					t_strip;

typedef	struct		s_entity
{
	t_fcrd			pos;
	float			distance;
	float			angle;
	int				texture;
	int				visible;
}					t_entity;

typedef struct		s_data
{
	t_mlx			mlx;
	t_frame			frame;
	t_player		player;
	t_ray			*rays;
	t_event			event;
	t_cfg			cfg;
	t_texture		textures[5];
	t_entity		*entities;
	size_t			entities_count;
}					t_data;

int		parse(t_data *data, char *file);
void	parse_map(char *line, t_data *data);
int		arg_exists(char **params, t_data *data);
int		cfg_filled(t_data *data);
void	map_to_mat(t_data *data);
int		is_map_leaking(t_data *data);
void	parse_player(t_data *data);
float	get_angle(char direction);
void	error_params(t_data *data, char **params, char *error);
void	free_params(char **params);
int		ft_issuffix(char *s1, char *s2);

void	init(t_data *data);
void	load(t_data *data);

void	handle_events(t_data *data);

void	update(t_data *data);
void	update_player(t_data *data);
void	update_rays(t_data *data);
void	update_entities(t_data *data);

void	draw(t_data *data);
void	draw_world(t_data *data);
void	draw_player(t_data *data);
void	draw_map(t_data *data);
void	draw_entities(t_data *data);

float	normalize_angle(float angle);
int		params_count(char **params);
int		only_digit(const char *s);

void	exit_failure(t_data *data, char *error);

#endif
