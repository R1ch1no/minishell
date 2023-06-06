
#include "../minishell.h"

typedef struct s_test
{
	char				*test;
    char                *bash;
    char                *mini;
	struct s_test		*next;
}						t_test;

t_test	*lstlast_test(t_test *lst)
{
	t_test	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}


void	add_test_back(t_test **lst, char *test, char *bash)
{
	t_test	*last;
    t_test	*new;
    new = malloc(sizeof(t_test));
    if (new == NULL)
	    return ;
    char *str = ft_strdup(test);
    dollar_and_s_quotes(&str, NULL);
    //printf("%s\n", test);
    new->next = NULL;
    new->test = test;
	new->bash = bash;
    new->mini = str;
    
    if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = lstlast_test(*lst);
	last->next = new;
}

void print_test(t_test node)
{
    if (strcmp(node.bash, node.mini) == 0)
    {
        //printf("Test: %s\n", node.test);
        //printf("bash: %s\n", node.bash);
        //printf("mini: %s\n", node.mini);
        //printf("Success\n");
        return ;
    }
    else
    {
        printf("Test: %s\n", node.test);
        printf("bash: %s\n", node.bash);
        printf("mini: %s\n", node.mini);
        printf("Fail 🥲\n");
        ft_printf("-------------------------------------------\n\n");
    }

}

void	print_test_list(t_test *head)
{
	t_test	*print;

	if (!head)
		return ;
	print = head;
	
	while (print)
	{
		print_test(*print);
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
    t_test *head = NULL;
    
    
    //richards test with quotes
    add_test_back
    (   &head, 
        "a='\"'",
        "a=\""   
    );

     add_test_back
    (   &head, 
        "b=\"'\"",
        "b='"   
    );

    add_test_back
    (   &head, 
        "(b=\"\"\"this\"\"isnotfun)",
        "(b=this\"isnotfun)"   
    );
         add_test_back
    (   &head, 
        "(b=\"\"\"\"\"\"\"this\"\"is\"\"not\"\"fun\")",
        "(b=thisisnotfun)"   
    );

         add_test_back
    (   &head, 
        "(c='\"\"\"\"\"\"\"this\"\"is\"\"not\"\"fun\"')",
        "(c=\"\"\"\"\"\"\"this\"\"is\"\"not\"\"fun\")"   
    );
    
    //Quotes
    add_test_back
    (   &head, 
        "(\"01'$USER'SHIT $USER$USER'''$'user\")",
        "(01$USERSHIT qtranqtran$user)"   
    );
    

    //
    add_test_back
    (   &head, 
        "text'$'",
        "text$"   
    );
    
    add_test_back
    (   &head, 
        "text$",
        "text$"   
    );

    add_test_back
    (   &head, 
        "$USER'$' space",
        "qtran$ space"   
    );

    //closed quotes directly after
    add_test_back
    (   &head, 
        "(text$\"USER\")",
        "(textUSER)"   
    );

    add_test_back
    (   &head, 
        "(text$'USER')",
        "(textUSER)"   
    );

    add_test_back
    (   &head, 
        "(\"text$'USER\")",
        "(textqtran)"   
    );
    //closed single quotes directly after but in double quotes
    add_test_back
    (   &head,
        "(\"text$'USER'\")",
        "(text$'USER')"
    );

    //closed double quotes in $ sign 
    add_test_back
    (   &head,
        "(\"text$\"USER)",
        "(text$USER)"
    );

    //unclosed quotes
    add_test_back
    (   &head, 
        "text$USER\"",
        "textqtran"
    );
    add_test_back
    (   &head,
        "text$USER\"three\"quo\"tes",
        "textqtranthreequo\"tes"
    );

    
    
    
    
    
    
    add_test_back
    (   &head,
        "text$USER\"NAME\"",
        "textqtranNAME"  
    );

    add_test_back
    (   &head,
        "text$USER>name",
        "textqtran>name"
    );

     add_test_back
    (   &head,
        "text$USER name",
        "textqtran name"
    );

    add_test_back
    (   &head,
        "text\"$USER\"",
        "textqtran"
    );

    add_test_back
    (   &head,
        "text$USER\"NAME\"",
        "textqtranNAME"
    );

    add_test_back
    (   &head,
        "text\"$USER",
        "text\"qtran"
    );

    add_test_back
    (   &head,
        "$USER\"",
        "qtran"
    );

    
    //$ sign and special instant afterwards
    add_test_back
    (   &head,
        "text$|text",
        "text$|text"
    );

    add_test_back
    (   &head,
        "text$<text",
        "text$<text"
    );

    add_test_back
    (   &head,
        "text$>>text",
        "text$>>text"
    );
    //special not instant afterwards
    add_test_back
    (   &head,
        "(text$te|xt)",
        "(textqtran|xt)"
    );

    add_test_back
    (   &head,
        "(text$te>>xt)",
        "(textqtran>>xt)"
    );
    
    //EXIT STATUS AKA $?
    add_test_back
    (   &head,
        "text$?\"exit-status",
        "text1234\"exit-status"
    );
    
    add_test_back
    (   &head,
        "(text$USER?text\")",
        "(textqtran?text\")"
    );

    add_test_back
    (   &head,
        "text$'?text",
        "textqtran?text"
    );

    add_test_back
    (   &head,
        "'text$?text'",
        "text$?text"
    );

    add_test_back
    (   &head,
        "(\"text$?text\")",
        "(text1234text)"
    );


    print_test_list(head);
    return 0;
}
