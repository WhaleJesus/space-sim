#include "../includes/space.h"

int handle_skill_check(t_char *c, t_stat_type stat, int req)
{
    if (get_char_stat(c, stat) >= req)
        return (1);
    return (0);
}

void    handle_dialogue_option(t_data *data, t_char *npc, t_dialogue *dialogue, int i)
{
    t_option    *option;

    option = dialogue->options[i];
    if (option->skill_check)
    {
        if (handle_skill_check(data->char_main, option->stat, option->req))
        {
            character_add_xp(data->char_main, option->xp, 1);
            display_dialogue(data, npc, option->next);
        }
        else 
            display_dialogue(data, npc, option->fail);
    }
    else if (option->next)
        display_dialogue(data, npc, option->next);
}

void    display_dialogue(t_data *data, t_char *npc, t_dialogue *dialogue)
{
    int     option = -1;

    if (!DEBUG)
        clear_console();
    printf("%s:\n%s\n", dialogue->text);
    if (!dialogue->options)
    {
        get_input_int("");
        if (dialogue->next)
            display_dialogue(data, npc, dialogue->next);
    }
    else 
    {
        int i = 0;
        while (dialogue->options)
        {
            printf("%i. %s%s\n", i + 1, get_skill_check_name(dialogue->options[i]->stat), dialogue->options[i]->text);
            i++;
        }
        while (option < 0)
        {
            option = get_input_int("");
            if (option < 1 || option > option_arr_len(dialogue->options))
            {
                option = -1;
                printf("wrong input\n");
            }
            else 
            {
                option--;
                handle_dialogue_option(data, npc, dialogue, option);
            }
        }
    }
}