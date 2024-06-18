/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: f██████ <f██████@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:59:10 by f██████           #+#    #+#             */
/*   Updated: 2024/06/18 07:41:28 by f██████          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// get action code
int	get_action_keycode(int keycode)
{
	if (keycode == LETTER_KEY_MOVE_LEFT)
		return (1);
	else if (keycode == LETTER_KEY_MOVE_RIGHT)
		return (2);
	else if (keycode == ARROW_KEY_MOVE_FORWARD || \
	keycode == LETTER_KEY_MOVE_FORWARD)
		return (3);
	else if (keycode == ARROW_KEY_MOVE_BACKWARD || \
	keycode == LETTER_KEY_MOVE_BACKWARD)
		return (4);
	else if (keycode == ARROW_KEY_LOOK_LEFT)
		return (5);
	else if (keycode == ARROW_KEY_LOOK_RIGHT)
		return (6);
	return (0);
}

// set action
void	set_action(int keycode, t_data *data)
{
	if (data->ac[0] == 0
		|| data->ac[0] == get_action_keycode(keycode))
		data->ac[0] = get_action_keycode(keycode);
	else if (data->ac[1] == 0 || \
		data->ac[1] == get_action_keycode(keycode))
		data->ac[1] = get_action_keycode(keycode);
}

// unset action
void	unset_action(int keycode, t_data *data)
{
	if (data->ac[0] == get_action_keycode(keycode))
		data->ac[0] = 0;
	if (data->ac[1] == get_action_keycode(keycode))
		data->ac[1] = 0;
	if (data->ac[0] == 0 && data->ac[1] != 0)
	{
		data->ac[0] = data->ac[1];
		data->ac[1] = 0;
	}
}

// player action (move and look)
void	player_action(t_data *data)
{
	int	pos;

	pos = 0;
	if (data->ac[1] != 0)
		pos = 1;
	else
		pos = 0;
	if (data->ac[pos] == 1)
		move_left(&(*data));
	else if (data->ac[pos] == 2)
		move_right(&(*data));
	else if (data->ac[pos] == 3)
		move_forward(&(*data));
	else if (data->ac[pos] == 4)
		move_backward(&(*data));
	else if (data->ac[pos] == 5)
		look_left(&(*data));
	else if (data->ac[pos] == 6)
		look_right(&(*data));
}
