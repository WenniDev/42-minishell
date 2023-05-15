/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <jopadova@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:57:48 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/15 15:52:42 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_COMMAND_H
# define MINISHELL_COMMAND_H

# include "minishell_utils.h"
# include "fcntl.h"

/* values for word flags */
# define W_DOLLAR		0x01	//dollar sign present
# define W_QUOTES		0x02	//quotes present
# define W_NOEXPAND		0x04	//do not expand filenames

/* values for command flags */
# define CMD_SUBSHELL	0x01	//command wants subshell
# define CMD_BUILTIN	0x02	//command is a builtin
# define CMD_EXECTRUE	0x02	//execution command if previous is true
# define CMD_EXECFALSE	0x04	//execution command if previous is false
# define CMD_STARTPIPE	0x08	//command start a pipeline
# define CMD_PIPE		0x10	//command is in a pipeline
# define CMD_ENDPIPE	0x20	//command ends a pipeline

typedef enum e_red_infos
{
	r_input,
	r_output_tr,
	r_output_ap,
	r_heredoc
}t_red_infos;

typedef enum e_command_type
{
	simple_cmd,
	subshell_cmd
}t_command_type;

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
	int				oflags;
	int				rflags;
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
	t_command_type	type;
	int				flags;
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
