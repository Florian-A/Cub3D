/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: f██████ <f██████@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:59:01 by f██████           #+#    #+#             */
/*   Updated: 2024/06/18 07:41:28 by f██████          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	add_extra_top_bottom_borders(t_data *data)
{
	size_t	i;

	i = 0;
	while (i <= (*data).parsing.map_max_width)
	{
		(*data).map_info.map[0][i] = 'h';
		(*data).map_info.map[(*data).parsing.map_height + 1][i] = 'h';
		i++;
	}
	(*data).map_info.map[0][i] = '\0';
	(*data).map_info.map[(*data).parsing.map_height + 1][i] = '\0';
}

static void	orientation(t_data *data, int l, int j, char o)
{
	(*data).map_info.map[l][j] = o;
	(*data).map_info.pos_start_orientation = o;
	(*data).player.pos_x = l + 0.01;
	(*data).player.pos_y = j + 0.01;
	(*data).map_info.pos_start_count++;
}

static int	iterate_over_map_grid(t_data *data, char *l, int k, size_t *i)
{
	int	j;

	j = 0;
	while (l[*i])
	{
		if (j == 0)
		{
			(*data).map_info.map[k][0] = 'h';
			(*i)--;
		}
		else if (l[*i] == ' ')
			(*data).map_info.map[k][j] = 'h';
		else if (l[*i] == '0' || l[*i] == '1')
			(*data).map_info.map[k][j] = l[*i];
		else if (l[*i] == 'N' || l[*i] == 'S' || l[*i] == 'E' || l[*i] == 'W')
			orientation(data, k, j, l[*i]);
		else if (l[*i] != '\n')
		{
			printf("%s\n", "Possible characters: 0,1,N,S,E or W.");
			return (0);
		}
		(*i)++;
		j++;
	}
	return (1);
}

/*
	(*data).parsing.map_max_width + 3) // +2 for two extra lines of h
*/
int	parse_map(t_data *data, char *line, int *l)
{
	size_t	i;

	(*data).map_info.map[*l] = ft_calloc(sizeof(char), \
		(*data).parsing.map_max_width + 3);
	if (!(*data).map_info.map[*l])
		return (0);
	i = 0;
	if (!iterate_over_map_grid(data, line, *l, &i))
		return (0);
	free(line);
	if (line[i - 1] != '\n')
		i++;
	while (i <= (*data).parsing.map_max_width)
		(*data).map_info.map[*l][i++] = 'h';
	(*data).map_info.map[*l][i] = '\0';
	return (1);
}

int	is_the_map_surrounded_by_walls(t_data *data)
{
	int		i;
	size_t	j;

	i = -1;
	while (++i < (*data).parsing.map_height)
	{
		j = -1;
		while (++j < (*data).parsing.map_max_width)
		{
			if (((*data).map_info.map[i + 1][j + 1] == '0' || \
				(*data).map_info.map[i + 1][j + 1] == 'N' || \
				(*data).map_info.map[i + 1][j + 1] == 'S' || \
				(*data).map_info.map[i + 1][j + 1] == 'E' || \
				(*data).map_info.map[i + 1][j + 1] == 'W') && \
				((*data).map_info.map[i][j + 1] == 'h' || \
				(*data).map_info.map[i + 2][j + 1] == 'h' || \
				(*data).map_info.map[i + 1][j] == 'h' || \
				(*data).map_info.map[i + 1][j + 2] == 'h'))
			{
				printf("%s\n", "Map is invalid.");
				return (0);
			}
		}
	}
	return (1);
}
