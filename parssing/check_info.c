/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:59:05 by tkurukul          #+#    #+#             */
/*   Updated: 2025/07/01 01:21:18 by tkurukul         ###   ########.fr       */
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
	close(fd);
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
	close(fd);
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
	if (!flag)
		return (false);
	return (true);
}

int	fill_map(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	info->count = 0;
	while (info->file[i] && !map_only(info->file[i]))
		i++;
	if (!info->file[i])
		return (ft_printf(2, "Error: File is missing the map.\n"));
	j = i;
	while (info->file[j])
	{
		j++;
		info->count++;
	}
	info->map = malloc((info->count + 1) * sizeof(char *));
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

char	*ft_mapdup(const char *s, t_info *info)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc((info->max + 3) * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = 'X';
	while (i < (info->max + 2))
	{
		if (s[i + 1] == '\0')
		{
			str[i + 1] = 'X';
			while (i < (info->max + 1))
			{
				str[i + 1] = 'X';
				i++;
			}
			str[i + 1] = '\n';
			str[i + 2] = '\0';
			break;
		}
		else if ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
			str[i + 1] = 'X';
		else
			str[i + 1] = s[i];
		i++;
	}
	return str;
}

char	*x_fill(t_info *info)
{
	int	i;
	int	len;
	char	*str;

	i = -1;
	info->max = 0;
	len = 0;
	while (info->map[++i])
	{
		len = ft_strlen(info->map[i]);
		if (len > info->max)
			info->max = len + 1;
	}
	str = malloc((info->max + 4) * sizeof(char));
	if (!str)
		return (ft_printf(2, "Error: malloc failed.\n"), NULL);
	i = -1;
	while (++i < (info->max + 2))
		str[i] = 'X';
	str[i] = '\n';
	str[i + 1] = '\0';
	return (str);
}
int	fill_tmp(t_info *info)
{
	int	i;

	i = -1;
	info->tmp = malloc((info->count + 3) * sizeof (char *));
	if (!info->tmp)
		return (ft_printf(2, "Error: malloc failed.\n"));
	info->tmp[0] = x_fill(info);
	while (info->map[++i])
	{
		info->tmp[i + 1] = ft_mapdup(info->map[i], info);
		if (!info->map[i + 1])
			info->tmp[i + 2] = x_fill(info);
	}
	info->tmp[i + 2] = NULL;
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
	// print_matrix(info.map);
	if (fill_tmp(&info))
		return (1);
	print_matrix(info.tmp);
	free_mat(info.tmp);
	free_mat(info.map);
	free_mat(info.file);
}
