/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y██████ <y██████@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:58:53 by y██████          #+#    #+#             */
/*   Updated: 2023/02/20 15:58:54 by y██████         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_up_image(t_data *data)
{
	(*data).mlx = mlx_init();
	if (!(*data).mlx)
		exit(0);
	(*data).win_size.win_w = SCREEN_WIDTH;
	(*data).win_size.win_h = SCREEN_HEIGHT;
	(*data).mlx_win = mlx_new_window((*data).mlx, \
		(*data).win_size.win_w, (*data).win_size.win_h, "Cub3d");
	if (!(*data).mlx_win)
		exit(0);
	(*data).img = mlx_new_image((*data).mlx, (*data).win_size.win_w, \
		(*data).win_size.win_h);
	if (!(*data).img)
		exit(0);
	(*data).addr = mlx_get_data_addr((*data).img, &(*data).bits_per_pixel, \
		&(*data).line_length, &(*data).endian);
	if (!(*data).addr)
		exit(0);
}
