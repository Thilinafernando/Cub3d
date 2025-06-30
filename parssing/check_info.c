/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:59:05 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/30 20:51:18 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	extention_check(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '.')
		i++;
	if (str[i] == '\0')
		return (false);
	else
	{
		str = &str[i + 1];
		if (ft_strcmp(str, "cub"))
			return (false);
	}
	return (true);
}

int		count_lines(char *map)
{
	int		fd;
	char	*tmp;
	int		i;

	i = 0;
	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (ft_printf(2, "Error: open failed.\n"));
	tmp = get_next_line(fd);
	while (tmp)
	{
		i++;
		free (tmp);
		tmp = get_next_line(fd);
	}
	return (i);
}

int	fill_file(char *map, t_info *info)
{
	int	fd;
	int	i;
	int	size;

	i = -1;
	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (ft_printf(2, "Error: open failed.\n"));
	size = count_lines(map);
	info->file = malloc((size + 1) * sizeof(char *));
	if (!info->file)
		return (ft_printf(2, "Error: malloc failed.\n"));
	info->file[0] = get_next_line(fd);
	while (info->file[++i])
		info->file[i + 1] = get_next_line(fd);
	info->file[i] = NULL;
	return (0);
}

bool	map_only(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!strncmp(str, "NO", 2) || !strncmp(str, "SO", 2) || !strncmp(str, "WE", 2)
			|| !strncmp(str, "EA", 2) || !strncmp(str, "F", 1) || !strncmp(str, "C", 1)
			|| str[0] == '\n' || !str)
			return (false);
	else
	{
		while (str[i] != '\0')
		{
			if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
				i++;
			else if (str[i] == '1')
			{
				i++;
				flag = 1;
			}
			else
				return (false);
		}
	}
	if (!flag)
		return (false);
	return (true);
}

int	fill_map(t_info *info)
{
	int	i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (info->file[i] && !map_only(info->file[i]))
		i++;
	if (!info->file[i])
		return (ft_printf(2, "Error: File is missing the map.\n"));
	j = i;
	while (info->file[j])
	{
		j++;
		count++;
	}
	info->map = malloc((count + 1) * sizeof(char *));
	if (!info->map)
		return (ft_printf(2, "Error: malloc failed.\n"));
	j = 0;
	while (info->file[i])
	{
		info->map[j] = ft_strdup(info->file[i]);
		i++;
		j++;
	}
	info->map[j] = NULL;
	return (0);
}

void print_matrix(char **matrix)
{
	int i = 0;
	while (matrix[i] != NULL)
	{
		int j = 0;
		while (matrix[i][j] != '\0')
		{
			putchar(matrix[i][j]);
			j++;
		}
		i++;
	}
}

int main(int ac, char **av)
{
	t_info	info;

	info.map = NULL;
	info.file = NULL;
	(void)ac;
	if (!extention_check(av[1]))
		return (1);
	if (fill_file(av[1], &info))
		return (1);
	print_matrix(info.file);
	printf("\n");
	printf("\n");
	printf("map_only:\n");
	if (fill_map(&info))
		return (1);
	print_matrix(info.map);
	free_mat(info.map);
	free_mat(info.file);
}
