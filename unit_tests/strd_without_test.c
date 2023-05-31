
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c && s[i])
		i++;
	if (s[i] == (char)c)
		return ((char *)(&s[i]));
	else
		return (NULL);
}
char *strdup_without(char *src, char c, int len)
{
    char *dup;
    int i;
    int j;

    if (!src)
        return (NULL);
    dup = malloc(sizeof(char) * (len + 1));
    if (!dup)
        exit(1); //cleanse()
    i = 0;
    j = 0;
    while (src[i] && j < len)
    {
        if (src[i] != c)
        {
            dup[j] = src[i];
            j++;
        }
        i++;
    }
    dup[j] = '\0';
    return (dup);
}

int main()
{
    //strdup_without
    char *str = "'Hell Wrl'd";
    char *dup = strdup_without(str, 'o', ft_strchr(&str[1], '\'') - str);
    printf("len with ft_strchr: %ld\n", ft_strchr(&str[1], '\'') - str);
    
    printf("%s\n", str);
    printf("%s\n", dup);
    free(dup);

    //

}