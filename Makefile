NAME			= cub3D
INC_DIR			= ./include/
SRC_DIR			= ./src/
OUT_DIR			= ./obj/

SRC				= 	main.c \

SRCC			= ${addprefix ${SRC_DIR}, ${SRC}}
OBJS			= ${SRCC:%.c=${OUT_DIR}%.o}
INCLUDE			= -I${INC_DIR}

CC				= gcc
CFLAGS			= -g -Wall -Wextra
# CFLAGS			+= -Werror
# CFLAGS			+= -fsanitize=address
MKDIR			= mkdir -p
RM				= rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} -o ${NAME} ${INCLUDE} ${OBJS} ${CFLAGS}

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
