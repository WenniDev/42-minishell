/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:07:45 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/27 10:58:01 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSE_H
# define MINISHELL_PARSE_H

# include "minishell_command.h"
# include "minishell_utils.h"
# include "minishell_error.h"
# include "libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <stdint.h>
# include <readline/readline.h>
# include <readline/history.h>

/* values for the parser state */
# define PST_SUBSHELL		0x01
# define PST_HEREDOC		0x02
# define PST_CMD			0x04
# define PST_END			0x08

# define HEREDOC_MAX		16

# define META_CHARACTERS	" \n<>|&()"
# define BUILTINS			"env pwd cd unset echo export exit"

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

/* struct to store the heredocs reds */
typedef struct s_hd
{
	t_red		*red;
	struct s_hd	*next;
}t_hd;

/* struct to store the the subshel cmds */
typedef struct s_addr_lst
{
	t_command_lst		*addr;
	struct s_addr_lst	*prev;
}t_addr_lst;

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
	t_hd			*hd_lst;
	int				hd_nb;
	t_command_lst	*cmd_lst;
	t_command_lst	*cl_curr;
	t_addr_lst		*sub_lst;
	bool			eof;
	int				status;
}t_parser;

int			is_meta(char c);
char		get_char(char **ptr);
void		unget_char(char **ptr);
void		clean_cmd(t_command_lst *cl);
char		*get_line(t_parser *p);
int			next_token(t_parser *p, int tk);
void		reset_parser(t_parser *p);
int			end_subshell_cmd(t_parser *p);
t_red		*ft_last_red(t_red *r);
int			ft_is_builtin(char *s);

void		gather_heredoc(t_parser *p);

#endif
