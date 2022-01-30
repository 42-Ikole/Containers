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

DIFF		=	diff.txt

STD			=	tests/std_containers

CC			=	clang++

FLAGS		=	-std=c++98 -pedantic -Wall -Werror -Wextra $(HEADER_LOC)

DEBUG_FLAGS	=	-g -fsanitize=address

TEST_SRC	=	tests/main.cpp					\
				tests/vector_test.cpp			\
				tests/vector_iterator_test.cpp	\
				tests/deque_test.cpp			\
				tests/map_test.cpp				\
				tests/map_iterator_test.cpp		\
				tests/set_test.cpp				\
				tests/set_iterator_test.cpp		\
				tests/stack_test.cpp	

HEADER_LOC	=	-I deque/					\
				-I utility/					\
				-I iterator/				\
				-I lexicographical_compare	\
				-I list/					\
				-I map/						\
				-I pair/					\
				-I multimap/				\
				-I priority_queue/			\
				-I queue/					\
				-I set/						\
				-I sfinae/					\
				-I stack/					\
				-I traits/					\
				-I vector/

TEST_HEADER =	-I tests/

RM 			=	rm -f

all: $(NAME)

$(NAME): test

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(FT)  $(FT).txt
	$(RM) $(STD) $(STD).txt
	$(RM) $(DIFF)

re: fclean all

run: re
	./$(NAME)

test:
	@ clear
	@ printf "\n\033[34mRunning test:\n\033[0m"
	@ $(MAKE) compile_ft
	@ ./$(FT) > $(FT).txt
	@ $(MAKE) compile_std
	@ ./$(STD) > $(STD).txt
	@ diff $(FT).txt $(STD).txt > $(DIFF)

compile_ft: $(FT)

$(FT): $(TEST_SRC)
	@ printf "\n\033[33mcompiling ft::containters\n\n\033[0m"
	@ $(CC) $(FLAGS) $(TEST_HEADER) $(TEST_SRC) -o $(FT)

compile_std: $(STD)

$(STD): $(TEST_SRC)
	@ printf "\n\033[33mcompiling std::containers\n\n\033[0m"
	@ $(CC) $(FLAGS) $(TEST_HEADER) $(TEST_SRC) -D STD -o $(STD)

debug: fclean
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $(SRC) -D DEBUG -o $(NAME)
