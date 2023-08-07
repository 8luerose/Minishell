typedef enum	s_type
{
	WORD,
	REDIRECTION,
	QUOTING,
	PIPE,
	HEREDOC
}	t_type;

t_type token_type(char *token)
{
	if (strcmp(token, "|") == 0)
		return PIPE;
	else if (strcmp(token, ">") == 0 || strcmp(token, ">>") == 0 || strcmp(token, "<") == 0)
		return REDIRECTION;
	else if (strcmp(token, "<<") == 0)
		return HEREDOC;
	else if (*token == '"' || *token == '\'')
		return QUOTING;
	else
		return WORD;
}