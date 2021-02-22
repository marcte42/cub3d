/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:47:02 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/22 21:28:45 by mterkhoy         ###   ########.fr       */
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
	if (data->rays)
		free(data->rays);
	if (data->entities)
		free(data->entities);
	if (data->cfg.no)
		free(data->cfg.no);
	if (data->cfg.so)
		free(data->cfg.so);
	if (data->cfg.we)
		free(data->cfg.we);
	if (data->cfg.ea)
		free(data->cfg.ea);
	if (data->cfg.s)
		free(data->cfg.s);
	if (data->cfg.c_str)
		free(data->cfg.c_str);
	if (data->cfg.f_str)
		free(data->cfg.f_str);
	if (data->cfg.map_lst)
		ft_lstclear(&data->cfg.map_lst, free);
	while (--data->cfg.map_size.y >= 0)
		free(data->cfg.map[data->cfg.map_size.y]);
	free(data->cfg.map);
	mlx_destroy_window(data->mlx.ptr, data->mlx.win);
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
