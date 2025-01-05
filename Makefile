NAME    = mini
CC      = gcc
RM      = rm -f
CFLAGS  = -Wall -Wextra -Werror -g
#RDIR    = /usr/local/opt/readline
RDIR	= /home/linuxbrew/.linuxbrew/opt/readline
CFLAGS += -I$(RDIR)/include
LDFLAGS = -L$(RDIR)/lib -lreadline -lhistory -lncurses

# Dossiers
SRCDIR  = srcs/
OBJDIR  = objs/
LIBFT   = incs/libft/libft.a
GNL     = incs/gnl/gnl.a

# Liste manuelle des fichiers source
SRCS    = \
          srcs/main/main.c \
          srcs/cmd/handle_redirection.c \
          srcs/cmd/set_command_tab.c \
          srcs/signal/signal.c \
          srcs/token/expand.c \
          srcs/token/token_utils.c \
          srcs/token/token.c \
          srcs/init/init.c \
          srcs/utils/free.c \
          srcs/debug/debug.c \
          srcs/env/env.c \
          srcs/exec/exec.c \
          srcs/exec/exec_builtins.c \
          srcs/builtins/cd.c \
          srcs/builtins/echo.c \
          srcs/builtins/env.c \
          srcs/builtins/exit.c \
          srcs/builtins/pwd.c \
          srcs/builtins/export.c \
          srcs/builtins/unset.c

OBJS    = $(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)

# Règle principale
all: $(NAME)

$(NAME): $(OBJS)
	@make -C incs/libft/ --silent
	@make -C incs/gnl/ --silent
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(GNL) $(LDFLAGS)

# Compilation des fichiers objets
$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des objets et des exécutables
clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJDIR)
	@make clean -C incs/libft/ --silent
	@make clean -C incs/gnl/ --silent

fclean: clean
	$(RM) $(NAME)
	@make fclean -C incs/libft/ --silent
	@make fclean -C incs/gnl/ --silent

re: fclean all
