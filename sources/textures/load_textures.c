/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y██████ <y██████@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:59:18 by y██████          #+#    #+#             */
/*   Updated: 2023/02/20 15:59:19 by y██████         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	load_textures(t_data *data)
{
	if (load_texture(&(*data), (*data).map_info.so, 0) == 0)
		return (0);
	if (load_texture(&(*data), (*data).map_info.no, 1) == 0)
		return (0);
	if (load_texture(&(*data), (*data).map_info.ea, 2) == 0)
		return (0);
	if (load_texture(&(*data), (*data).map_info.we, 3) == 0)
		return (0);
	return (1);
}

int	load_texture(t_data *data, char *texture_path, int text_num)
{
	(*data).texture[text_num].text = \
		mlx_xpm_file_to_image((*data).mlx, texture_path, \
		&(*data).texture[text_num].width_img, \
		&(*data).texture[text_num].height_img);
	if (!(*data).texture[text_num].text)
		return (0);
	(*data).texture[text_num].text_adr = \
	mlx_get_data_addr((*data).texture[text_num].text, \
	&(*data).texture[text_num].bits_per_pixel, \
	&(*data).texture[text_num].line_length, \
	&(*data).texture[text_num].endian);
	if (!(*data).texture[text_num].text_adr)
		return (0);
	return (1);
}
