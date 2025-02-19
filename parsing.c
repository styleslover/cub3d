#include "cub3d.h"

void  parse_config_line(...)
{
  //todo
}

void  is_map_line(char *str)
{
  while (*str && *str == ' ')
    str++;
  if (*str != '1' || *str != '0' || *str != 'N' || *str != 'S' || *str != 'E' || *str != 'V')
        return (0);
  return (1);
}

void  parse_file(int fd, t_game *game)
{
  char *line;
  int  line_len;
  
  game->win_width = 0;
  game->win_height = 0;
  line_len = 0;
  while (line = get_next_line(fd))
    {
      if (is_map_line(line))
      {
        line_len = ft_strlen(ft_strtrim(line, " "));
        if (line_len > game->win_width)
          game->win_width = line_len;
        height++;
      }
      else
        parse_config_line(); //todo
      free(line);
    }
}
