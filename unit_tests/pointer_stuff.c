
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


void print_address(char *str)
{
    printf("address in function scope: %p\n", &str);
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

    char *str1 = strdup("Hello");
    char *str2 = strdup("nothing");
    printf("address main scope: %p\n", &str1);
    print_address(str1);
    printf("address main scope: %p\n", &str2);
    print_address(str2);

}