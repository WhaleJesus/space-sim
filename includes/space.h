#ifndef SPACE_H
#define SPACE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

typedef struct	s_char
{
	char			*name;
	int				hp;
	int				attack;
	struct s_char	*prev;
	struct s_char	*next;
}	t_char;

typedef struct	s_location
{
	char				*name;
	char				*description;
	char				**options;
	char				**enemies;
	int					x;
	int					y;
	struct s_location	*next;
	struct s_location	*prev;
}	t_location;

typedef struct	s_data
{
	struct s_char 		*char_main;
	struct s_char		*enemies;
	struct s_location	*map;
	int					map_width;
	int					map_height;
	struct s_location	*current_location;
	int					exit;
}	t_data;

// init
void		init_data(t_data *data);

// get
t_char		*copy_enemy(t_char *enemy_tmp);
t_char		*get_enemy(t_char *enemies, char *name);
t_location	*get_map_location(t_location *map, int x, int y);

// input
void 		clear_console(void);
char		*get_input(char *msg);
int			get_input_int(char *msg);

// free
void		free_data(t_data *data);
void		free_char(t_char *character);
void		free_map(t_data *data);
void		free_location(t_location *location);

// read
void		read_location(t_location *location, FILE *fd);

// utils
char* 		ft_substr(char* arr, int start, int len);
char 		*ft_strdup(char *s);

// battle
int			battle(t_char *main, t_char *enemy_tmp);

// location
void		handle_location_option(t_data *data, t_location *location, int i);

// display
void		display_location(t_data *data);

#endif
