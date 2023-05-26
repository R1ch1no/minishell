
#include "../minishell.h"

void	error_msg(char *str)
{
	printf("%s: command not found\n", str);
	//if (< || << || > || >> als letztes)
	printf("bash: syntax error near unexpected token `newline\n");
}
