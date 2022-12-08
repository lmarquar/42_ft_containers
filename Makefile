CC			:= c++
CFLAGS		:= -Wall -Werror -Wextra -Wconversion -std=c++98 -g
SRC			:= main.cpp
MY_SRC		:= mymain.cpp MyTester.cpp
NAME		:= ft_containers_test.out
MY_NAME		:= ft_containers_test_mine.out

all: $(MY_NAME)

mytest: $(NAME)

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
