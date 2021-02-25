/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:59:57 by mterkhoy          #+#    #+#             */
/*   Updated: 2021/02/26 00:16:21 by mterkhoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	int_to_buff(int data, unsigned char *buffer)
{
	buffer[0] = (unsigned char)(data);
	buffer[1] = (unsigned char)(data >> 8);
	buffer[2] = (unsigned char)(data >> 16);
	buffer[3] = (unsigned char)(data >> 24);
}

void	bmp_header(t_data *data, unsigned char *buffer, int size)
{
	buffer[0] = (unsigned char)'B';
	buffer[1] = (unsigned char)'M';
	int_to_buff(size, &buffer[2]);
	buffer[10] = (unsigned char)54;
	buffer[14] = (unsigned char)40;
	int_to_buff(data->cfg.r.x, &buffer[18]);
	int_to_buff(data->cfg.r.y, &buffer[22]);
	buffer[26] = (unsigned char)1;
	buffer[28] = (unsigned char)32;
}

void	color_table(t_data *data, unsigned char *buffer, int padding)
{
	int		i;
	int		j;
	int		color;
	size_t	index;
	int		pad;

	index = 0;
	i = data->cfg.r.y;
	while (--i >= 0)
	{
		j = -1;
		while (++j < data->cfg.r.x)
		{
			color = data->frame.addr[i * data->frame.line_length / 4 + j];
			int_to_buff(color, &buffer[index]);
			index += 4;
		}
		pad = padding;
		while (--pad >= 0)
		{
			buffer[index] = 0;
			index++;
		}
	}
}

void	save(t_data *data)
{
	unsigned char	*buffer;
	int				fd;
	size_t			img_size;
	int				padding;

	if (!(fd = open("save.bmp", O_RDWR | O_CREAT | O_TRUNC, 0666)))
		exit_failure(data, "System error");
	padding = (data->cfg.r.x * 4) % 4;
	img_size = 54 + (data->cfg.r.x * data->cfg.r.y * 4)
							+ (padding * data->cfg.r.y);
	if (!(buffer = malloc(img_size * sizeof(char))))
		exit_failure(data, "Malloc failed");
	ft_bzero(buffer, img_size);
	bmp_header(data, buffer, img_size);
	color_table(data, &buffer[54], padding);
	if (!(write(fd, buffer, img_size)))
		exit_failure(data, "System error");
	close(fd);
	free(buffer);
}
