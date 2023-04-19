//	NORM
//		-missing header

#ifndef SPASH_TYPES_H
# define SPASH_TYPES_H

/*******Types used for syntax and token********/

typedef enum e_op
{
	HEREDOC_RED,
	OUTAP_RED,
	AND_OP,
	OR_OP,
	IN_RED,
	OUTTR_RED,
	PIPE,
	O_PAR,
	C_PAR,
	NEWLINE,
	NONE
}t_op;

typedef enum e_type
{
	CTRL_OP,
	RED_OP,
	WORD
}t_type;

typedef struct s_token
{
	t_type			type;
	t_op			op;
	char			*value;
	struct s_token	*prev;
}t_token;

typedef struct s_syntax
{
	t_token *tk;
	char	**grammar;
	int		stat;
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
	char			*file;
	int				flags;
	struct s_red	*next;
}t_red;

typedef struct s_subcmd
{
	char	*line;
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

typedef union u_cdm_struct
{
	t_simple_cmd	simple_cmd;
	t_subcmd		subcmd;
}t_cmd_struct;

typedef enum e_cmd_type
{
	SIMPLE_CMD,
	SUBCMD,
	BUILTIN
}t_cmd_type;

typedef struct s_cmd
{
	t_cmd_struct	cmd;
	t_cmd_type		type;
}t_cmd;

/**************Main data type***************/

typedef struct s_data
{
	char		*c_line;
	t_cmd		*c_table;
	int			c_nb;
	t_syntax 	stx;
	t_error		error;
	int			exit_status;
}t_data;

#endif
