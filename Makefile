#*********PROJECT**********#

PROJDIR	=	$(realpath $(CURDIR))
NAME	=	minishell
LIBDIR	=	$(PROJDIR)/lib
SRCDIR	=	$(PROJDIR)/srcs
HDDIR	=	$(PROJDIR)/inc
OBJDIR	=	$(PROJDIR)/objs
DEPDIR	=	$(PROJDIR)/deps

#*********FILES************#

LIBFT	=	$(LIBDIR)/libft/libft.a
SRCS	=	$(SRCDIR)/main.c\
			$(SRCDIR)/init.c\
			$(SRCDIR)/error.c\
			$(SRCDIR)/exit_prg.c\
			$(SRCDIR)/spash.c\
			$(SRCDIR)/cleanup.c\
			$(SRCDIR)/parsing/get_cmd_line.c\
			$(SRCDIR)/parsing/parse.c\
			$(SRCDIR)/parsing/create_tokens.c\
			$(SRCDIR)/parsing/check_syntax.c\
			$(SRCDIR)/parsing/add_cmd.c\
			$(SRCDIR)/parsing/subcmd.c\
			$(SRCDIR)/parsing/add_io_red.c\
			$(SRCDIR)/parsing/add_arg.c\
			$(SRCDIR)/execution/exec.c\
			$(SRCDIR)/execution/io_red.c\
			$(SRCDIR)/execution/exec_cmd.c\
			$(SRCDIR)/execution/exec_builtin.c\
			$(SRCDIR)/execution/get_path.c\
			$(SRCDIR)/sig.c\
			$(SRCDIR)/builtins/b_cd.c\
			$(SRCDIR)/builtins/b_env.c\
			$(SRCDIR)/builtins/b_pwd.c\
			$(SRCDIR)/builtins/b_unset.c\
			$(SRCDIR)/environ/init_env.c
HD		=	$(HDDIR)/spash.h\
			$(HDDIR)/spash_parsing.h\
			$(HDDIR)/spash_types.h\
			$(HDDIR)/spash_error.h\
			$(HDDIR)/spash_exec.h\
			$(SRCDIR)/spash_builtins.h\
			$(SRCDIR)/spash_environ.h
OBJS	=	$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCS:.c=.o))
DEPS	=	$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCS:.c=.d))

#*********COMPILER*********#

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
DEBUG	=	-g -fsanitize=address
HDINC	=	-I $(HDDIR) -I $(LIBDIR)/libft/inc
LIBINC	=	-lreadline

#*********COLORS***********#

GREEN	=	\e[32m
BLUE	=	\e[34m
NC		=	\e[0m

#*********RULES************#

all : $(NAME)

debug : $(NAME)
	@printf "Linking $(BLUE)$< $(NC)with debug flags\n"
	@$(CC) $(CFLAGS) $(DEBUG) $(OBJS) $(LIBFT) -o $(NAME) $(LIBINC)
	@printf "$(GREEN)Done\n$(NC)"

$(NAME) : $(LIBFT) $(OBJS)
	@printf "$(GREEN)Build complete\n$(NC)"
	@printf "Linking $(BLUE)$@\n$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@ $(LIBINC)
	@printf "$(GREEN)Done\n$(NC)"


$(LIBFT) :
	@printf "Compiling $(notdir $@)\n"
	@make -s -C $(LIBDIR)/libft/
	@printf "$(GREEN)Done\n$(NC)"

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@mkdir -p $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(dir $@))
	@printf "Building $(BLUE)$(notdir $@)\n$(NC)"
	@$(CC) $(CFLAGS) $(HDINC) -c $< -o $@ \
		-MMD -MF $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(@:.o=.d))

-include $(DEPS)

clean :
	@printf "Cleaning object files...\n"
	@make -s clean -C $(LIBDIR)/libft/
	@rm -rf $(OBJDIR)
	@printf "$(GREEN)Done\n$(NC)"
	@printf "Cleaning dependency files...\n"
	@rm -rf $(DEPDIR)
	@printf "$(GREEN)Done\n$(NC)"

fclean : clean
	@printf "Cleaning target files...\n"
	@make -s fclean -C $(LIBDIR)/libft/
	@rm -f $(NAME)
	@printf "$(GREEN)Done\n$(NC)"

re : fclean all

.PHONY : all debug clean fclean re