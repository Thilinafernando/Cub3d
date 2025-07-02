/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 03:05:56 by tkurukul          #+#    #+#             */
/*   Updated: 2025/07/02 03:10:06 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	paths_check(t_info *info, int i, int j, char *str)
{
	if (!ft_strncmp(info->file[i], "NO", 2) || !ft_strncmp(info->file[i], "SO", 2) || !ft_strncmp(info->file[i], "WE", 2)
		|| !ft_strncmp(info->file[i], "EA", 2) || !ft_strncmp(info->file[i], "F", 1) || !ft_strncmp(info->file[i], "C", 1))
	{
		j = 1;
		ft_strlcpy(str, info->file[i], 3);
		while (info->file[i][++j] != '\0')
		{
			if ((info->file[i][j] >= 9 && info->file[i][j] <= 13) || info->file[i][j] == 32)
				j++;
			else
				break;
		}
		if (info->file[i][j] == '\0')
			return (ft_printf(2, "Error: %s info not included in the file.\n", str));
		if (ft_strncmp(info->file[i], "F", 1) && ft_strncmp(info->file[i], "C", 1) && save_path(str, info, i, j))
			return (-1);
		else if ((!ft_strncmp(info->file[i], "F", 1) || !ft_strncmp(info->file[i], "C", 1)) && rgb_convertion(info, str, i, j))
			return (-1);
	}
	return (0);
}

int	paths(t_info *info)
{
	int		i;
	int		j;
	char	str[3];

	i = -1;
	ft_bzero(str, 3);
	while (info->file[++i])
	{
		if (paths_check(info, i, j, str) == -1)
			return (-1);
	}
	if (!info->ea || !info->no || !info->so || !info->we)
		return (ft_printf(2, "Error: Not all textures are included in the file.\n"));
	return (0);
}
