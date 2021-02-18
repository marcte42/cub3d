/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:28:42 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/18 12:59:09 by mterkhoy         ###   ########.fr       */
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

# define SPACE					"\t\n\v\f "
# define TILES					"012NSEW "
# define COLLIDERS				"1"
# define TILE_SIZE				32

# define SPEED					1
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
	int				color;
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
	int				c;
	t_list			*map_tmp;
	char			**map;
	t_crd			map_size;
}					t_cfg;

typedef struct		s_data
{
	t_mlx			mlx;
	t_frame			frame;
	t_player		player;
	t_ray			*rays;
	t_event			event;
	t_cfg			cfg;
}					t_data;

void	exit_failure(char *error);

int		parse_file(char *file, t_data *data);
void	update_player(t_data *data);

int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);

void	draw(t_data *data);

void	raycast(t_data *data);

float	normalize_angle(float angle);

#endif
