/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:22:48 by moel-fat          #+#    #+#             */
/*   Updated: 2024/09/17 17:42:01 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

void free_array(char **array)
{
	int i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void free_map(t_map *map)
{
    t_data *current;
    t_data *next;
    
    if (map == NULL)
        return;
    current = map->data;
    while (current != NULL)
    {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
	if (map != NULL)
		free_array(map->map);
	free_array(map->v_map);
    free(map->no);
    free(map->so);
    free(map->we);
    free(map->ea);
    free(map);
}

void	ft_error(t_map *map, int flag)
{
	if (flag == 1 )
		ft_putstr_fd("Error\nNeed The Map path as second arg and no more", 2);
	else if (flag == 2)
		ft_putstr_fd("Error\nNo Map Exists OR Invalid File Extension", 2);
	else if (flag == 3)
		ft_putstr_fd("Error\nMap is not closed by walls or have extra elemnet", 2);
	else if (flag == 4)
		ft_putstr_fd("Error\nunwanted elemnet in the file", 2);
	else if (flag == 5)
		ft_putstr_fd("Error\nfound empty line in inside the map", 2);
	else if (flag == 6)
		ft_putstr_fd("Error\nInvalid RGB value must be between 0 and 255 with no spaces", 2);
	else if (flag == 7)
		ft_putstr_fd("Error\nInvalid arguments for RGB format", 2);
	else if (flag == 8)
		ft_putstr_fd("Error\nplayer not found or wrong dericetion", 2);
	else if (flag == 9)
		ft_putstr_fd("Error\nmalloc fail\n", 2);
	else if (flag == 10)
		ft_putstr_fd("Error\nInvalid Texture Path or permition \n", 2);
	else if (flag == 11)
		ft_putstr_fd("Error\nColors are missing or missmatch\n", 2);
	if(map != NULL)
		free_map(map);//TODO update to free everything after;
	exit(EXIT_FAILURE);
}

void ft_print_error(t_map *map, char *str, int flag)
{
	ft_putstr_fd("Error\n", 2);
	if (str != NULL && flag == -1)
		ft_putstr_fd(str, 2);
	ft_error(map, flag);
}

void	*safe_malloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

char *remove_new_line(char *str)
{
	int i = 0;
	char *tmp;

	if (str == NULL)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	tmp = ft_strndup(str, i);
	free(str);
	return (tmp);
}

bool is_just_spaces(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\n')
			return false;
		i++;
	}
	return true;
}
