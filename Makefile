.PHONY:  all clean fclean re

CXX := g++

CXXFLAGS := -c -Wall -Wextra -Werror -g3 -I include

FILES := $(shell find src -name '*.cpp')

SRC := $(addprefix src/, $(FILES))

OBJ := $(FILES:src/%.cpp=obj/%.o)

NAME := ft_retro 

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -lncurses -o $@

obj/%.o: src/%.cpp
	mkdir -p obj
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all