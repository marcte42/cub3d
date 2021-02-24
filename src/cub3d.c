/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 20:56:03 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/23 10:47:14 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		engine(t_data *data)
{
	update(data);
	draw(data);
	return (0);
}

void	setup(t_data *data, char *file, int save)
{
	parse(data, file);
	init(data);
}

void	update(t_data *data)
{
	update_player(data);
	update_rays(data);
	update_entities(data);
}

void	cub3d(char *file, int save)
{
	t_data data;

	errno = 0;
	ft_bzero(&data, sizeof(data));
	setup(&data, file, save);
	handle_events(&data);
	mlx_loop_hook(data.mlx.ptr, engine, &data);
	mlx_loop(data.mlx.ptr);
}

int		main(int argc, char **argv)
{
	if (argc < 2 || argc > 3 || (argc == 3 && strcmp(argv[2], "--save") != 0))
	{
		write(1, "Usage : cub3d [map] [--save]", 27);
		return (1);
	}
	cub3d(argv[1], argc == 3 ? 1 : 0);
	return (0);
}
