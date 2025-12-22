#include "../includes/space.h"

void    init_npc_basic(t_data *data)
{
    t_char *c;

    c = init_char(data, "john doe", 100, NULL);
    init_character_stats(c, 10, 10, 10, 10, 10, 10);
    c->dialogue = init_dialogue(data, "hello\n");
    t_option    **options = malloc(sizeof(t_option *) * 3);
    options[0] = init_option("eat ass", 1, 2, STAT_STEALTH, 25);
    options[0]->next = init_dialogue(data, "ooh");
    options[0]->fail = init_dialogue(data, "WHAT ARE YOU DOING");
    return (c);
}