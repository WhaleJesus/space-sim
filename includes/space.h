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
#include <time.h>

typedef struct	s_char
{
	char				*name;
	int					hp;
	struct s_item		*weapon;
	struct s_inventory	*inventory;
	struct s_char		*prev;
	struct s_char		*next;
}	t_char;

typedef struct	s_item
{
	unsigned long	id;
	char			*name;
	char			*description;
	char			*type;
	int				stat;
	int				equipped;
	int				can_drop;
	struct s_item	*next;
	struct s_item	*prev;
}	t_item;

typedef struct	s_inventory
{
	struct s_item	*item;
	int				size;
	int				maxSize;
}	t_inventory;

typedef struct	s_location
{
	char				*name;
	char				*description;
	char				**options;
	char				**enemies;
	char				**characters;
	int					x;
	int					y;
	struct s_location	*next;
	struct s_location	*prev;
}	t_location;

typedef struct	s_data
{
	struct s_char 			*char_main;
	struct s_char			*enemies;
	struct s_inventory		*inventory;
	struct s_location		*map;
	int						map_width;
	int						map_height;
	int						inventory_base_size;
	unsigned long			item_id;
	struct s_location		*current_location;
	int						exit;
}	t_data;

// init
void		init_data(t_data *data);
t_inventory	*init_inventory(int maxSize);
t_item		*init_item(t_data *data, char *name, char *description, char *type, int stat, int can_drop);
t_char		*init_char(t_data *data, char *name, int hp, char *weapon);

// init location
t_location	*init_location_plains(int x, int y);

// get
t_inventory	*copy_inventory(t_data *data, t_inventory *src);
t_char		*copy_enemy(t_data *data, t_char *enemy_tmp);
t_char		*get_enemy(t_data *data, t_char *enemies, char *name);
t_item		*get_item_by_name(t_item *src, char *name);
t_item		*get_item_by_pos(t_item *src, int pos);
int			get_item_pos_by_name(t_item *src, char *name);
t_location	*get_map_location(t_location *map, int x, int y);

// input
void 		clear_console(void);
char		*get_input(char *msg);
int			get_input_int(char *msg);

// free
void		free_data(t_data *data);
void		free_character(t_char *character);
void		free_item(t_item *item);
void		free_inventory(t_inventory *inv);
void		free_char_array(char **arr);
void		free_location(t_location *location);
void		free_map(t_data *data);
void		free_location(t_location *location);

// read
void		read_location(t_location *location, FILE *fd);

// utils
char		*ft_substr(char* arr, int start, int len);
char 		*ft_strdup(char *s);
int			char_arr_len(char **arr);
char		**add_option(char **arr, char *option);
int 		rand_range(int min, int max);
char 		*format_width(const char *src, size_t size);
char		*strjoin(char *s1, char *s2);

// battle
int			battle(t_char *main, t_char *enemy_tmp);

// location
void		handle_location_option(t_data *data, t_location *location, int i);

// item
void		add_item(t_item *dst, t_item *item);
int			inventory_add_item(t_inventory *inv, t_item *item);
int			inventory_remove_item(t_inventory *inv, int	pos);
int			equip_weapon_from_inv(t_char *c, t_inventory *inv, unsigned long id);
int			unequip_weapon(t_char *c);
void		print_inventory(t_inventory *inv);

// display
void		display_location(t_data *data);
void		display_inventory(t_char *c, t_inventory *inv);

#endif
