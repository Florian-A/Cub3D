/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_element_parsing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: f██████ <f██████@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:59:07 by f██████           #+#    #+#             */
/*   Updated: 2024/06/18 07:41:28 by f██████          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	parse_texture_no(t_data *data, char *line)
{
	int	path_size;

	path_size = ft_strlen(ft_strchr(line, '.')) - 1;
	(*data).map_info.no = ft_strdup(ft_strchr(line, '.'));
	free(line);
	(*data).map_info.no[path_size] = '\0';
	(*data).parsing.count_identifiers++;
}

void	parse_texture_so(t_data *data, char *line)
{
	int	path_size;

	path_size = ft_strlen(ft_strchr(line, '.')) - 1;
	(*data).map_info.so = ft_strdup(ft_strchr(line, '.'));
	free(line);
	(*data).map_info.so[path_size] = '\0';
	(*data).parsing.count_identifiers++;
}

void	parse_texture_we(t_data *data, char *line)
{
	int	path_size;

	path_size = ft_strlen(ft_strchr(line, '.')) - 1;
	(*data).map_info.we = ft_strdup(ft_strchr(line, '.'));
	free(line);
	(*data).map_info.we[path_size] = '\0';
	(*data).parsing.count_identifiers++;
}

void	parse_texture_ea(t_data *data, char *line)
{
	int	path_size;

	path_size = ft_strlen(ft_strchr(line, '.')) - 1;
	(*data).map_info.ea = ft_strdup(ft_strchr(line, '.'));
	free(line);
	(*data).map_info.ea[path_size] = '\0';
	(*data).parsing.count_identifiers++;
}
