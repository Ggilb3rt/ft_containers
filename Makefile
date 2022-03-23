#Coucou


NAME = Container
INC_DIR = containers
FLAGS = -Wall -Wextra -Werror -I. -g
STD = -std=c++98
COMPIL = c++

DEPS = $(INC_DIR)/vector.hpp
SRC = $(shell find './mains' -name '*.cpp')
OBJ = $(SRC:.cpp=.o)


%.o: %.cpp $(DEPS)
	$(COMPIL) $(FLAGS) $(STD) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJ)
	$(COMPIL) $(FLAGS) $(STD) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

test : all
	./$(NAME)

test_leaks : all
	valgrind --leak-check=full ./$(NAME)

.PHONY : all re fclean clean test test_leaks