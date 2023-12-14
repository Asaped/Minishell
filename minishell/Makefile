# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cedmulle <cedmulle@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/14 20:46:48 by cedmulle          #+#    #+#              #
#    Updated: 2023/12/14 21:14:58 by cedmulle         ###   ########.fr        #
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
SRC			= $(wildcard $(SRCDIR)*.c)
OBJ			= $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRC))
# ---------- GNL ---------- #
GL_DIR		= $(INCDIR)gnl/
GL_SRC		= $(wildcard $(GL_DIR)*.c)
GL_OBJ		= $(patsubst $(GL_DIR)%.c,$(OBJDIR)%.o,$(GL_SRC))
GL_LIB		= libgnl.a
# --------- LIBFT --------- #
LF_DIR		= $(INCDIR)libft/
LF_SRC		= $(wildcard $(LF_DIR)*.c)
LF_OBJ		= $(patsubst $(LF_DIR)%.c,$(OBJDIR)%.o,$(LF_SRC))
LF_LIB		= libft.a
# ------ COMPILATION ------ #
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -I$(INCDIR)
LDFLAGS		= -L./lib -lgnl -lft
RM			= rm -f

# ---------------------------------------------------------------------------- #
#                                 Fonctions                                    #
# ---------------------------------------------------------------------------- #
# Règle générale ------------------------------------------------------------- #
all:		$(NAME)

$(NAME):	$(OBJ) $(LF_LIB) $(GL_LIB)
				@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
				@echo "\033[1;36m\"$(NAME)\" compiled\t\t√\033[0m"

# Création de la libft ------------------------------------------------------- #
$(LF_LIB):	$(LF_OBJ)
				@ar rcs $(LF_LIB) $(LF_OBJ)
				@ranlib $(LF_LIB)
				@mkdir -p ./lib/
				@mv $(LF_LIB) ./lib/
				@echo "\033[1;36m\"$(LF_LIB)\" compiled\t\t√\033[0m"

# Création de la gnl --------------------------------------------------------- #
$(GL_LIB):	$(GL_OBJ)
				@ar rcs $(GL_LIB) $(GL_OBJ)
				@ranlib $(GL_LIB)
				@mkdir -p ./lib/
				@mv $(GL_LIB) ./lib/
				@echo "\033[1;36m\"$(GL_LIB)\" compiled\t\t√\033[0m"

# Création des objets -------------------------------------------------------- #
$(OBJDIR)%.o:	$(SRCDIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o:	$(GL_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o:	$(LF_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

# Suppression des fichiers objets -------------------------------------------- #
clean:
				@$(RM) -r $(OBJDIR)
				@echo "\033[1;31mObject files deleted\t\t√\033[0m"

# Suppression de l'éxécutable + clean ---------------------------------------- #
fclean:		clean
				@$(RM) $(NAME)
				@$(RM) -r ./lib
				@echo "\033[1;31m\"$(NAME)\" deleted\t\t√\033[0m"
				@echo "\033[1;31m\"$(LF_LIB)\" deleted\t\t√\033[0m"
				@echo "\033[1;31m\"$(GL_LIB)\" deleted\t\t√\033[0m"

# Suppression de l'éxécutable + clean + recompile ---------------------------- #
re:			fclean all

run:		re
				@./$(NAME)

norme:
			@python3 -m norminette -R CheckDefine $(SRC) $(INCDIR) $(GL_SRC) $(LF_SRC)

leaks:
			@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY:		all clean fclean re norme leaks
