

#include "../minishell.h"

int ft_strcmp_v2(char *s1, char *s2)
{
	if (!s1 || s1 == NULL || !s2 || s2 == NULL)
		return (9999);
	printf("s1: %s, s2 %s" , s1, s2);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((int)(unsigned char)(*s1) - (int)(unsigned char)(*s2));
}

int main()
{
    char *line = NULL;
    int i = ft_strcmp_v2(line, "test");

}