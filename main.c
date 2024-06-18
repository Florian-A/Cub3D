/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: f██████ <f██████@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:59:21 by y██████          #+#    #+#             */
/*   Updated: 2024/06/18 07:41:28 by f██████          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

/*
	Game loop: mlx_loop_hook

	When the ray (starting at the player's position) hits a wall, 
	the loop will stop, calculate the distance from the player's position 
	to the wall, and draw the wall with the correct height.
*/
int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		if (!parsing_main(&data, argv))
			exit(1);
		set_up_player(&data);
		set_up_image(&data);
		if (load_textures(&data) == 0)
		{
			printf("%s\n", "Invalid texture path");
			exit(1);
		}
		hook_key_register(&data);
		mlx_loop_hook(data.mlx, update, &data);
		mlx_loop(data.mlx);
	}
	else
	{
		printf("%s\n", "Wrong number of arguments");
		exit(1);
	}
	return (0);
}
