//  NORM
//      -missing header

#ifndef SPASH_PARSING_H
# define SPASH_PARSING_H

# include "spash_types.h"

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

# define END					2
# define NO_END					1
# define CORRECT				0

# define METACHARACTERS			" \t\n|&()<>"
# define BUILTINS				"export unset echo cd env exit"

# define NOT_FOUND				""
# define SINGLE_QUOTE			'\''
# define DOUBLE_QUOTE			'"'
# define SPACE					' '

char	*get_cmd_line(t_data *data);
void	parse(t_data *data);
void	create_tokens(t_data *data);
int		check_syntax(t_data *data, t_token *tk, int *par);
void	add_cmd(t_data *data, t_token *tk);
void	subcmd(t_data *data, t_cmd *cmd, t_token *tk);
void	add_io_red(t_data *data, t_cmd *cmd, t_token *tk);
void	add_arg(t_data *data, t_cmd *cmd, char *arg);

#endif
