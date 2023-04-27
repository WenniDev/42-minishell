#PROJECT
PROJDIR		=	$(realpath $(CURDIR))
TARGET		=	minishell
INCDIR		=	$(PROJDIR)/headers
SRCDIR		=	$(PROJDIR)/sources
OBJDIR		=	$(PROJDIR)/objects
DEPDIR		=	$(PROJDIR)/dependencies

#COMPILER
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
HDINC		=	-I $(INCDIR) -I $(PROJDIR)/libft/libft.a
LIBINC		=	-lreadline

#FILES
LIBFT		=	$(PROJDIR)/libft/libft.a
SRCS		=	$(SRCDIR)/main.c\
				$(SRCDIR)/minishell.c
INCS		=	$(INCDIR)/minishell_types.h\
				$(INCDIR)/minishell_command.h
OBJS		=	$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCS:.c=.o))
DEPS		=	$(patsubst $(SRCDIR)/%,$(DEPDIR)/%,$(SRCS:.c=.d))

#RULES
all : $(TARGET)

$(TARGET) : $(LIBFT) $(OBJS)
	@printf "\nLinking $@...\n"
	@$(CC) $(CFLAGS) $(HDINC) $(OBJS) $(LIBFT) -o $@
	@printf "All done\n"

$(LIBFT) :
	@printf "Compiling libft...\n"
	@make -s -C $(PROJDIR)/libft

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@mkdir -p $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(dir $(@:.o=.d)))
	@printf "Buildind object files...\r"
	@$(CC) $(CFLAGS) $(HDINC) -c $< -o $@ \
		-MMD -MF $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(@:.o=.d))

-include $(DEPS);

clean :
	@printf "Cleaning object files...\n"
	@make -s clean -C $(PROJDIR)/libft
	@rm -rf $(OBJDIR) $(DEPDIR)

fclean : clean
	@printf "Cleaning target files...\n"
	@rm -rf $(LIBFT) $(TARGET)

re : fclean all

.PHONY : all clean fclean re