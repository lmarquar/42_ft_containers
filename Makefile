CC			:= c++
CFLAGS		:= -Wall -Werror -Wextra -Wconversion -std=c++98 -g
TEST_DIR	:= ./tests/
MAINNAME	:= main.cpp
MY_MAINNAME	:= mymain.cpp MyTester.cpp
SRC			:= $(TEST_DIR)$(MAINNAME)
MY_SRC		:= $(addprefix $(TEST_DIR),$(MY_MAINNAME))
NAME		:= ft_containers_test.out
MY_NAME		:= ft_containers_test_mine.out

all: $(MY_NAME)

intratest: $(NAME)

re: fclean all

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

$(MY_NAME): $(MY_SRC)
	$(CC) $(CFLAGS) $(MY_SRC) -o $(MY_NAME)

clean:

fclean: clean
	rm -rfd $(NAME).dSYM
	rm -f $(NAME)
	rm -rfd $(MY_NAME).dSYM
	rm -f $(MY_NAME)
