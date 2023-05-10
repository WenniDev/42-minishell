#ifndef MINISHELL_PARSE_H
# define MINISHELL_PARSE_H

# include "minishell_command.h"
# include "minishell_utils.h"
# include "minishell_error.h"
# include "libft.h"
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

/* values for the parser state */
# define PST_SUBSHELL		0x01
# define PST_HEREDOC		0x02
# define PST_END			0x04

# define HEREDOC_MAX		16

# define META_CHARACTERS	" \n<>|&()"
# define BUILTINS			"echo unset pwd export cd env"

# define INPUT_RED			1
# define OUTPUT_RED			2

/* values for non ASCII tokens */
typedef enum e_token_type
{
	TOKEN_ERROR = -2,
	LESS_LESS = 256,
	GREATER_GREATER = 257,
	AND_AND = 258,
	OR_OR = 259,
	WORD = 260
}t_token_type;

/* semantic symbols values */
typedef enum e_symbol_kind
{
	SYM_EMPTY = -1,
	SYM_LESS = 1,
	SYM_GREATER = 2,
	SYM_LESS_LESS = 3,
	SYM_GREATER_GREATER = 4,
	SYM_OR = 5,
	SYM_OR_OR = 6,
	SYM_AND_AND = 7,
	SYM_OPEN_PAR = 8,
	SYM_CLOSED_PAR = 9,
	SYM_NEWLINE = 10,
	SYM_WORD = 11,
	SYM_SIMPLE_CMD = 12,
	SYM_SUBSHELL_CMD = 13
}t_symbol_kind;

typedef struct s_parser
{
	char			*cmd_line;
	char			*line_read;
	char			*line_ptr;
	int				line;
	int				state;
	int				ssymc;
	int				tk;
	int				act;
	int				pc;
	t_word_d		word;
	t_red			*hd_lst;
	t_command_lst	*cmd_lst;
	t_command_lst	*cl_last;
	t_command_lst	*cl_curr;
	bool			eof;
	int				status;
}t_parser;

int			is_redir(int tk);
int			is_connector(int tk);
int			is_meta(char c);
int			tk_symbol(int tk);
char		get_char(char **ptr);
const char	*tk_translate(int tk);
void		unget_char(char **ptr);
void		clean_cmd(t_command_lst *cl);
char		*get_line(t_parser *p);
void		parser_act(t_parser *p, int act);
int			next_token(t_parser *p, int tk);
void		reset_parser(t_parser *p);

#endif
