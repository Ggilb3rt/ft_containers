#Coucou


NAME = Container
INC_DIR = containers
FLAGS = -Wall -Wextra -Werror -I. -g
DEFINE_FT = -DUSING_STD=0
DEFINE_STD = -DUSING_STD=1
STD = -std=c++11
COMPIL = c++

DEPS = $(shell find './$(INC_DIR)' -name '*.hpp') #$(INC_DIR)/vector.hpp
SRC = $(shell find './mains' -name '*.cpp')
OBJ = $(SRC:.cpp=.o)


%.o: %.cpp $(DEPS)
	$(COMPIL) $(FLAGS) $(DEFINE_FT) $(STD) -o $@ -c $<

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
