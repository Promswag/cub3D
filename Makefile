NAME			= cub3D
INC_DIR			= ./include/
SRC_DIR			= ./src/
OUT_DIR			= ./obj/

SRC				= 	main.c \
					bonus.c \
					get_next_line.c \
					get_next_line_utils.c \
					utils.c \
					inputs.c \
					movements.c \
					textures.c \
					raycaster.c \
					raycaster_utils.c \
					draw.c \
					minimap.c \
					door.c \
					doorlst.c \
					pars/check_map.c \
                    pars/parsing.c \
                   	pars/wall_inspect.c \
                   	pars/create_tab.c \
                   	pars/pars_texture.c \
                   	pars/fc_texture.c \
                   	pars/pars_utils.c \

SRCC			= ${addprefix ${SRC_DIR}, ${SRC}}
BSRCC			= ${SRCC:${SRC_DIR}bonus.c=${SRC_DIR}bonus_bonus.c}
OBJS			= ${SRCC:%.c=${OUT_DIR}%.o}
BOBJS			= ${BSRCC:%.c=${OUT_DIR}%.o}			
INCLUDE			= -I${INC_DIR}
MLX				= -L MLX42 -lmlx42
LIBFT			= -L libft -lft
GLFW			= -L/Users/${USER}/goinfre/homebrew/Cellar/glfw/3.3.8/lib -lglfw

CC				= gcc
CFLAGS			= -g -Wall -Wextra 
# CFLAGS			+= -Werror
CFLAGS			+= -fsanitize=address
MKDIR			= mkdir -p
RM				= rm -rf

all:

${NAME}: ${OBJS}
	make -C libft
	make -C MLX42
#	@${CC} libmlx42.a -lglfw -L/Users/${USER}/goinfre/homebrew/Cellar/glfw/3.3.8/lib -o ${NAME} ${LIBFT} ${INCLUDE} ${OBJS} ${CFLAGS}
	@${CC} ${MLX} ${GLFW} -o ${NAME} ${LIBFT} ${INCLUDE} ${OBJS} ${CFLAGS}

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

bonus: ${BOBJS}
	make -C libft
	make -C MLX42
	@${CC} ${MLX} ${GLFW} -o ${NAME} ${LIBFT} ${INCLUDE} ${BOBJS} ${CFLAGS}

.PHONY:	all clean fclean re bonus
