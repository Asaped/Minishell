# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/14 20:46:48 by cedmulle          #+#    #+#              #
#    Updated: 2023/12/24 12:21:02 by cedmulle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#                                 Variables                                    #
# ---------------------------------------------------------------------------- #

# ------ EXECUTABLES ------ #
NAME		= minishell
# ------ DIRECTORIES ------ #
SRCDIR		= src/
INCDIR		= inc/
OBJDIR		= obj/
# ----- SOURCES FILES ----- #
SRC			= $(wildcard $(SRCDIR)**/*.c)
OBJ			= $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRC))
# --------- LIBFT --------- #
LF_DIR		= $(INCDIR)libft/
LF_SRC		= $(wildcard $(LF_DIR)*.c)
LF_OBJ		= $(patsubst $(LF_DIR)%.c,$(OBJDIR)%.o,$(LF_SRC))
LF_LIB		= libft.a
# ------ COMPILATION ------ #
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -I$(INCDIR)
LDFLAGS		= -L./lib -lft -I./inc/readline -L./inc/readline -lreadline -lhistory -lncurses
RM			= rm -f
# --------- COLORS -------- #
RST			= \033[0m
R			= \033[1;31m
G			= \033[1;32m
Y			= \033[1;33m
B			= \033[1;34m
M			= \033[1;35m
C			= \033[1;36m
W			= \033[1;37m

# ---------------------------------------------------------------------------- #
#                                 Fonctions                                    #
# ---------------------------------------------------------------------------- #
# Règle générale ------------------------------------------------------------- #
all:		load $(LOAD) $(NAME)

$(NAME):	$(OBJ) $(LF_LIB)
				@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
				@clear
# unicode ici
				@echo "                                                                          $(RST)"
				@echo "                                                                          $(RST)"
				@echo "    $(G)███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗        $(RST)"
				@echo "    $(G)████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║        $(RST)"
				@echo "    $(G)██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║        $(RST)"
				@echo "    $(G)██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║        $(RST)"
				@echo "    $(G)██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗   $(RST)"
				@echo "    $(G)╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝   $(RST)"
				@echo "                                                  $(G)BY MOTURKI & CEDMULLE   $(RST)"
				@echo "                                                                          $(RST)"
				@echo "    $(Y)Usage : ./minishell\n\n                                                   $(RST)"

load:
				@echo "$(B)Loading...$(RST)"

# Création de la libft ------------------------------------------------------- #
$(LF_LIB):	$(LF_OBJ)
				@ar rcs $(LF_LIB) $(LF_OBJ)
				@ranlib $(LF_LIB)
				@mkdir -p ./lib/
				@mv $(LF_LIB) ./lib/

# Création des objets -------------------------------------------------------- #
$(OBJDIR)%.o:	$(SRCDIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o:	$(LF_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

# Suppression des fichiers objets -------------------------------------------- #
clean:
				@$(RM) -r $(OBJDIR)
				@echo "$(R)Object files deleted\t\t√$(RST)"

# Suppression de l'éxécutable + clean ---------------------------------------- #
fclean:		clean
				@$(RM) $(NAME)
				@$(RM) -r ./lib
				@echo "$(R)\"$(NAME)\" deleted\t\t√$(RST)"
				@echo "$(R)\"$(LF_LIB)\" deleted\t\t√$(RST)"

# Suppression de l'éxécutable + clean + recompile ---------------------------- #
re:			fclean all

# Extras --------------------------------------------------------------------- #
norme:
			@python3 -m norminette -R CheckDefine $(SRC) $(INCDIR)libft $(INCDIR)minishell.h $(LF_SRC)

.PHONY:		all clean fclean re norme leaks
