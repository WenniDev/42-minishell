//  NORM
//      -missing header

#ifndef SPASH_GRAMMAR_H
# define SPASH_GRAMMAR_H

# define MUCH_LESS				"<<"
# define MUCH_GREATER			">>"
# define DOUBLE_AMPERSAND		"&&"
# define DOUBLE_VERTICAL_BAR	"||"
# define LESS					"<"
# define GREATER				">"
# define VERTICAL_BAR			"|"
# define OPENED_PARENTHESIS		"("
# define CLOSED_PARENTHESIS		")"
# define NEWLINE				"\n"

typedef char * t_word;
typedef char * t_newline;

typedef enum e_io_red
{
	IN_RED,
	HEREDOC_RED,
	OUT_RED_TRUNC,
	OUT_RED_APPEND
}t_io_red;

typedef enum e_cmd_sep
{
	PIPE,
	AND_OPERATOR,
	OR_OPERATOR
}t_cmd_sep;

typedef union u_type
{
	t_io_red	io_red;
	t_cmd_sep	cmd_sep;
	t_word		word;
	t_newline	newline;
}t_type;

typedef struct s_token
{
	t_type	type;
}t_token;

typedef struct s_syntax
{
	t_token	token;
	char	**grammar;
}t_syntax;

#endif
