/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: f██████ <f██████@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:58:59 by f██████           #+#    #+#             */
/*   Updated: 2024/06/18 07:41:28 by f██████          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	elem_and_start_pos(t_data *data, char *line)
{
	if ((*data).parsing.count_identifiers != 6)
	{
		free(line);
		printf("%s\n", "Wrong number of elements.");
		return (0);
	}
	if ((*data).map_info.pos_start_count != 1)
	{
		printf("%s\n", "Cannot have none or multiple starting positions.");
		return (0);
	}
	return (1);
}

/*
	(*data).parsing.count_identifiers == 6 // All identifiers are parsed
*/
static int	iterate_over_file(t_data *data, char *l, int *i)
{
	if (ft_strnstr(l, "NO", ft_strlen(l)) != 0)
		parse_texture_no(data, l);
	else if (ft_strnstr(l, "SO", ft_strlen(l)) != 0)
		parse_texture_so(data, l);
	else if (ft_strnstr(l, "WE", ft_strlen(l)) != 0)
		parse_texture_we(data, l);
	else if (ft_strnstr(l, "EA", ft_strlen(l)) != 0)
		parse_texture_ea(data, l);
	else if (ft_strnstr(l, "F", ft_strlen(l)) != 0)
		parse_floor_color(data, l);
	else if (ft_strnstr(l, "C", ft_strlen(l)) != 0)
		parse_ceiling_color(data, l);
	else if ((*data).parsing.count_identifiers == 6 && \
		(ft_strnstr(l, "0", ft_strlen(l)) != 0 || \
			ft_strnstr(l, "1", ft_strlen(l)) != 0))
	{
		if (!parse_map(data, l, &(*i)))
			return (0);
		(*i)++;
	}
	else
		free(l);
	return (1);
}

static int	parse_map_file(t_data *data, char *map_file)
{
	char	*l;
	int		fd;
	int		i;

	i = 1;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
	{
		printf("%s\n", "The map does not exist.");
		exit(EXIT_FAILURE);
	}
	l = get_next_line(fd);
	while (l != NULL)
	{
		if (!iterate_over_file(data, l, &i))
			return (0);
		l = get_next_line(fd);
	}
	if (!elem_and_start_pos(data, l))
		return (0);
	close(fd);
	return (1);
}

int	parsing_main(t_data *data, char **argv)
{
	(*data).map_info.pos_start_count = 0;
	check_extension_cub(argv[1]);
	get_map_height_max_width(data, argv[1]);
	if (!malloc_data_info(data))
		return (0);
	add_extra_top_bottom_borders(data);
	if (!parse_map_file(data, argv[1]))
		return (0);
	if (!is_the_map_surrounded_by_walls(data))
		return (0);
	return (1);
}
