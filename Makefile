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

DEBUG_FLAGS	=	-g -fsanitize=address

SRC			=	main.cpp

TEST_SRC	=	tests/main.cpp \
				tests/vector_test.cpp \
				tests/vector_iterator_test.cpp \
				tests/deque_test.cpp

HEADER_LOC	=	-I deque/			\
				-I utility/			\
				-I iterator/		\
				-I list/			\
				-I map/				\
				-I pair/			\
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
	@ clear
	@ printf "\n\033[33mcompiling ft::containters\n\n\033[0m"
	@ $(CC) $(FLAGS) $(TEST_HEADER) $(TEST_SRC) -o $(FT)
	@ ./$(FT) > $(FT).txt
	@ printf "\n\033[33mcompiling std::containers\n\n\033[0m"
	@ $(CC) $(FLAGS) $(TEST_HEADER) $(TEST_SRC) -D STD -o $(STD)
	@ ./$(STD) > $(STD).txt
	diff $(FT).txt $(STD).txt

debug: fclean
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $(SRC) -D DEBUG -o $(NAME)
