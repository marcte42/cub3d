/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 19:00:08 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/24 08:39:17 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	entity_visible(t_data *data, t_entity *entity)
{
	float angle;

	angle = data->player.angle - atan2(data->player.pos.y -
				entity->pos.y, entity->pos.x - data->player.pos.x);
	angle -= (angle > M_PI) ? M_PI * 2 : 0;
	angle += (angle < -M_PI) ? M_PI * 2 : 0;
	angle = fabs(angle);
	if (angle < (FOV / 2))
	{
		entity->visible = 1;
		entity->angle = angle;
		entity->distance = hit_distance(entity->pos.x, entity->pos.y,
					data->player.pos.x, data->player.pos.y);
	}
	else
		entity->visible = 0;
}

void	draw_hud_entity(t_data *data, t_entity *entity)
{
	t_crd	pos;
	int		color;

	color = entity->visible ? 0x00FF0000 : 0x00FFFF00;
	pos.x = entity->pos.x / TILE_SIZE *
		((data->cfg.r.x / MAP_RATIO) / data->cfg.map_size.x) + 10;
	pos.y = entity->pos.y / TILE_SIZE *
		((data->cfg.r.x / MAP_RATIO) / data->cfg.map_size.x) + 10;
	data->frame.addr[pos.y * data->frame.line_length / 4 +
						pos.x] = color;
	data->frame.addr[pos.y * data->frame.line_length / 4 +
						(pos.x - 1)] = color;
	data->frame.addr[pos.y * data->frame.line_length / 4 +
						(pos.x + 1)] = color;
	data->frame.addr[(pos.y - 1) * data->frame.line_length / 4 +
						pos.x] = color;
	data->frame.addr[(pos.y + 1) * data->frame.line_length / 4 +
						pos.x] = color;
}

void	draw_entity(t_data *data, t_entity *entity)
{
	float	height;
	float	width;
	float	top;
	float	tmp_top;
	float	bottom;
	float	angle;
	float	x_pos;
	float	sprite_left;
	float	sprite_right;
	float	ratio_x;
	float	ratio_y;
	int		color;

	if (entity->visible)
	{
		height = (TILE_SIZE * 3 / entity->distance) * (data->cfg.r.x / 2) * tan(FOV / 2);
		width = height;
		top = (data->cfg.r.y / 2) - (height / 2);
		tmp_top = top;
		top = (top < 0) ? 0 : top;
		bottom = (data->cfg.r.y / 2) + (height / 2);
		bottom = (bottom > data->cfg.r.y) ? data->cfg.r.y : bottom;
		angle = atan2(entity->pos.y - data->player.pos.y, entity->pos.x - data->player.pos.x) + data->player.angle;
		x_pos = tan(angle) * (data->cfg.r.x / 2) * tan(FOV / 2) * 3;
		sprite_left = (data->cfg.r.x / 2) + x_pos - (width / 2);
		sprite_right = sprite_left + width;

		for (int y = top; y < bottom; y++)
		{
			for (int x = sprite_left; x < sprite_right; x++)
			{
				if (x > 0 && x < data->cfg.r.x && y > 0 && y < data->cfg.r.y && data->rays[x].distance > entity->distance)
				{
					ratio_x = (float)TILE_SIZE / height;
					ratio_y = (float)TILE_SIZE / width;
					int y_offset = (int)((y - tmp_top) * ratio_y);
					int x_offset = (int)((x - sprite_left) * ratio_x);
					color = data->textures[4].addr[y_offset * data->textures[4].line_length / 4 + x_offset];
					if (color != 0x00ff38cb && y_offset > 0)
						data->frame.addr[(y * data->frame.line_length) / 4 + x] = color;
				}
			}
		}
	}
}

void	ft_entityiter(t_data *data, t_list *lst,
						void (*f)(t_data *, t_entity *))
{
	if (lst)
	{
		f(data, lst->content);
		ft_entityiter(data, lst->next, f);
	}
}

void	update_entities(t_data *data)
{
	ft_entityiter(data, data->entities, entity_visible);
}

void	init_entities(t_data *data)
{
	size_t		x;
	size_t		y;
	t_entity	*entity;

	y = -1;
	while (++y < data->cfg.map_size.y)
	{
		x = -1;
		while (++x < data->cfg.map_size.x)
		{
			if (ft_strchr(ENTITY, data->cfg.map[y][x]))
			{
				if (!(entity = malloc(sizeof(t_entity))))
					exit_failure(data, "Malloc failed");
				entity->angle = M_PI;
				entity->pos.x = (x * TILE_SIZE) + (TILE_SIZE / 2);
				entity->pos.y = (y * TILE_SIZE) + (TILE_SIZE / 2);
				entity->visible = 0;
				ft_lstadd_front(&data->entities, ft_lstnew(entity));
			}
		}
	}
}
