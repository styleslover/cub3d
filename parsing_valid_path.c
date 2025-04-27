/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_valid_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damoncad <damoncad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:25:54 by damoncad          #+#    #+#             */
/*   Updated: 2025/04/27 16:43:40 by damoncad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


char *ft_strstr(const char *haystack, const char *needle)
{
    size_t i;
    size_t j;

    i = 0;
    if (!needle[0])
        return ((char *)haystack);
    while (haystack[i])
    {
        j = 0;
        while (haystack[i + j] && haystack[i + j] == needle[j])
        {
            j++;
            if (!needle[j])
                return ((char *)&haystack[i]);
        }
        i++;
    }
    return (NULL);
}

void free_split(char **split)
{
    int i;

    i = 0;
    if (!split)
        return;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

int	check_xpm_values(int *values, char **split)
{
    if (!split || !split[0] || !split[1] || !split[2] || !split[3])
        return (0);
    
    values[0] = ft_atoi(split[0]);
    values[1] = ft_atoi(split[1]);
    values[2] = ft_atoi(split[2]);
    values[3] = ft_atoi(split[3]);
    
    if (values[0] > 0 && values[1] > 0 && 
        values[2] > 0 && values[3] > 0)
        return (1);
    return (0);
}

int	process_xpm_dimension_line(char *line, int *values)
{
    char	*start;
    char	*end;
    char	*temp;
    char	**split;
    int		valid;

    valid = 0;
    start = ft_strchr(line, '"');
    if (!start)
        return (0);
    start++;
    end = ft_strchr(start, '"');
    if (!end)
        return (0);
    temp = ft_substr(start, 0, end - start);
    if (!temp)
        return (0);
    split = ft_split(temp, ' ');
    valid = check_xpm_values(values, split);
    if (split)
        free_split(split);
    free(temp);
    return (valid);
}

int	find_xpm_header(int fd, int *values)
{
    char	*line;
    int		valid;

    valid = 0;
    while ((line = get_next_line(fd)))
    {
        if (ft_strstr(line, "columns rows colors chars-per-pixel"))
        {
            free(line);
            line = get_next_line(fd);
            if (line)
            {
                valid = process_xpm_dimension_line(line, values);
                free(line);
            }
            break;
        }
        free(line);
    }
    return (valid);
}
