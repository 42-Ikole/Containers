# **************************************************************************** #
#                                                                              #
#       .------..------..------..------..------..------..------..------.       #
#       |M.--. ||A.--. ||K.--. ||E.--. ||F.--. ||I.--. ||L.--. ||E.--. |       #
#       | (\/) || (\/) || :/\: || (\/) || :(): || (\/) || :/\: || (\/) |       #
#       | :\/: || :\/: || :\/: || :\/: || ()() || :\/: || (__) || :\/: |       #
#       | '--'M|| '--'A|| '--'K|| '--'E|| '--'F|| '--'I|| '--'L|| '--'E|       #
#       `------'`------'`------'`------'`------'`------'`------'`------'       #
#                                                                              #
#                    Kingmar  |  https://github.com/K1ngmar                    #
#                                                                              #
# **************************************************************************** #

NAME		=	containers

CC			=	clang++

FLAGS		=	-std=c++98 -pedantic -Wall -Werror -Wextra $(HEADER_LOC)

DEBUG_FLAGS	=	-g -fsanitize=address

SRC			=	main.cpp

HEADER_LOC	=	-I deque/			\
				-I iterator/		\
				-I list/			\
				-I map/				\
				-I multimap/		\
				-I priority_queue/	\
				-I queue/			\
				-I set/				\
				-I stack/			\
				-I unordered_map/	\
				-I vector/

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
