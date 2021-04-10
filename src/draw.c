/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:21:00 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/04/07 10:28:26 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_data *data)
{
	data->frame.ptr = mlx_new_image(data->mlx.ptr, data->cfg.r.x,
						data->cfg.r.y);
	data->frame.addr = (int *)mlx_get_data_addr(data->frame.ptr,
		&data->frame.bpp, &data->frame.line_length, &data->frame.endian);
	draw_world(data);
	draw_entities(data);
	//draw_map(data);
	//draw_hud_entities(data);
	//draw_player(data);
	if (data->save)
	{
		save(data);
		exit_failure(data, NULL);
	}
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
		data->frame.ptr, 0, 0);
	mlx_destroy_image(data->mlx.ptr, data->frame.ptr);
}
