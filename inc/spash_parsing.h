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
# define NEWLINE_S				"\n"

#define METACHARACTERS			" \t\n|&()<>"

# define EMPTY					""

char	*get_cmd_line(t_data *data);

#endif
