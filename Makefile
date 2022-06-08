#Coucou


NAME = Container
INC_DIR = containers
FLAGS = -Wall -Wextra -Werror -I. -g -ferror-limit=5
DEFINE_FT = -DUSING_STD=0
STD = -std=c++98
STD11 = -std=c++11
COMPIL = c++

DEPS = $(shell find './$(INC_DIR)' -name '*.hpp')
SRC ?= $(shell find './mains' -name 'main_map.cpp')
OBJ = $(SRC:.cpp=.o)

%.o: %.cpp $(DEPS)
	$(COMPIL) $(FLAGS) $(DEFINE_FT) $(STD11) -o $@ -c $<

.SILENT:
all: $(NAME)

$(NAME): $(OBJ)
	$(COMPIL) $(FLAGS) $(STD11) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

gostd : 
	$(MAKE) DEFINE_FT=-DUSING_STD=1 all

test : all
	./$(NAME)

test_leaks : all
	valgrind --leak-check=full --track-origins=yes ./$(NAME)

test_massif : all
	valgrind --tool=massif --time-unit=B ./$(NAME)
	ms_print massif.out.*
	rm massif.out.*


.PHONY : all re fclean clean test test_leaks test_massif gostd
