# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/30 18:20:58 by wxuerui           #+#    #+#              #
#    Updated: 2022/07/31 16:05:32 by wxuerui          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variables

NAME	= tester
GNL_DIR = get_next_line/
CC	= gcc
GNL_HEADER = -I $(GNL_DIR)get_next_line.h
BONUS_GNL_HEADER = -I $(GNL_DIR)get_next_line_bonus.h
HEADER	= -I tester_header.h
CFLAGS	= -Wall -Werror -Wextra
OBJS_DIR	= objs/
BUFF_SIZE	=

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#sources

SRC_FILES	= main gnl utils get_file_content run_tests malloc_count get_result

SRCS	= $(addsuffix .c, $(SRC_FILES))
OBJS	= $(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

########

all:	$(NAME)

$(OBJS_DIR)%.o: %.c
				@$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFF_SIZE) $(GNL_HEADER) $(HEADER) -c $^ -o $@

$(NAME):	mkdir_objs $(OBJS)
			@$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFF_SIZE) $(GNL_HEADER) $(HEADER) -c $(GNL_DIR)get_next_line.c -o $(OBJS_DIR)get_next_line.o
			@$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFF_SIZE) $(GNL_HEADER) $(HEADER) -c $(GNL_DIR)get_next_line_utils.c -o $(OBJS_DIR)get_next_line_utils.o
			@$(CC) $(CFLAGS) $(HEADER) $(GNL_HEADER) -D BUFFER_SIZE=$(BUFF_SIZE) -o $(NAME) $(OBJS_DIR)* -ldl

bonus:	mkdir_objs $(OBJS)
			@$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFF_SIZE) $(GNL_HEADER) $(HEADER) -c $(GNL_DIR)get_next_line_bonus.c -o $(OBJS_DIR)get_next_line_bonus.o
			@$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFF_SIZE) $(GNL_HEADER) $(HEADER) -c $(GNL_DIR)get_next_line_utils_bonus.c -o $(OBJS_DIR)get_next_line_utils_bonus.o
			@$(CC) $(CFLAGS) $(HEADER) $(GNL_HEADER) -D BUFFER_SIZE=$(BUFF_SIZE) -o $(NAME) $(OBJS_DIR)* -ldl

mkdir_objs:
			@mkdir -p $(OBJS_DIR)

clean:
		@rm -rf $(OBJS_DIR)

fclean:	clean
		@rm -rf $(NAME)

re:	fclean all

.PHONY:	all clean fclean re