/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: f██████ <f██████@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:58:30 by y██████          #+#    #+#             */
/*   Updated: 2024/06/18 07:41:28 by f██████          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
	Game loop.
	Every time there is a keyboard hook (W, A, S, D, RIGHT and LEFT ARROWS),
	this function gets triggered and render a new image with new calculation.
*/
int	update(t_data *data)
{
	int			x;
	t_player	*p;

	player_action(&(*data));
	floor_and_ceiling(&(*data));
	x = 0;
	while (x < (*data).win_size.win_w)
	{
		step_and_player_to_grid(&(*data), x);
		dda(&(*data), x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}
