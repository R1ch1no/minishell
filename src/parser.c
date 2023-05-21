/*
bash: syntax error near unexpected token `|' or `newline'
    if pipe at beginning or end
    if after any redirection no string afterwards
    any of these: <| <<| >| >>|


DONT need to handle that:
<<<                   
>>> or >>>> or more
--> so just error msg the >> "gives syntax error near unexpected token"         


DONT KNOW WHAT TO DO:
pipe after pipe

*/