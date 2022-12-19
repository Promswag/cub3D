# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 10:13:56 by gbaumgar          #+#    #+#              #
#    Updated: 2022/12/16 12:45:19 by gbaumgar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a
INC_DIR 		= ./include/
SRC_DIR 		= ./src/
OUT_DIR			= ./obj/

SRC				=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c\
					ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c\
					ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c\
					ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
					ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
					ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
					ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

SRCC			= ${addprefix ${SRC_DIR}, ${SRC}}
OBJS			= ${SRCC:%.c=${OUT_DIR}%.o}
INCLUDE			= -I${INC_DIR}

AR				= ar rc
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
MKDIR			= mkdir -p
RM				= rm -rf

all: ${NAME}

$(NAME): ${OBJS}
	@${AR} ${NAME} ${OBJS} 

${OUT_DIR}%.o: %.c Makefile
	@${MKDIR} ${OUT_DIR}
	@${MKDIR} ${@D}
	@${CC} ${CFLAGS} ${INCLUDE} $< -c -o $@

clean:
	@${RM} ${OBJS}
	@${RM} ${OUT_DIR}

fclean:	clean
	@${RM} ${NAME}

re: fclean ${NAME}

bonus:	all

.PHONY:	all clean fclean re bonus
