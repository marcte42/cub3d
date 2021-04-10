/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:27:01 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/22 21:23:27 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		mlx_end_loop(t_data *data)
{
	exit_failure(data, 0);
	return (0);
}

int		key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		exit_failure(data, 0);
	if (keycode == Z_KEY)
		data->event.front = 1;
	if (keycode == S_KEY)
		data->event.front = -1;
	if (keycode == Q_KEY)
		data->event.side = -1;
	if (keycode == D_KEY)
		data->event.side = 1;
	if (keycode == LEFT_ARROW)
		data->event.turn = 1;
	if (keycode == RIGHT_ARROW)
		data->event.turn = -1;
	return (1);
}

int		key_release(int keycode, t_data *data)
{
	if (keycode == Z_KEY)
		data->event.front = 0;
	if (keycode == S_KEY)
		data->event.front = 0;
	if (keycode == Q_KEY)
		data->event.side = 0;
	if (keycode == D_KEY)
		data->event.side = 0;
	if (keycode == LEFT_ARROW)
		data->event.turn = 0;
	if (keycode == RIGHT_ARROW)
		data->event.turn = 0;
	return (1);
}

void	handle_events(t_data *data)
{
	mlx_hook(data->mlx.win, KEY_PRESS, 1L << 0, key_press, data);
	mlx_hook(data->mlx.win, KEY_RELEASE, 1L << 1, key_release, data);
	mlx_hook(data->mlx.win, 33, 1L << 5, mlx_end_loop, data);
}
