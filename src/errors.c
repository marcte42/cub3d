/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:47:02 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/03/27 12:52:20 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_params(char **params)
{
	size_t i;

	if (!params)
		return ;
	i = -1;
	while (params[++i])
		free(params[i]);
	free(params);
}

void	free_struct(t_data *data)
{
	int i;

	if (data->rays)
		free(data->rays);
	if (data->entities)
		ft_lstclear(&data->entities, free);
	i = -1;
	while (++i < T_COUNT)
		if (data->cfg.textures[i])
			free(data->cfg.textures[i]);
	(data->cfg.c_str) ? free(data->cfg.c_str) : 0;
	(data->cfg.f_str) ? free(data->cfg.f_str) : 0;
	(data->cfg.map_lst) ? ft_lstclear(&data->cfg.map_lst, free) : 0;
	if (data->cfg.map)
	{
		while (--data->cfg.map_size.y >= 0
				&& data->cfg.map[data->cfg.map_size.y])
			free(data->cfg.map[data->cfg.map_size.y]);
		free(data->cfg.map);
	}
	if (data->mlx.win)
		mlx_destroy_window(data->mlx.ptr, data->mlx.win);
	if (data->mlx.ptr)
		mlx_destroy_display(data->mlx.ptr);
}

void	exit_failure(t_data *data, char *error)
{
	free_struct(data);
	if (error)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(1);
	}
	exit(0);
}

void	error_params(t_data *data, char **params, char *error)
{
	free_params(params);
	exit_failure(data, error);
}
