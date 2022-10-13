NAME	=	libnet.so
CFLAGS  =       -W  -Wextra -Wall
OBJ	=	$(SRC:.cpp=.o)
FLAGS 	=	lsfml-graphics -lsfml-window -lsfml-system
INCLUDES	+=	-I./include/

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(OBJ) $(INCLUDES) $(TESTFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)	\
	rm -f *~	\
	rm -f *#	\

re:	fclean clean all

.PHONY:	all re clean fclean
