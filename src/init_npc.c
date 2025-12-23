#include "../includes/space.h"

t_char  *init_npc_basic(t_data *data)
{
    t_char *c;

    c = init_char(data, "john doe", 100, NULL);
    if (!c)
        return (NULL);
    init_character_stats(c, 10, 10, 10, 10, 10, 10);
    c->gold = 20;
    c->dialogue = init_dialogue(data, "hello\n");
    if (!c->dialogue)
        return (NULL);
    t_option    **options = malloc(sizeof(t_option *) * 3);
    if (!options)
    {
        free_character(c);
    }
    options[0] = init_option("eat ass", 1, 2, STAT_STEALTH, 25);
    options[0]->next = init_dialogue(data, "ooh");
    options[0]->fail = init_dialogue(data, "WHAT ARE YOU DOING");
    options[1] = init_option("let's trade", 0, 0, STAT_NONE, 0);
    options[1]->next = init_dialogue(data, "great doing business with you");
    options[2] = NULL;
    c->dialogue->options = options;
    return (c);
}