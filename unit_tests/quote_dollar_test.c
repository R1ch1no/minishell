
#include "../minishell.h"

typedef struct s_node
{
	char				*test;
    char                *bash;
    char                *mini;
	struct s_node		*next;
}						t_node;

t_node	*lstlast(t_node *lst)
{
	t_node	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}


void	add_node_back(t_node **lst, char *test, char *bash)
{
	t_node	*last;
    t_node	*new;
    new = malloc(sizeof(t_node));
    if (new == NULL)
	    return ;
    char *str = ft_strdup(test);
    dollar_and_s_quotes(&str);
    
    new->next = NULL;
    new->test = test;
	new->bash = bash;
    new->mini = str;
    
    if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = lstlast(*lst);
	last->next = new;
}

void print_test(t_node node)
{
    printf("Test: %s\n", node.test);
    printf("bash: %s\n", node.bash);
    printf("mini: %s\n", node.mini);

    if (strcmp(node.bash, node.mini) == 0)
        printf("Success\n");
    else
        printf("Fail 🥲\n");
}

void	print_list(t_node *head)
{
	t_node	*print;

	if (!head)
		return ;
	print = head;
	
	while (print)
	{
        ft_printf("-------------------------------------------\n");
		print_test(*print);
        ft_printf("-------------------------------------------\n\n");
        print = print->next;
	}
}

int main()
{
    //TESTING ACTUAL IMPLEMENTATION FOR MINISHELL
    //test rules:
    //any $text_not_special evals-to: qtran even if it doesnt exist
    //$? evals-to: 1234
    //
    t_node *head = NULL;
    //Quotes
    add_node_back
    (   &head, 
        "(\"01'$USER'SHIT $USER$USER'''$'user\")",
        "(01$USERSHIT qtranqtran$user)"   
    );
    

    //
    add_node_back
    (   &head, 
        "text'$'",
        "text$"   
    );
    
    add_node_back
    (   &head, 
        "text$",
        "text$"   
    );

    add_node_back
    (   &head, 
        "$USER'$' space",
        "qtran$ space"   
    );

    //closed quotes directly after
    add_node_back
    (   &head, 
        "(text$\"USER\")",
        "(textUSER)"   
    );

    add_node_back
    (   &head, 
        "(text$'USER')",
        "(textUSER)"   
    );

    add_node_back
    (   &head, 
        "(\"text$'USER\")",
        "(textqtran)"   
    );
    //closed single quotes directly after but in double quotes
    add_node_back
    (   &head,
        "(\"text$'USER'\")",
        "(text$'USER')"
    );

    //closed double quotes in $ sign 
    add_node_back
    (   &head,
        "(\"text$\"USER)",
        "(text$USER)"
    );

    //unclosed quotes
    add_node_back
    (   &head, 
        "text$USER\"",
        "textqtran"
    );
    add_node_back
    (   &head,
        "text$USER\"three\"quo\"tes",
        "textqtranthreequo\"tes"
    );

    
    
    
    
    
    
    add_node_back
    (   &head,
        "text$USER\"NAME\"",
        "textqtranNAME"  
    );

    add_node_back
    (   &head,
        "text$USER>name",
        "textqtran>name"
    );

     add_node_back
    (   &head,
        "text$USER name",
        "textqtran name"
    );

    add_node_back
    (   &head,
        "text\"$USER\"",
        "textqtran"
    );

    add_node_back
    (   &head,
        "text$USER\"NAME\"",
        "textqtranNAME"
    );

    add_node_back
    (   &head,
        "text\"$USER",
        "text\"qtran"
    );

    add_node_back
    (   &head,
        "$USER\"",
        "qtran"
    );

    
    //$ sign and special instant afterwards
    add_node_back
    (   &head,
        "text$|text",
        "text$|text"
    );

    add_node_back
    (   &head,
        "text$<text",
        "text$<text"
    );

    add_node_back
    (   &head,
        "text$>>text",
        "text$>>text"
    );
    //special not instant afterwards
    add_node_back
    (   &head,
        "(text$te|xt)",
        "(textqtran|xt)"
    );

    add_node_back
    (   &head,
        "(text$te>>xt)",
        "(textqtran>>xt)"
    );
    
    //EXIT STATUS AKA $?
    add_node_back
    (   &head,
        "text$?\"exit-status",
        "text1234\"exit-status"
    );
    
    add_node_back
    (   &head,
        "(text$USER?text\")",
        "(textqtran?text\")"
    );

    add_node_back
    (   &head,
        "text$'?text",
        "textqtran?text"
    );

    add_node_back
    (   &head,
        "'text$?text'",
        "text$?text"
    );

    add_node_back
    (   &head,
        "(\"text$?text\")",
        "(text1234text)"
    );


    print_list(head);
    return 0;
}
