
#include "../minishell.h"

void	print_int_arr(int *arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("arr[%d]: %d\n", i, arr[i]);
		i++;
	}
}

void	print_str_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
	{
		printf("arr == NULL");
		return ;
	}
	while (arr[i])
	{
		printf("%s#\n", arr[i]);
		i++;
	}
	printf("%s#\n", arr[i]);
}
