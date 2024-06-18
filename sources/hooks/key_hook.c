/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: f██████ <f██████@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:58:27 by f██████           #+#    #+#             */
/*   Updated: 2024/06/18 07:41:28 by f██████          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	keydown_hook(int keycode, t_data *data)
{
	set_action(keycode, data);
	return (0);
}

int	keyup_hook(int keycode, t_data *data)
{
	if (keycode != KEY_ESC)
		unset_action(keycode, data);
	else
		exit_game(&(*data));
	return (0);
}

void	hook_key_register(t_data *data)
{
	if (ft_strcmp(OS, "linux") == 0)
	{
		mlx_hook(data->mlx_win, 2, 1L << 0, keydown_hook, data);
		mlx_hook(data->mlx_win, 3, 1L << 1, keyup_hook, data);
	}
	else if (ft_strcmp(OS, "macos") == 0)
	{
		mlx_hook(data->mlx_win, 2, 0, keydown_hook, data);
		mlx_key_hook(data->mlx_win, keyup_hook, data);
	}
	mlx_hook(data->mlx_win, 17, 0, exit_game, data);
}
