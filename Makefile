NAME			= cub3D
INC_DIR			= ./include/
SRC_DIR			= ./src/
OUT_DIR			= ./obj/

SRC				= 	main.c \
					get_next_line.c \
					get_next_line_utils.c \
					utils.c \
					cub3d_minimap.c \
					inputs.c \
					movements.c \

SRCC			= ${addprefix ${SRC_DIR}, ${SRC}}
OBJS			= ${SRCC:%.c=${OUT_DIR}%.o}
INCLUDE			= -I${INC_DIR}
# MLX				= -L. -lmlx42
# GLFW			= -L/Users/gbaumgar/goinfre/homebrew/Cellar/glfw/3.3.8/lib -lglfw
LIBFT			= -L libft -lft

CC				= gcc
CFLAGS			= -g -Wall -Wextra
# CFLAGS			+= -Werror
CFLAGS			+= -fsanitize=address
MKDIR			= mkdir -p
RM				= rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	make -C libft
#	@${CC} ${MLX} ${GLFW} ${NAME} ${LIBFT} ${INCLUDE} ${OBJS} ${CFLAGS}
	@${CC} libmlx42.a -lglfw -L/Users/gbaumgar/goinfre/homebrew/Cellar/glfw/3.3.8/lib -o ${NAME} ${LIBFT} ${INCLUDE} ${OBJS} ${CFLAGS}

${OUT_DIR}%.o: %.c Makefile
	@${MKDIR} ${OUT_DIR}
	@${MKDIR} ${@D}
	@${CC} ${CFLAGS} ${INCLUDE} $< -c -o $@

clean:
	make clean -C libft
	@${RM} ${OBJS}
	@${RM} ${OUT_DIR}

fclean:	clean
	make fclean -C libft
	@${RM} ${NAME}

re: fclean ${NAME}

bonus:	all

.PHONY:	all clean fclean re bonus
