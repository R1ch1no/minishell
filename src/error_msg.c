
#include "../minishell.h"

//second printf -> if (< || << || > || >> is the last thing)
void	error_msg(char *str)
{
	printf("%s: command not found\n", str);
	printf("bash: syntax error near unexpected token `newline\n");
}
