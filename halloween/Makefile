  MOD		=	`pwd | rev | cut -d "/" -f3 | rev`

  BIN		=	`pwd | rev | cut -d "/" -f1 | rev`
  OUTPUT 	= libprout.so
  FLAG		=	-W -Wall -Wextra -g3

  INCLUDE	=	-I./include/
  SRC		=	$(wildcard src/*.cpp)
  OBJ		=	$(SRC:.cpp=.o)
  LIBPATH	=	-L${HOME}/.froot/lib/
  LIB		=	-lstdc++ -lm -ldl -lpthread -lgcc_s -lavcall -O0 -g3 -ggdb3 -fprofile-arcs -ftest-coverage --coverage -lgcov -fPIC -lsfml-graphics -lsfml-window -lsfml-system

  all:		bin
  bin:		$(OBJ)
		@g++ $(OBJ) -o $(BIN) $(LIBPATH) $(LIB)
		@echo "[OUT] " $(BIN)
		@echo $(BIN) | tr '[:lower:]' '[:upper:]'
  .cpp.o:
		@g++ $(INCLUDE) $(FLAG) -c $< -o $@
		@echo "[G++]" $<
  clean:
		@rm -f $(OBJ)
  fclean:	clean
		@rm -f $(BIN)
  re:		fclean all
  lib:    $(OBJ)
		@g++ -shared  -fprofile-arcs -o $(OUTPUT) $(OBJ) $(LIB) 

  .PHONY: all clean fclean re

  .SUFFIXES: .cpp .o