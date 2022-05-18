#Coucou


NAME = Container
INC_DIR = containers
FLAGS = -Wall -Wextra -Werror -I. -g -ferror-limit=5
DEFINE_FT = -DUSING_STD=0
DEFINE_STD = -DUSING_STD=1
STD = -std=c++98
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

re_test: re test

test : all
	./$(NAME)

test_leaks : all
	valgrind --leak-check=full --track-origins=yes ./$(NAME)

test_massif : all
	valgrind --tool=massif --time-unit=B ./$(NAME)
	ms_print massif.out.*
	rm massif.out.*

.PHONY : all re fclean clean test test_leaks
