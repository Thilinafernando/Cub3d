/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:59:05 by tkurukul          #+#    #+#             */
/*   Updated: 2025/07/01 23:24:12 by tkurukul         ###   ########.fr       */
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
	{
		ft_printf(2, "Error: Invalid map, \".cub\" extention needed.\n");
		return (false);
	}
	else
	{
		str = &str[i + 1];
		if (ft_strcmp(str, "cub"))
		{
			ft_printf(2, "Error: Incorrect extention.\n");
			return (false);
		}
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
		return (ft_printf(2, "Error: Open failed.\n"));
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
		return (ft_printf(2, "Error: Open failed.\n"));
	size = count_lines(map);
	info->file = malloc((size + 1) * sizeof(char *));
	if (!info->file)
		return (ft_printf(2, "Error: Malloc failed.\n"));
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
	if (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2) || !ft_strncmp(str, "WE", 2)
			|| !ft_strncmp(str, "EA", 2) || !ft_strncmp(str, "F", 1) || !ft_strncmp(str, "C", 1)
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
	j = i - 1;
	while (info->file[++j])
		info->count++;
	info->map = malloc((info->count + 1) * sizeof(char *));
	if (!info->map)
		return (ft_printf(2, "Error: Malloc failed.\n"));
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

	i = -1;
	str = malloc((info->max + 3) * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = 'X';
	while (++i < (info->max + 2))
	{
		if (s[i + 1] == '\0')
		{
			str[i + 1] = 'X';
			while (++i < (info->max))
				str[i + 1] = 'X';
			str[i + 1] = '\n';
			str[i + 2] = '\0';
			break;
		}
		else if ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
			str[i + 1] = 'X';
		else
			str[i + 1] = s[i];
	}
	return (str);
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
	str = malloc((info->max + 3) * sizeof(char));
	if (!str)
		return (ft_printf(2, "Error: Malloc failed.\n"), NULL);
	i = -1;
	while (++i < (info->max + 1))
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
		return (ft_printf(2, "Error: Malloc failed.\n"));
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

int	find_player_pos(char **matrix, t_info *info)
{
	int		y;
	int		x;
	int		flag;

	y = -1;
	flag = 0;
	while (matrix[++y])
	{
		x = -1;
		while (matrix[y][++x])
		{
			if (matrix[y][x] == 'W' || matrix[y][x] == 'E'
				|| matrix[y][x] == 'N' || matrix[y][x] == 'S')
			{
				info->player_y = y;
				info->player_x = x;
				flag++;
			}
		}
	}
	if (flag != 1)
		return (-1);
	return (0);
}

bool	verify_char(char c)
{
	if (c == '1' || c == 'Z' || c == '\0' || c == '\n' || !c)
		return (false);
	return (true);
}

void	flood_fill(int x, int y, t_info *info)
{
	if (y < 0 || x < 0 || !info->tmp[y] || x >= (int)ft_strlen(info->tmp[y]))
		return ;
	if (info->tmp[y][x] == '0' || info->tmp[y][x] == 'W' || info->tmp[y][x] == 'E'
		|| info->tmp[y][x] == 'S' || info->tmp[y][x] == 'N')
	{
		info->flood_flag = -42;
		return ;
	}
	info->tmp[y][x] = 'Z';
	if (info->tmp[y][x + 1] && verify_char(info->tmp[y][x + 1]))
		flood_fill(x + 1, y, info);
	if (x != 0 && info->tmp[y][x - 1] && verify_char(info->tmp[y][x - 1]))
		flood_fill(x - 1, y, info);
	if (info->tmp[y + 1] && verify_char(info->tmp[y + 1][x]))
		flood_fill(x, y + 1, info);
	if (y != 0 && info->tmp[y - 1] && verify_char(info->tmp[y - 1][x]))
		flood_fill(x, y - 1, info);
	return ;
}

int		validate_map(t_info *info)
{
	if (fill_tmp(info))
		return (-1);
	flood_fill(0, 0, info);
	if (info->flood_flag == -42)
		return(ft_printf(2, "Error: Map not closed.\n"));
	print_matrix(info->tmp);
	free_mat(info->tmp);
	info->tmp = NULL;
	ft_printf(1, "Map is closed!\n");
	return (0);
}

char	*ft_mydup(const char *s)
{
	int		i;
	int		a;
	char	*str;

	i = 0;
	a = 0;
	while (s[a] != '\0' && (!((s[a] >= 9 && s[a] <=13) || s[a] == 32)))
		a++;
	str = (char *)malloc((a + 1) * (sizeof(char)));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0' && (!((s[i] >= 9 && s[i] <=13) || s[i] == 32)))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (&str[0]);
}

void	init_struct(t_info *info)
{
	info->count = 0;
	info->no = NULL;
	info->so = NULL;
	info->ea = NULL;
	info->we = NULL;
	info->file = NULL;
	info->map = NULL;
	info->tmp = NULL;
	info->max = 0;
	info->player_x = -1;
	info->player_y = -1;
	info->flood_flag = 0;
	info->rgb_c = -42;
	info->rgb_f = -42;
}

int	save_path(char *str, t_info *info, int i, int j)
{
	char	*path;
	int		fd;

	if (!str)
		return (ft_printf(2, "Error: ft_strlcpy failed me.\n"));
	path = ft_mydup(info->file[i] + (j - 1));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_printf(2, "Error: Invalid %s texture. PATH: %s\n", str, path));
	close(fd);
	if (!ft_strcmp(str, "NO"))
		info->no = path;
	if (!ft_strcmp(str, "SO"))
		info->so = path;
	if (!ft_strcmp(str, "WE"))
		info->we = path;
	if (!ft_strcmp(str, "EA"))
		info->ea = path;
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
		if (!ft_strncmp(info->file[i], "NO", 2) || !ft_strncmp(info->file[i], "SO", 2) || !ft_strncmp(info->file[i], "WE", 2)
			|| !ft_strncmp(info->file[i], "EA", 2))
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
				return (ft_printf(2, "Error: %s texture not included in the file.\n", str));
			if (save_path(str, info, i, j))
				return (-1);
		}
	}
	if (!info->ea || !info->no || !info->so || !info->we)
		return (ft_printf(2, "Error: Not all textures are included in the file.\n"));
	ft_printf(1, "ITS A OKAY.\n");
	return (0);
}

void	free_all(t_info *info)
{
	if (info->file)
		free_mat(info->file);
	if (info->map)
		free_mat(info->map);
	if (info->tmp)
		free_mat(info->tmp);
	if (info->no)
		free(info->no);
	if (info->so)
		free(info->so);
	if (info->ea)
		free(info->ea);
	if (info->we)
		free(info->we);
}

int main(int ac, char **av)
{
	t_info	info;

	init_struct(&info);
	if (ac != 2)
		return (ft_printf(2, "Error: Invalid number of arguments for program.\n"), 1);
	if (!extention_check(av[1]))
		return (1);
	if (fill_file(av[1], &info))
		return (free_all(&info), 1);
	if (paths(&info))
		return (free_all(&info), 1);
	if (fill_map(&info))
		return (free_all(&info), 1);
	if (validate_map(&info))
		return (free_all(&info), 1);
	free_all(&info);
}
