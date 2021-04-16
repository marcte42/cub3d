/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 13:44:24 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/04/15 21:29:07 by marcte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_entities(t_list *lst)
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
			if (entity->visible && entity_next->visible
			&& entity->distance < entity_next->distance)
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

void	draw_texel(t_data *data, t_entity *entity, size_t x, size_t y)
{
	int		texel;
	int		x_offset;
	int		y_offset;

	if (x > 0 && x < data->cfg.r.x && y > 0
		&& y < data->cfg.r.y && data->rays[x].distance > entity->distance)
	{
		y_offset = (int)((y - (int)entity->real_top) * entity->ratio.y);
		x_offset = (int)((x - (int)entity->sprite_left) * entity->ratio.x);
		texel = data->textures[4].addr[y_offset * data->textures[4].line_length
			/ 4 + x_offset];
		if (texel != 0x00ff38cb)
			data->frame.addr[(y * data->frame.line_length) / 4 + x] = texel;
	}
}

void	process_entity(t_data *data, t_entity *entity)
{
	entity->size = (((float)TILE_SIZE * 3)
		/ entity->distance) * (data->cfg.r.x / 2) * tan(FOV / 2);
	entity->top = (data->cfg.r.y / 2) - (entity->size / 2);
	entity->real_top = entity->top;
	entity->top = (entity->top < 0) ? 0 : entity->top;
	entity->bottom = (data->cfg.r.y / 2) + (entity->size / 2);
	entity->bottom = (entity->bottom > data->cfg.r.y)
		? data->cfg.r.y : entity->bottom;
	entity->sprite_left = (data->cfg.r.x / 2)
		+ tan(atan2(entity->pos.y - data->player.pos.y, entity->pos.x
		- data->player.pos.x) + data->player.angle)
		* (data->cfg.r.x / 2) * tan(FOV / 2) * 3 - (entity->size / 2);
	entity->sprite_right = entity->sprite_left + entity->size;
	entity->ratio.x = (float)data->textures[4].width / entity->size;
	entity->ratio.y = (float)data->textures[4].height / entity->size;
}

void	draw_entity(t_data *data, t_entity *entity)
{
	int		x;
	int		y;

	if (entity->visible)
	{
		process_entity(data, entity);
		y = entity->top + 1;
		while (y < entity->bottom - 1)
		{
			x = entity->sprite_left;
			while (x < entity->sprite_right)
			{
				draw_texel(data, entity, x, y);
				x++;
			}
			y++;
		}
	}
}

void	draw_entities(t_data *data)
{
	sort_entities(data->entities);
	ft_entityiter(data, data->entities, draw_entity);
}
