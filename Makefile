NAME =		philo

SRCS =		main.c	get_and_init.c	simulate.c	stop_simulation.c	utils.c

OBJS =		$(SRCS:.c=.o)

HEADER =	philosophers.h

RM =		rm -f

CC =		gcc

CFLAGS =	-Wall -Wextra -Werror -pthread

all: 		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $^ -o $@

%.o:		%.c $(HEADER) 
			$(CC) $(CFLAGS) -c $< -o $@

clean:		
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re