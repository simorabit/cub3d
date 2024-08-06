/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:12:50 by moel-fat          #+#    #+#             */
/*   Updated: 2024/08/06 14:55:56 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Cub3d.h"

//**chack map name if valid;

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

void free_array(char **array)
{
	int i = 0;
	if (array == NULL)
		return;
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
		ft_putstr_fd("Error\n unwanted elemnet in the file", 2);
	else if (flag == 5)
		ft_putstr_fd("Error\n found empty line in inside the map", 2);
	else if (flag == 6)
		ft_putstr_fd("Error\n Invalid RGB value must be between 0 and 255 with no spaces", 2);
	else if (flag == 7)
		ft_putstr_fd("Error\n Invalid arguments for RGB format", 2);
	
	if(map != NULL)
		free_map(map);//TODO update to free everything after;
	exit(EXIT_FAILURE);
}

int	check_map_exists(char *file_name, t_map *map)
{
	int	fd;
	int	len;

	len = ft_strlen(file_name);
	if ((len < 4) || ft_strnstr(&file_name[len - 4], ".cub", len) == NULL)
		ft_error(map, 2);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_error(map, 2);
	return (fd);
}

bool is_all_number(char *str)
{
	int	i;
	if(!str)
		return (false);
	i = 0;
	while(str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			break ;
		i++;
	}
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] != '\0')
		return (false);
	return (true);
}

void	get_rgb_value(char *rgb, t_map *map, char R)
{
	char **tmp;
	char *new_line;
	int i = 0;
	
	new_line = remove_new_line(rgb);
	tmp = ft_split(new_line + 1, ',');
	while(tmp[i] != NULL)
		i++;
	if (i != 3)
		ft_error(map, 7);
	if (R == 'F')
	{
		if(is_all_number(tmp[0]) == false)
			ft_error(map, 6);
		map->floor.r = ft_atoi(tmp[0]);
		if(is_all_number(tmp[1]) == false)
			ft_error(map, 6);
		map->floor.g = ft_atoi(tmp[1]);
		if(is_all_number(tmp[2]) == false)
			ft_error(map, 6);
		map->floor.b = ft_atoi(tmp[2]);
		if (map->floor.r < 0 || map->floor.r > 255 || map->floor.g < 0 || map->floor.g > 255 || map->floor.b < 0 || map->floor.b > 255)
			ft_error(map, 6);
	}
	else if (R == 'C')
	{
		if(is_all_number(tmp[0]) == false)
			ft_error(map, 6);
		map->ceiling.r = ft_atoi(tmp[0]);
		if(is_all_number(tmp[1]) == false)
			ft_error(map, 6);
		map->ceiling.g = ft_atoi(tmp[1]);
		if(is_all_number(tmp[2]) == false)
			ft_error(map, 6);
		map->ceiling.b = ft_atoi(tmp[2]);
		if (map->ceiling.r < 0 || map->ceiling.r > 255 || map->ceiling.g < 0 || map->ceiling.g > 255 || map->ceiling.b < 0 || map->ceiling.b > 255)
			ft_error(map, 6);
	}
	free(new_line);
	free_array(tmp);
}

void	parse_line(char *line, t_map *map, int *count)
{
	char *tmp;
	
	tmp = ft_strtrim(line, " ");
	if (ft_strncmp(tmp, "NO ", 3) == 0 && map->no == NULL)
		map->no = ft_strdup(tmp);
	else if (ft_strncmp(tmp, "SO ", 3) == 0 && map->so == NULL)
		map->so = ft_strdup(tmp);
	else if (ft_strncmp(tmp, "WE ", 3) == 0 && map->we == NULL)
		map->we = ft_strdup(tmp);
	else if (ft_strncmp(tmp, "EA ", 3) == 0 && map->ea == NULL)
		map->ea = ft_strdup(tmp);
	else if (ft_strncmp(tmp, "F ", 1) == 0)
		get_rgb_value(ft_strdup(tmp), map, 'F');
	else if (ft_strncmp(tmp, "C ", 1) == 0)
		get_rgb_value(ft_strdup(tmp), map, 'C');
	else if (ft_strncmp(tmp, "1", 1) == 0 || tmp[0] == '\n')
	{
		(*count)++;
		ft_lstadd_backmap(&map->data, ft_lstnewmap(ft_strdup(line)));
	}
	else if (tmp[0] != '\n')
	{
		free(tmp);
		ft_error(map, 4);
	}
	free(tmp);
		
}

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

void copy_map(t_map *map)
{
	t_data *current;
	int i = 0;
	char *tmp;
	
	current = map->data;
	// printf("height ->> %d\n", map->height);
	while (current != NULL && is_just_spaces(current->data) == true)
	{
		// if (current->data[0] == '\n')
		map->height--;
		current = current->next;
	}
	map->map = safe_malloc(sizeof(char *) * (map->height + 1));
	while (current != NULL)
	{
		if (current->data[0] == '\n')
			ft_error(map, 5);
		tmp = remove_new_line(ft_strdup(current->data));
		if(is_just_spaces(tmp) == true)
		{
			free(tmp);
			ft_error(map, 5);
		}
		map->map[i] = ft_strdup(tmp);
		free(tmp);
		i++;
		current = current->next;
	}
	map->map[i] = NULL;
}

void get_map_width(t_map *map)
{
	t_data *current;
	int max = 0;
	int len = 0;
	current = map->data;
	while (current != NULL)
	{
		len = ft_strlen(current->data);
		if (len > max)
			max = len;
		current = current->next;
	}
	map->width = max;
}

void fill_map(t_map *map)
{
	int	i = 0;
	int j;
	get_map_width(map);
	map->v_map = safe_malloc(sizeof(char *) * (map->height + 1));
	// printf("width ->> %d\n", map->width);
	while(i < map->height)
	{
		j = 0;
		map->v_map[i] = safe_malloc(sizeof(char) * (map->width + 1));
		while(map->map[i][j] != '\0')
		{
			if(map->map[i][j] == ' ')
				map->v_map[i][j] = 'x';
			else
				map->v_map[i][j] = map->map[i][j];
			j++;
		}
		while(j < map->width)
		{
			map->v_map[i][j] = 'x';
			j++;
		}
		map->v_map[i][j] = '\0';
		i++;
	}
	map->v_map[i] = NULL;
}

bool check_if_map_is_valid(t_map *map)
{
    int i = 0;
    while (i < map->height)
    {
        int j = 0;
        while (j < map->width)
        {
            if (map->v_map[i][j] == '0')
            {
                // Check top neighbor
                if (i > 0 && map->v_map[i - 1][j] == 'x')
                    return false;
                // Check bottom neighbor
                if (i < map->height - 1 && map->v_map[i + 1][j] == 'x')
                    return false;
                // Check left neighbor
                if (j > 0 && map->v_map[i][j - 1] == 'x')
                    return false;
                // Check right neighbor
                if ((j < map->width) - 1 && map->v_map[i][j + 1] == 'x')
                    return false;
            }
            j++;
        }
        i++;
    }
    return true;
}

bool is_surrounded_by_walls(t_map *map)
{
    int		i; 
	int		j;
	char	c;

    // Check top and bottom rows
    j = 0;
	while ( j < map->width)
	{
        if (map->v_map[0][j] != '1' && map->v_map[0][j] != 'x')
            return false;
        if (map->v_map[map->height - 1][j] != '1' && map->v_map[map->height - 1][j] != 'x')
            return false;
		j++;
    }

    // Check left and right columns
	i = 0;
    while (i < map->height)
	{
        if (map->v_map[i][0] != '1' && map->v_map[i][0] != 'x')
            return false;
        if (map->v_map[i][map->width - 1] != '1' && map->v_map[i][map->width - 1] != 'x')
            return false;
		i++;
    }

    // Check for valid characters
	i = 0;
    while (i < map->height)
	{
		j = 0;
        while (j < map->width)
		{
            c = map->v_map[i][j];
            if (c != '1' && c != '0' && c != 'x' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
                return false;
			j++;
        }
		i++;
    }
    return true;
}

void parse_map(t_map *map)
{
	map->so = check_texture(map->so);
	map->no = check_texture(map->no);
	map->we = check_texture(map->we);
	map->ea = check_texture(map->ea);
	if (map->so == NULL || map->no == NULL || map->we == NULL || map->ea == NULL)
		ft_error(map, -1);
	copy_map(map);
	fill_map(map);
	if (is_surrounded_by_walls(map) == false)
		ft_error(map, 3);
	if (check_if_map_is_valid(map) == false)
		ft_error(map, 3);
}


void store_map(t_map *map)
{
    char *line;
    int count = 0;
    // t_data *current;
    
    while(1)
    {
        line = get_next_line(map->map_fd);
        if (line == NULL)
            break;
        parse_line(line, map, &count);
		free(line);
    }
    close(map->map_fd);
	map->height = count;
	parse_map(map);
}


void check_read_map(char *filename, t_map *map)
{
	map->map_fd = check_map_exists(filename, map);
	store_map(map);
}

void map_init(t_map *map)
{
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->v_map = NULL;
	map->floor.r = -1;
	map->floor.g = -1;
	map->floor.b = -1;
	map->ceiling.r = -1;
	map->ceiling.g = -1;
	map->ceiling.b = -1;
	map->map = NULL;
	map->height = 0;
	map->width = 0;
	map->map_fd = 0;
	map->data = NULL;
}


// int main (int ac, char **av)
// {
// 	t_map *map;
// 	// atexit(leaks);
// 	if (ac != 2)
// 		ft_error(NULL, 1);
// 	map = safe_malloc(sizeof (t_map));
// 	map_init(map);
// 	check_read_map(av[1], map);
// 	printf("NO ->> %s\n", map->no);
// 	printf("SO ->> %s\n", map->so);
// 	printf("WE ->> %s\n", map->we);
// 	printf("EA ->> %s\n", map->ea);
// 	printf("Ceiling colors %d %d %d\n", map->ceiling.r, map->ceiling.g, map->ceiling.b);
// 	printf("Floor colors %d %d %d\n", map->floor.r, map->floor.g, map->floor.b);
// 	int i = 0;
// 	while (map->map[i] != NULL)
// 	{
// 		printf("copy of map line ->> [%s]\n", map->map[i]);
// 		i++;
// 	}
// 	i = 0;
// 	printf("**************************************************************\n");
// 	while (map->v_map[i] != NULL)
// 	{
// 		printf("finale  map line ->> {%s}\n", map->v_map[i]);
// 		i++;
// 	}

// 	mlx_t* mlx = mlx_init(800, 800, "42Balls", true);
// 	if (!mlx)
// 		return 1;
// 	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
// 	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
// 		return 1;

// 	mlx_loop(mlx);
// 	free_map(map);
// 	return (0);
// }