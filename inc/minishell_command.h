#ifndef MINISHELL_COMMAND_H
# define MINISHELL_COMMAND_H

# include "minishell_utils.h"
# include "fcntl.h"

/* values for word flags */
# define W_DOLLAR		0x01	//dollar sign present
# define W_QUOTES		0x02	//quotes present
# define W_NOEXPAND		0x04	//do not expand filenames

/* values for redirection flags */
# define RED_IN			0x01	//input red
# define RED_OUT		0x02	//output red
# define RED_TRUNC		0x04	//output red trunc
# define RED_APPEND		0x08	//output red append
# define RED_HEREDOC	0x10	//input red from heredoc

/* values for command flags */
# define CMD_SIMPLE		0x01	//command is a simple cmd
# define CMD_SUBSHELL	0x02	//command is a subshell cmd
# define CMD_BUILTIN	0x04	//command is a builtin
# define CMD_EXECTRUE	0x08	//execution command if previous is true
# define CMD_EXECFALSE	0x10	//execution command if previous is false
# define CMD_STARTPIPE	0x20	//command start a pipeline
# define CMD_PIPE		0x40	//command is in a pipeline
# define CMD_ENDPIPE	0x80	//command ends a pipeline

typedef struct s_word_d
{
	char	*lval;
	int		flags;
}t_word_d;

typedef struct s_word_lst
{
	t_word_d			*word;
	struct s_word_lst	*next;
}t_word_lst;

typedef struct s_red
{
	int				rflags;
	int				oflags;
	t_word_d		*filename;
	char			*heredoc_eof;
	struct s_red	*next;
}t_red;

typedef union u_command_elems
{
	t_word_lst				*words;
	struct s_command_lst	*cmds;
}t_command_elems;

typedef struct s_command
{
	int				flags;
	char			**argv;
	int				argc;
	char			*cmd_path;
	t_red			*reds;
	t_command_elems	elem;
}t_command;

typedef struct s_command_lst
{
	t_command				cmd;
	struct s_command_lst	*prev;
	struct s_command_lst	*next;
}t_command_lst;

#endif
