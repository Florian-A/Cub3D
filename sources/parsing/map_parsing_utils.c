/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: f██████ <f██████@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:59:04 by f██████           #+#    #+#             */
/*   Updated: 2024/06/18 07:41:28 by f██████          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_map_height_max_width(t_data *data, char *map_file)
{
	char	*line;
	int		fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
	{
		printf("%s\n", "The map does not exist.");
		exit(EXIT_FAILURE);
	}
	(*data).parsing.count_identifiers = 0;
	(*data).parsing.map_max_width = 0;
	(*data).parsing.map_height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strlen(line) > (*data).parsing.map_max_width)
			(*data).parsing.map_max_width = ft_strlen(line);
		if ((ft_strchr(line, '0') != 0 || ft_strchr(line, '1') != 0) && \
			ft_strnstr(line, "./", ft_strlen(line)) == 0 && \
			ft_strchr(line, ',') == 0)
			(*data).parsing.map_height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	check_extension_cub(char *map_file)
{
	size_t	len;

	len = ft_strlen(map_file);
	if (len < 4 || ft_strcmp(map_file + len - 4, ".cub") != 0)
	{
		printf("%s\n", "Error: file name of the map does not end with .cub");
		exit(EXIT_FAILURE);
	}
}

/*
	(*data).parsing.map_height + 2) // +2 for two extra lines of h
*/
int	malloc_data_info(t_data *data)
{
	(*data).map_info.f = ft_calloc(sizeof(int *), 3);
	if (!(*data).map_info.f)
		return (0);
	(*data).map_info.c = ft_calloc(sizeof(int *), 3);
	if (!(*data).map_info.c)
		return (0);
	(*data).map_info.map = ft_calloc(sizeof(char *), \
		(*data).parsing.map_height + 2);
	if (!(*data).map_info.map)
		return (0);
	(*data).map_info.map[0] = ft_calloc(sizeof(char), \
		(*data).parsing.map_max_width + 3);
	if (!(*data).map_info.map[0])
		return (0);
	(*data).map_info.map[(*data).parsing.map_height + 1] = \
		ft_calloc(sizeof(char), (*data).parsing.map_max_width + 3);
	if (!(*data).map_info.map[(*data).parsing.map_height + 1])
		return (0);
	return (1);
}
