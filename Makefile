NAME	= mini
CC		= gcc
RM 		= rm
CFLAGS	= -Wall -Wextra -Werror -g
#RDIR	= /home/linuxbrew/.linuxbrew/opt/readline
RDIR	= /usr/local/opt/readline
CFLAGS += -I$(RDIR)/include
LDFLAGS	= -L$(RDIR)/lib -lreadline -lhistory -lncurses
SRCDIR	= srcs/
SRCS	= $(wildcard $(SRCDIR)**/*.c)
OBJS	= $(patsubst $(SRCDIR)%.c,$(SRCDIR)%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
				make -C incs/libft/
				make -C incs/gnl/
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) incs/libft/libft.a incs/gnl/gnl.a $(LDFLAGS)

$(OBJDIR)%.o:	$(SRCDIR)%.c
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJS) incs/libft/*.o incs/gnl/*.o

fclean: clean
				$(RM) $(NAME) incs/libft/libft.a incs/gnl/gnl.a

re: fclean all