//	NORM
//		-missing header

#ifndef SPASH_TYPES_H
# define SPASH_TYPES_H

# include "string.h"

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
	struct s_token	*next;
	struct s_token	*prev;
}t_token;

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
	t_op			op;
	struct s_red	*next;
}t_red;

typedef enum e_exec
{
	ALL,
	IF_TRUE,
	IF_FALSE
}t_exec;

typedef enum e_cmd_type
{
	SIMPLE_CMD,
	SUBCMD,
	BUILTIN
}t_cmd_type;

typedef struct s_cmd
{
	char		**argv;
	int			argc;
	char		*subcmd_line;
	t_red		*io_red;
	t_exec		exec_if;
	t_cmd_type	type;
}t_cmd;

/**************Main data type***************/

typedef struct s_data
{
	char		*c_line;
	t_cmd		*c_table;
	size_t		c_nb;
	t_token		*tk_lst;
	char		**grammar;
	int			stx;
	t_error		error;
	int			exit_status;
}t_data;

#endif
