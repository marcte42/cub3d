/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 14:08:41 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/03/27 14:08:46 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		*get_texture_addr(t_data *data, int n)
{
	return ((int *)mlx_get_data_addr(data->textures[n].ptr,
										&data->textures[n].bpp,
										&data->textures[n].line_length,
										&data->textures[n].endian));
}

void	*get_texture_ptr(t_data *data, int n)
{
	return (mlx_xpm_file_to_image(data->mlx.ptr, data->cfg.textures[n],
	&data->textures[n].width, &data->textures[n].height));
}

void	init_textures(t_data *data)
{
	if (!(data->textures[0].ptr = get_texture_ptr(data, 0)))
		exit_failure(data, "Unable to load texture");
	data->textures[0].addr = get_texture_addr(data, 0);
	if (!(data->textures[1].ptr = get_texture_ptr(data, 1)))
		exit_failure(data, "Unable to load texture");
	data->textures[1].addr = get_texture_addr(data, 1);
	if (!(data->textures[2].ptr = get_texture_ptr(data, 2)))
		exit_failure(data, "Unable to load texture");
	data->textures[2].addr = get_texture_addr(data, 2);
	if (!(data->textures[3].ptr = get_texture_ptr(data, 3)))
		exit_failure(data, "Unable to load texture");
	data->textures[3].addr = get_texture_addr(data, 3);
	if (!(data->textures[4].ptr = get_texture_ptr(data, 4)))
		exit_failure(data, "Unable to load texture");
	data->textures[4].addr = get_texture_addr(data, 4);
}
