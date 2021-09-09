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

FT			=	tests/ft_containers

STD			=	tests/std_containers

CC			=	clang++

FLAGS		=	-std=c++98 -pedantic -Wall -Werror -Wextra $(HEADER_LOC)

TEST_FLAGS	=	-std=c++11 -pedantic -Wall -Wextra -Werror $(HEADER_LOC) $(TEST_HEADER)

DEBUG_FLAGS	=	-g -fsanitize=address

SRC			=	main.cpp

TEST_SRC	=	tests/main.cpp \
				tests/vector_test.cpp

HEADER_LOC	=	-I deque/			\
				-I iterator/		\
				-I list/			\
				-I map/				\
				-I multimap/		\
				-I priority_queue/	\
				-I queue/			\
				-I set/				\
				-I sfinae/			\
				-I stack/			\
				-I unordered_map/	\
				-I vector/

TEST_HEADER =	-I tests/

RM 			=	rm -f

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(FT)  $(FT).txt
	$(RM) $(STD) $(STD).txt 

re: fclean all

run: re
	./$(NAME)

test: re
	@clear
	@$(CC) $(TEST_FLAGS) $(DEBUG_FLAGS) $(TEST_SRC) -o $(FT)
	@./$(FT) > $(FT).txt
	@$(CC) $(TEST_FLAGS) $(TEST_SRC) -D STD -o $(STD)
	@./$(STD) > $(STD).txt
	diff $(FT).txt $(STD).txt


debug: fclean
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $(SRC) -D DEBUG -o $(NAME)
