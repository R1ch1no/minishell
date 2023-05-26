
#include "../minishell.h"

//for far only counts number of pipes 
//and saves their index + 1 in the pipes[] int array
int	syntaxer(char **cmd_line)
{
	int	y;
	int	pipes[500];
	int	p;

	y = -1;
	p = 0;
	while (cmd_line[++y] != NULL)
	{
		if (ft_strcmp_v2(cmd_line[y], "|") == 0)
		{
			pipes[p] = y + 1;
			p++;
		}
	}
	return (0);
}
