# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 18:16:07 by uzanchi           #+#    #+#              #
#    Updated: 2024/11/09 18:24:40 by uzanchi          ###   ########.fr        #
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
