/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:00:08 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/30 19:52:49 by tkurukul         ###   ########.fr       */
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
	char	**tmp;
	char	*north_w;
	char	*south_w;
	char	*east_w;
	char	*west_w;
	int		rgb_f;
	int		rgb_c;
} t_info;

//parssing



#endif
