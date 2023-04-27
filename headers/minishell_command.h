 #ifndef MINISHELL_COMMAND_H
# define MINISHELL_COMMAND_H

# define	W_DOLLAR		(1 << 0)
# define 	W_QUOTES		(1 << 1)

# define 	CMD_SUBSHELL	(1 << 0)
# define 	CMD_BUILTIN		(1 << 1)

typedef enum e_command_type
{
	simple_cmd,
	subshell_cmd
}t_command_type;

typedef struct s_word_desc
{
	char	*word;
	int		flags;
}t_word_desc;

typedef struct s_word_lst
{
	t_word_desc			word_desc;
	struct s_word_lst	*next;
}t_word_lst;

typedef struct s_redirect
{
	int					flags;
	int					oflags;
	t_word_desc 		filename;
	char				*heredoc_eof;
	struct s_redirect	*next;
}t_redirect;

typedef struct s_subshell_cmd
{
	int					flags;
	int					line;
	struct s_command	*command;
}t_subshell_cmd;

typedef struct s_simple_cmd
{
	int			flags;
	int			line;
	t_word_lst	*words;
	t_redirect	*redirects;
}t_simple_cmd;

typedef union u_command_value
{
	t_simple_cmd	*simple_cmd;
	t_subshell_cmd	*subshell_cmd;
}t_command_value;

 typedef struct s_command
 {
	 t_command_type		type;
	 int				flags;
	 int				line;
	 t_redirect			*redirects;
	 t_command_value	value;
 }t_command;

#endif
