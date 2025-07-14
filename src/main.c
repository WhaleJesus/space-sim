#include "../includes/space.h"

size_t strarrlen(char **arr)
{
    size_t i = 0;

    while (arr[i])
        i++;
    return (i);
}

t_building *init_building(t_data *data, char *name, int lvl, t_resource **resources)
{
}

void init_data_buildings(t_data *data)
{
    int i;
    int max;
    t_building **buildings;

    i = 0;
    max = 2;
    buildings = malloc(sizeof(t_building) * max);
    if (!buildings)
        return (NULL);
    buildings[0] = init_building;
}

init_data_resources(t_data *data)
{
    int i;
    int max;
    char *names[] = {"iron", "stone", "oxygen"};
    t_resource **resources;
    t_resource *resource;

    i = 0;
    max = strarrlen(names);
    resources = malloc(sizeof(t_resource *) * max);
    if (!resources)
        return (NULL);
    while (i < max)
    {
        resource = malloc(sizeof(t_resource));
        if (!resource)
        {
            i = 0;
            while (resources[i])
                free(resources[i++]);
            free(resources);
            return (NULL);
        }
        resource->name = names[i];
        resource->amount = -1;
        resources[i] = resource;
    }
    data->resources = resources;
}

void init_data(t_data *data)
{
    data->map = NULL;
    data->resources = NULL;
    data->buildings = NULL;

    data->resources = init_data_resources(data);
}

int main(int ac, char **av)
{
    t_data data;

    init_data(&data);
}