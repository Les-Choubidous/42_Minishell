# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 18:16:07 by uzanchi           #+#    #+#              #
#    Updated: 2024/11/09 20:55:43 by uzanchi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Compiler targets and librairies
NAME		=	minishell
CC			=	cc 
CFLAGS		=	-Wall -Werror -Wextra -g -fsanitize=address
LIBFT		=	libft.a

#Directories
SRC_DIR		=	./sources/
HEAD_DIR	=	./includes/
LIBFT_DIR	=	./libft/
OBJ_DIR		=	${SRC_DIR}.o

#Colours, symbols and utils
RESET	=	\033[0m
BLACK	=	\033[0;30m
RED		=	\033[0;31m
GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
BLUE	=	\033[0;34m
PURPLE	=	\033[1;35m
CYAN	=	\033[1;36m
WHITE	=	\033[0;37m
ROSE	=	\033[38;5;216m

# Styles (To change a style, you have to change the "0" after the open square bracket "[" in "Colors" to the following numbers.)
# NORMAL = 0
# BOLD = 1
# LOW INTENSITY = 2
# ITALIC = 3
# UNDERLINED = 4
# BLINKING = 5
# INVERTED/UNDERLINE = 7
# HIDDEN = 8
# CROSSED OUT = 9 

# Symbols
OK		=	✓
FAIL	=	✗
INFO	=	ⓘ
CLEAN	=	♻
TRASH	=	🗑

# Sources
SRC		=	0_utils/... \
			1_lexer/... \
			2_parser/... \
			3_executer/... \
			4_builtins/... \
			5_free/... \
			main.c

SRCS	=	$(addprefix ${SRCS_DIR}, ${SRC})
SRC_NB	=	$(words ${SRCS})

# Objects

project_logo:
	@echo "${ROSE}   ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗        ${RESET}"
	@echo "${ROSE}   ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║        ${RESET}"
	@echo "${ROSE}   ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║        ${RESET}"
	@echo "${ROSE}   ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║        ${RESET}"
	@echo "${ROSE}   ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗   ${RESET}"
	@echo "${ROSE}   ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝   ${RESET}"
