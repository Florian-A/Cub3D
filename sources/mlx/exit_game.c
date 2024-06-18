/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y██████ <y██████@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:58:38 by y██████          #+#    #+#             */
/*   Updated: 2023/02/20 15:58:39 by y██████         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	exit_game(t_data *data)
{
	int	i;

	mlx_destroy_image((*data).mlx, (*data).img);
	mlx_destroy_window((*data).mlx, (*data).mlx_win);
	free((*data).map_info.no);
	free((*data).map_info.so);
	free((*data).map_info.we);
	free((*data).map_info.ea);
	free((*data).map_info.f);
	free((*data).map_info.c);
	i = 0;
	while (i < (*data).parsing.map_height + 2)
		free((*data).map_info.map[i++]);
	free((*data).map_info.map);
	exit(0);
}
