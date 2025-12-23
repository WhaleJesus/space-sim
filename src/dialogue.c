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
    int         input;
    int         display_next = 1;

    option = dialogue->options[i];
    if (option->skill_check)
    {
        if (handle_skill_check(data->char_main, option->stat, option->req))
            character_add_xp(data->char_main, option->xp, 1);
        else
        {
            display_next = 0;
            display_dialogue(data, npc, option->fail);
        }    
    }
    if (!strcmp(option->text, "let's trade"))
    {
        
        input = -1;
        while (input < 1 || input > 3)
        {
            if (!DEBUG)
                clear_console();
            input = get_input_int("1. buy\n2. sell\n3. back\n");
            if (input == 1)
                display_inventory(data, npc, npc->inventory, 0, 1);
            else if (input == 2)
                display_inventory(data, npc, data->char_main->inventory, 1, 1);
            else if (input == 3)
                break ;
            input = -1;
        }
    }
    if (display_next)
        display_dialogue(data, npc, option->next);
}

void    display_dialogue(t_data *data, t_char *npc, t_dialogue *dialogue)
{
    int     option = -1;

    if (!data || !npc || !dialogue)
    {
        if (DEBUG)
            printf("DEBUG: no dialogue\n");
        return ;
    }
    if (!DEBUG)
        clear_console();
    printf("%s:\n%s\n", npc->name, dialogue->text);
    if (!dialogue->options)
    {
        get_input_int("");
        if (dialogue->next)
            display_dialogue(data, npc, dialogue->next);
    }
    else 
    {
        int i = 0;
        while (dialogue->options[i])
        {
            printf("%i. %s%s\n", i + 1, get_stat_name(dialogue->options[i]->stat), dialogue->options[i]->text);
            i++;
        }
        while (option < 0)
        {
            option = get_input_int("");
            if (option < 1 || option > ptr_arr_len((void **)dialogue->options))
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