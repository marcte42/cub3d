/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:28:42 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/01/27 14:39:32 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CUB3D_H__
# define __CUB3D_H__

# include "mlx.h"
# include "../libft/libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <string.h>
# include <math.h>
# include <stdio.h>
# include <errno.h>

# define SPACE "\t\n\v\f "
# define TILES "012NSEW "

# define ARG_EXISTS				201
# define PARAM_INVALID			202
# define TXT_ERROR				203
# define ARG_INVALID			204
# define EMPTY_FILE				205
# define WRONG_TILE				206

typedef struct		s_crd
{
	int				x;
	int				y;
}					t_crd;

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
	t_crd			pos;
	double			angle;
}					t_player;

typedef struct		s_cfg
{
	int				error;
	t_crd			r;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*s;
	char			*f;
	char			*c;
	t_list			*map_tmp;
	char			**map;
	t_crd			map_size;
	int				tile_size;
}					t_cfg;

typedef struct		s_data
{
	t_mlx			mlx;
	t_frame			frame;
	t_player		player;
	t_cfg			cfg;
}					t_data;

int		parse_file(char *file, t_data *data);


#endif
