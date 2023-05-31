
#include "../minishell.h"

void idintify_tokens(t_node *head)
{
    t_node *current;

    current = head;
    while (current)
    {
        if (ft_strcmp_v2(current->cmd, "<" ) == 0 || ft_strcmp_v2(current->cmd, "<<" ) == 0)
            current->special = TRUE;
        else if (ft_strcmp_v2(current->cmd, ">" ) == 0 || ft_strcmp_v2(current->cmd, ">>" ) == 0)
            current->special = TRUE;
        else if (ft_strcmp_v2(current->cmd, "|" ) == 0)
            current->special = TRUE;
        current = current->next;
    }
}