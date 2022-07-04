NAME	=	philo_bonus

SRCS	=	args_bonus.c \
			eat_bonus.c \
			finish_bonus.c \
			ft_atoi_bonus.c \
			init_bonus.c \
			philo_bonus.c \
			put_forks_bonus.c \
			routine_bonus.c \
			sleep_bonus.c \
			take_forks_bonus.c \
			think_bonus.c \
			time_bonus.c \
			utils_bonus.c

HEADER	=	philo_bonus.h

OBJS	=	${SRCS:%.c=%.o}

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

.PHONY	:	all clean fclean re

all		:	${NAME}

%.o 	:	%.c ${HEADER}
			${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean	:
			${RM} ${OBJS}

fclean	:	clean
			${RM} ${NAME}

re		:	fclean all
