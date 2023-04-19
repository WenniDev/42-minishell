//  NORM
//      -missing header

#ifndef SPASH_PARSING_H
# define SPASH_PARSING_H

# define MUCH_LESS				"<<"
# define MUCH_GREATER			">>"
# define DOUBLE_AMPERSAND		"&&"
# define DOUBLE_VERTICAL_BAR	"||"
# define LESS					"<"
# define GREATER				">"
# define VERTICAL_BAR			"|"
# define OPENED_PARENTHESIS		"("
# define CLOSED_PARENTHESIS		")"
# define S_NEWLINE				"newline"

# define FALSE					0
# define END					1
# define NO_END					2
# define CORRECT				3

#define METACHARACTERS			" \t\n|&()<>"

# define EMPTY					""
# define SINGLE_QUOTE			'\''
# define DOUBLE_QUOTE			'"'
# define SPACE					' '

char	*get_cmd_line(t_data *data);
void	parse(t_data *data);
void	init_syntax(t_data *data, t_syntax *stx);
int		check_syntax(t_data *data, t_token *tk);

#endif
