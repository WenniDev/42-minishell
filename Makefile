#PROJECT
PROJDIR		=	$(realpath $(CURDIR))
TARGET		=	minishell
INCDIR		=	$(PROJDIR)/inc
SRCDIR		=	$(PROJDIR)/srcs
OBJDIR		=	$(PROJDIR)/objects
DEPDIR		=	$(PROJDIR)/dependencies

#COMPILER
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address
HDINC		=	-I $(INCDIR) -I $(PROJDIR)/libft/inc
LIBINC		=	-lreadline

#FILES
LIBFT		=	$(PROJDIR)/libft/libft.a
SRCS		=	$(SRCDIR)/main.c\
				$(SRCDIR)/parser/parse.c\
				$(SRCDIR)/parser/token.c\
				$(SRCDIR)/parser/token_word.c\
				$(SRCDIR)/parser/actions.c\
				$(SRCDIR)/parser/get_line.c\
				$(SRCDIR)/parser/here_document_read.c\
				$(SRCDIR)/parser/parse_utils.c\
				$(SRCDIR)/parser/parse_utils2.c\
				$(SRCDIR)/expand/expand.c\
				$(SRCDIR)/expand/expand_special.c\
				$(SRCDIR)/expand/environment.c\
				$(SRCDIR)/expand/word_splitting.c\
				$(SRCDIR)/expand/redirection.c\
				$(SRCDIR)/expand/wildcard.c\
				$(SRCDIR)/expand/wildcard_utils.c\
				$(SRCDIR)/expand/here_document_expand.c\
				$(SRCDIR)/execution/execute_cmd.c\
				$(SRCDIR)/execution/redirection.c\
				$(SRCDIR)/execution/path.c\
				$(SRCDIR)/execution/exec_utils.c\
				$(SRCDIR)/execution/here_document_write.c\
				$(SRCDIR)/execution/builtins/b_env.c\
				$(SRCDIR)/execution/builtins/b_pwd.c\
				$(SRCDIR)/execution/builtins/b_cd.c\
				$(SRCDIR)/execution/builtins/b_unset.c\
				$(SRCDIR)/execution/builtins/b_export.c\
				$(SRCDIR)/execution/builtins/b_echo.c\
				$(SRCDIR)/execution/builtins/b_exit.c\
				$(SRCDIR)/env.c\
				$(SRCDIR)/sfcalloc.c\
				$(SRCDIR)/sfprint.c\
				$(SRCDIR)/error.c\
				$(SRCDIR)/signal_handler.c\
				$(SRCDIR)/cleanup.c\
				$(SRCDIR)/prompt.c
INCS		=	$(INCDIR)/minishell_parse.h\
				$(INCDIR)/minishell_command.h\
				$(INCDIR)/minishell_expand.h\
				$(INCDIR)/minishell_execute.h\
				$(INCDIR)/minishell.h\
				$(INCDIR)/minishell_error.h\
				$(INCDIR)/minishell_env.h\
				$(INCDIR)/minishell_builtins.h
OBJS		=	$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCS:.c=.o))
DEPS		=	$(patsubst $(SRCDIR)/%,$(DEPDIR)/%,$(SRCS:.c=.d))

#RULES
all : $(TARGET)

$(TARGET) : $(LIBFT) $(OBJS)
	@printf "\nLinking $@...\n"
	@$(CC) $(CFLAGS) $(HDINC) $(OBJS) $(LIBFT) -o $@ $(LIBINC)
	@printf "All done\n"

$(LIBFT) :
	@printf "Compiling libft...\n"
	@make -s -C $(PROJDIR)/libft/

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@mkdir -p $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(dir $(@:.o=.d)))
	@printf "Buildind object files...\r"
	@$(CC) $(CFLAGS) $(HDINC) -c $< -o $@ \
		-MMD -MF $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(@:.o=.d))

-include $(DEPS);

clean :
	@printf "Cleaning object files...\n"
	@make -s clean -C $(PROJDIR)/libft/
	@rm -rf $(OBJDIR) $(DEPDIR)

fclean : clean
	@printf "Cleaning target files...\n"
	@rm -rf $(LIBFT) $(TARGET)

re : fclean all

.PHONY : all clean fclean re