/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_element_parsing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: f██████ <f██████@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:58:56 by f██████           #+#    #+#             */
/*   Updated: 2024/06/18 07:41:28 by f██████          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
	First while: Find the first occurrence of a non-digit 
		character followed by a digit
*/
void	parse_floor_color(t_data *data, char *line)
{
	char	**rgb_colors_f;
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_isdigit(line[i]) && ft_isdigit(line[i + 1]))
			break ;
		i++;
	}
	rgb_colors_f = ft_split(&line[i], ',');
	free(line);
	i = -1;
	while (rgb_colors_f[++i])
	{
		(*data).map_info.f[i] = ft_atoi(rgb_colors_f[i]);
		free(rgb_colors_f[i]);
	}
	free(rgb_colors_f);
	(*data).parsing.count_identifiers++;
}

/*
	First while: Find the first occurrence of a non-digit 
		character followed by a digit
*/
void	parse_ceiling_color(t_data *data, char *line)
{
	char	**rgb_colors_c;
	int		j;

	j = -1;
	while (line[++j] != '\0')
		if (!ft_isdigit(line[j]) && ft_isdigit(line[j + 1]))
			break ;
	rgb_colors_c = ft_split(&line[j], ',');
	free(line);
	j = -1;
	while (rgb_colors_c[++j])
	{
		if (ft_atoi(rgb_colors_c[j]) < 0 || ft_atoi(rgb_colors_c[j]) > 255)
		{
			printf("%s\n", "R,G,B colors in range [0,255]");
			exit(0);
		}
		(*data).map_info.c[j] = ft_atoi(rgb_colors_c[j]);
		free(rgb_colors_c[j]);
	}
	free(rgb_colors_c);
	(*data).parsing.count_identifiers++;
}
