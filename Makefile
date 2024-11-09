# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 18:16:07 by uzanchi           #+#    #+#              #
#    Updated: 2024/11/09 21:30:24 by uzanchi          ###   ########.fr        #
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
BOLD	=	\033[1m

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
OBJS	=	$(patsubst ${SRCS_DIR}%, ${OBJ_DIR}/%, $(SRCS:.c=.o))

# Rules
all:		project_logo ${OBJ_DIR}
				@make -s ${LIBFT}
				@make -s ${NAME}

${LIBFT}:
				@echo "${CYAN}\nCOMPILING $$(echo ${LIBFT} | tr '[:lower:]' '[:upper:]')${RESET}"
				@if [ -d ${LIBFT_DIR} ]; \
				then git -C ${LIBFT_DIR} pull; \
				else git clone https://github.com/ugozchi/42_Libft.git ${LIBFT_DIR}; \
				fi
				make -C ${LIBFT_DIR}

${NAME}:		entry_message ${OBJS}
				@${CC} ${CFLAGS} ${SRCS} -I${HEAD_DIR} ${LIBFT_DIR}${LIBFT} ${READLINE} -o ${NAME}
				@echo "${YELLOW}\nCompilation complete, ${NAME} executable at the root of the directory${RESET}\n"

${OBJ_DIR}:
				@if [ ! -d "${OBJ_DIR}" ]; \
				then mkdir -p "${OBJ_DIR}"; \
				fi

$(OBJ_DIR)/%.o:	$(SRCS_DIR)%.c
				@mkdir -p $(dir $@)
				@printf "Compiling $(notdir $<)"; \
				${CC} ${CFLAGS} -I${HEAD_DIR} -c $< -o $@; \
				printf "${GREEN}"; \
				printf " ${OK}\n"; \
				printf "${RESET}"; 


clean:
				@make -sC ${LIBFT_DIR} clean >/dev/null 2>&1
				@if [ ! -d "${OBJ_DIR}" ]; \
				then \
					echo "Repo already clean"; \
				else \
					echo "Removing all .o files"; \
					rm -r ${OBJ_DIR}; \
				fi

fclean:			clean
				@make -sC ${LIBFT_DIR} fclean >/dev/null 2>&1
				@echo "Removing ${NAME} and ${LIBFT} files from root"
				@rm -f ${NAME} ${LIBFT}

re:				fclean all

project_logo:
	@echo "																						   "
	@echo "${ROSE}   ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗        ${RESET}"
	@echo "${ROSE}   ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║        ${RESET}"
	@echo "${ROSE}   ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║        ${RESET}"
	@echo "${ROSE}   ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║        ${RESET}"
	@echo "${ROSE}   ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗   ${RESET}"
	@echo "${ROSE}   ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝   ${RESET}"
	@echo "			a 42 Project by MOTYLEWSKI Melina & ZANCHI Ugo								   "

entry_message:
				@echo "${CYAN}\nCOMPILING $$(echo ${NAME} | tr '[:lower:]' '[:upper:]')\n${RESET}${BOLD}Compiling necessary .o files out of ${SRC_NR} .c files in total${RESET}"

.PHONY:			all clean fclean re project_logo entry_message