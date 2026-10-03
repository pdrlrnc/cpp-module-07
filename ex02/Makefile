# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/12 13:00:56 by pedde-so          #+#    #+#              #
#    Updated: 2026/09/15 15:42:00 by pdrlrnc          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = arr
SRC         = main.cpp
OBJ_DIR	    = obj/
OBJ         = $(patsubst %.cpp, $(OBJ_DIR)%.o, $(SRC))

COMPILER    = c++
CFLAGS      = -Wall -Wextra -Werror -g -std=c++98
RM          = rm -rf

GRAY        = \033[38;5;244m
CURSIVE	   := \033[33;3m
INDIGO     := \033[38;5;057m
DEF_COLOUR  = \033[0m

all: $(NAME)
	@echo "$(GRAY)                    ^...^$(DEF_COLOUR)"
	@echo "$(GRAY)                   <_* *_>$(DEF_COLOUR)"
	@echo "$(GRAY)                     \_/  $(DEF_COLOUR)"
	@echo "$(CURSIVE)$(INDIGO)c++: shooting urself in the foot was never this fun! $(DEF_COLOUR)"

$(NAME): $(OBJ)
	@echo "Linking executable..."
	@$(COMPILER) $(OBJ) -o $@
	@echo "$(NAME) built!"
	-@ctags -R .

$(OBJ_DIR)%.o: %.cpp Array.hpp  | $(OBJ_DIR)
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
clean:
	@echo "Removing object files..."
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "Removing executable..."
	@$(RM) $(NAME)
	@$(RM) tags

re: fclean
	@$(MAKE) --no-print-directory all

.PHONY: all clean fclean re
