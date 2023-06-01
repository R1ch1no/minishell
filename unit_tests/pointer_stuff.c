
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

# include "../libft/libft.h"

typedef struct s_data
{
	char				*str;
}						t_data;


void change(char **str)
{
    free(*str);
    str = NULL;
    //str = "Test";
}


int main()
{
    t_data *data;

    data = malloc(sizeof(t_data));
    data->str = strdup("Hello");
    change(&data->str);
    if (&data->str == NULL)
        printf("NULL\n");
    if (data->str == NULL)
        printf("NULL\n");


    printf("End of main\n");
    free(data);
}