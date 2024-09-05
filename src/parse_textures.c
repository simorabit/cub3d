/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texturs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:28:43 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/05 16:36:38 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

char *check_texture(char *str)
{
	char **tmp;
	int fd;
	
	if (str == NULL )
	{
		ft_putstr_fd("Error\nMissing Texture Path\n", 2);
		return (NULL);
	}
	tmp = ft_split(str, ' ');
	if (tmp[1] == NULL)
	{
		free_array(tmp);
		ft_putstr_fd("Error\nInvalid Texture path\n", 2);
		return (NULL);
	}
	free(str);
	str = NULL;
	str = ft_strndup(tmp[1], ft_strlen(tmp[1]) - 1);
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		free_array(tmp);
		ft_putstr_fd("Error\nInvalid Texture Path or permition \n", 2);
		close(fd);
		return (NULL);
	}
	close(fd);
	free_array(tmp);
	return (str);
}
