NAME	=	fight
CFLAGS  =       -W  -Wextra -Wall
SRC	=	src/main.cpp
OBJ	=	$(SRC:.cpp=.o)
FLAGS 	=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INCLUDES =	-I./includes/

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(OBJ) $(INCLUDES) $(FLAGS) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)	\
	rm -f *~	\
	rm -f *#	\

re:	fclean clean all

.PHONY:	all re clean fclean
