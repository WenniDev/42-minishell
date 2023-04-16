//	NORM
//		-missing header

#ifndef SPASH_TYPES_H
# define SPASH_TYPES_H

/*******Types used for syntax and token********/

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
	char	*value;
}t_token;

typedef struct s_syntax
{
	t_token	*token;
	t_token *prev_token;
	char	**grammar;
}t_syntax;

/*************Type used for error************/

typedef struct s_error
{
	char	*msg;
	char	*infos;
	int		num;
}t_error;

/************Types used for commands*********/

typedef struct s_red
{
	char	*file;
	int		flags;
}t_red;

typedef struct s_subcmd
{
	char	*cmd_line;
	t_red	inred;
	t_red	*outred;
}t_subcmd;

typedef struct s_simple_cmd
{
	char	**argv;
	int		argc;
	t_red	inred;
	t_red	*outred;
}t_simple_cmd;

typedef union u_cdm
{
	t_simple_cmd	simple_cmd;
	t_subcmd		subcmd;
}t_cmd;

typedef struct s_cmd_line
{
	char	*string;
	t_cmd	*cmds;
	int		cmd_nb;
}t_cmd_line;

/**************Main data type***************/

typedef struct s_data
{
	t_cmd_line	cmd_line;
	t_syntax	syntax;
	t_error		error;
	int			exit_status;
}t_data;

#endif
