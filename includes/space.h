#ifndef SPACE_H
#define SPACE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct s_resource
{
    char *name;
    int amount;
} t_resource;

typedef struct s_building
{
    char *name;
    int lvl;
    t_resource *buildResources;
} t_building;

typedef struct s_planet
{
    bool settlement;
    int settlement_size;
    int planet_size;
    t_building *buildings;
    t_resource *resources;
} t_planet;

typedef struct s_sector
{
    int n_planet;
    t_planet **planets;
} t_sector;

typedef struct s_worldmap
{
    int width;
    int height;
    t_sector **map;
} t_worldmap;

typedef struct s_data
{
    t_worldmap *map;
    t_resource **resources;
    t_building **buildings;
} t_data;

#endif
