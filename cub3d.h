/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:00:08 by tkurukul          #+#    #+#             */
/*   Updated: 2025/07/03 19:54:07 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include "libft/libft.h"
# include "libprintf/ft_printf.h"
# include "get_next_line/get_next_line.h"

# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>

typedef struct s_info
{
	char	**file;
	char	**map;
	int		count;
	int		max;
	char	**tmp;
	int		player_x;
	int		player_y;
	int		flood_flag;
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	int		rgb_f;
	int		rgb_c;
}	t_info;

//parssing
bool	extention_check(char *str);
int		paths_conditions(t_info *info, int i, int j, char *str);
int		fill_file(char *map, t_info *info);
int		fill_map(t_info *info);
int		validate_map(t_info *info);
int		paths_check(t_info *info, int i, char *str);
int		check_spaces(t_info *info);
int		paths(t_info *info);
int		count_lines(char *map);
bool	map_only(char *str);
char	*ft_mapdup(const char *s, t_info *info);
char	*x_fill(t_info *info);
int		fill_tmp(t_info *info);
void	print_matrix(char **matrix);
int		find_player_pos(char **matrix, t_info *info);
bool	verify_char(char c);
void	flood_fill(int x, int y, t_info *info);
int		check_playable(t_info *info);
int		check_characters(t_info *info);
char	*ft_mydup(const char *s);
void	init_struct(t_info *info);
int		rgb_convertion(t_info *info, char *str, int i, int j);
int		save_path(char *str, t_info *info, int i, int j);
void	free_all(t_info *info);

#endif
