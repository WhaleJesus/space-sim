# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sklaps <sklaps@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/11 15:12:46 by sklaps            #+#    #+#              #
#    Updated: 2025/06/11 15:13:04 by sklaps           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= space

CC			= cc
CFLAGS		= -g -Wall -Wextra -Werror -Iinclude -pthread

SRCDIR		= src
OBJDIR		= objs
LIBFTDIR	= libft
LIBFT		= $(LIBFTDIR)/libft.a

SRCFILES	= init.c \
			  input.c \
			  battle.c \
			  free.c \
			  display.c \
			  location.c \
			  read.c \
			  utils.c \
			  get.c \
			  init_location.c \
			  item.c \
			  character.c 

MAINFILE	= main.c

SRC			= $(addprefix $(SRCDIR)/, $(SRCFILES))
MAIN		= $(SRCDIR)/$(MAINFILE)

OBJ			= $(addprefix $(OBJDIR)/, $(SRCFILES:.c=.o))
MAINOBJ		= $(OBJDIR)/$(MAINFILE:.c=.o)

RM			= rm -f
MKDIR		= mkdir -p

# Colors (optional)
GREEN		= \033[0;32m
YELLOW		= \033[38;2;255;255;0m
NEON		= \033[38;5;198m 
NC			= \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(MAINOBJ)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJ) $(MAINOBJ) -o $(NAME)
	@echo "$(GREEN)✔️ Build successful: $(NAME)$(nc)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(RM) $(OBJ)
	$(RM) $(MAINOBJ)
	@echo "$(GREEN)clean done$(NC)"

fclean: clean
	$(RM) $(NAME)
	@echo "$(GREEN)fclean done$(NC)"

re: fclean all

.PHONY: all clean fclean re

