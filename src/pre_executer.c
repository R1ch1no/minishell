
#include "../minishell.h"

void prep_for_executer(t_node *head, t_data *data)
{
    t_node *current;

    current = head;
    current = head;
    while (current)
    {
        if (count_char(current->cmd, '\'') > 1 || ft_strchr(current->cmd, '$') != NULL)
            
        current = current->next;    
    }
}
