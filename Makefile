NAME		=	containers

CC			=	clang++
FLAGS		=	-std=c++98 -pedantic -Wall -Werror -Wextra
DEBUG_FLAGS	=	-g -fsanitize=address
SRC			=	main.cpp

RM 			=	rm -rf

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: re
	./$(NAME)

debug: fclean
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $(SRC) -o $(NAME)