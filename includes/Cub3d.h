/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:11:00 by moel-fat          #+#    #+#             */
/*   Updated: 2024/08/01 08:12:17 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
// # include <mlx.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdbool.h>
# include "../libft/libft.h"

typedef struct s_data
{
	char			*data;
	struct s_data	*next;
} t_data;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}t_color;

typedef struct s_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_color floor;
	t_color ceiling;
	char	**map;
	char 	**v_map;
	int		height;
	int		width;
	int		map_fd;
	t_data	*data;
}t_map;

//** tools **// 

int		ft_lstsizemap(t_data *lst);
t_data	*ft_lstlastmap(t_data *lst);
t_data	*ft_lstnewmap(char *data);
void	ft_lstadd_backmap(t_data **lst, t_data *new);


#endif