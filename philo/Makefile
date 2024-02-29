NAME      = philo
CC        = cc
CFLAGS    = -Wall -Wextra -Werror -g3 
# -pthread -fsanitize=thread
RM        = rm -f
PRINTF    = ft_printf
FT_PRINTF = ft_printf/libftprintf.a
SRC 	  = source/main.c source/parsing.c source/monitor.c source/utils.c source/routine.c
OBJ       = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c  $< -o $@

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
