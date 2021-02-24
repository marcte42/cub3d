/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:21:00 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/23 23:40:34 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	strip_init(t_data *data, t_strip *strip, size_t x)
{
	strip->perp_distance = data->rays[x].distance
							* cos(data->rays[x].angle - data->player.angle);
	strip->plane_distance = (data->cfg.r.x / 2) * tan(FOV / 2);
	strip->height = (TILE_SIZE / strip->perp_distance)
					* strip->plane_distance * 3;
	strip->top = (data->cfg.r.y / 2) - (strip->height / 2);
	strip->tmp_top = strip->top;
	strip->bottom = (data->cfg.r.y / 2) + (strip->height / 2);
	strip->ratio = (float)TILE_SIZE / strip->height;
	strip->top = strip->top < 0 ? 0 : strip->top;
	strip->bottom = strip->bottom > data->cfg.r.y ?
								data->cfg.r.y : strip->bottom;
}

void	find_strip_color(t_data *data, t_strip *strip, size_t x, size_t y)
{
	if (data->rays[x].horizontal)
	{
		if (data->rays[x].angle < M_PI && data->rays[x].angle > 0)
			strip->color = data->textures[0].addr[(int)((y - strip->tmp_top)
			* strip->ratio) * data->textures[0].line_length / 4
			+ ((int)data->rays[x].hit.x % TILE_SIZE)];
		else
			strip->color = data->textures[1].addr[(int)((y - strip->tmp_top)
			* strip->ratio) * data->textures[1].line_length / 4
			+ (TILE_SIZE - (int)data->rays[x].hit.x % TILE_SIZE)];
	}
	else
	{
		if (data->rays[x].angle < M_PI_2 || data->rays[x].angle > M_PI_2 * 3)
			strip->color = (data->textures[3].addr[(int)((y - strip->tmp_top)
			* strip->ratio) * data->textures[3].line_length / 4
			+ ((int)data->rays[x].hit.y % TILE_SIZE)] >> 1) & 8355711;
		else
			strip->color = (data->textures[2].addr[(int)((y - strip->tmp_top)
			* strip->ratio) * data->textures[2].line_length / 4
			+ (TILE_SIZE - (int)data->rays[x].hit.y % TILE_SIZE)] >> 1)
			& 8355711;
	}
}

void	ft_lstsort(t_list *lst)
{
	t_list		*next;
	t_list		*ptr;
	t_entity	*entity;
	t_entity	*entity_next;
	t_entity	*entity_tmp;

	ptr = lst;
	while (ptr)
	{
		entity = ptr->content;
		next = ptr->next;
		while (next)
		{
			entity_next = next->content;
			if (entity->visible && entity_next->visible && entity->distance < entity_next->distance)
			{
				entity_tmp = ptr->content;
				ptr->content = next->content;
				next->content = entity_tmp;
			}
			next = next->next;
		}
		ptr = ptr->next;
	}
}

void	draw_entities(t_data *data)
{
	ft_lstsort(data->entities);
	ft_entityiter(data, data->entities, draw_entity);
}

void	draw_world(t_data *data)
{
	t_strip	strip;
	size_t	x;
	size_t	y;

	x = -1;
	while (++x < data->cfg.r.x)
	{
		strip_init(data, &strip, x);
		y = 0;
		while (y < strip.top)
			data->frame.addr[y++ *
				data->frame.line_length / 4 + x] = data->cfg.c;
		while (y < strip.bottom)
		{
			find_strip_color(data, &strip, x, y);
			data->frame.addr[y *
				data->frame.line_length / 4 + x] = strip.color;
			y++;
		}
		while (y < data->cfg.r.y)
			data->frame.addr[y++ *
				data->frame.line_length / 4 + x] = data->cfg.f;
	}
}

void	draw(t_data *data)
{
	data->frame.ptr = mlx_new_image(data->mlx.ptr, data->cfg.r.x,
						data->cfg.r.y);
	data->frame.addr = (int *)mlx_get_data_addr(data->frame.ptr,
		&data->frame.bpp, &data->frame.line_length, &data->frame.endian);
	draw_world(data);
	draw_entities(data);
	draw_map(data);
	draw_hud_entities(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
		data->frame.ptr, 0, 0);
	mlx_destroy_image(data->mlx.ptr, data->frame.ptr);
}
