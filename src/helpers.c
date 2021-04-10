/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:13:52 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/04/10 12:45:30 by marcte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	normalize_angle(float angle)
{
	if (angle < 0)
		angle += M_PI * 2;
	else if (angle > M_PI * 2)
		angle -= M_PI * 2;
	return (angle);
}

int		is_wall(t_data *data, float x, float y)
{
	if (ft_strchr("1 ", data->cfg.map[(int)y / TILE_SIZE][(int)x / TILE_SIZE]))
		return (1);
	return (0);
}

float	hit_distance(float p1_x, float p1_y, float p2_x, float p2_y)
{
	float	x;
	float	y;

	x = p1_x - p2_x;
	if (x < 0)
		x *= -1;
	y = p1_y - p2_y;
	if (y < 0)
		y *= -1;
	return (sqrtf(pow(x, 2) + pow(y, 2)));
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
