NAME = webserv

CC = clang++

CFLAGS =	-Wall -Wextra -Werror -std=c++98

HEADER =	Request.hpp \
			parser.hpp \
			Server.hpp \
			ServerUnit.hpp \

SRC = 	start.cpp \
		Request.cpp \
        parser.cpp \
        Server.cpp \
        ServerUnit.cpp \

SRCS = $(SRC)

all: $(NAME)

$(NAME): $(SRCS) $(HEADER)
	@echo "\n"
	@echo "\033[0;32mCompiling $(NAME)..."
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "\n\033[0mDone !"

clean:
	@echo "\nRemoving binaries..."
	@echo "\033[0m"

fclean:
	@echo "\033[0;31m\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\nDeleting trash..."
	@rm -f *.out
	@echo "\033[0m"

re: fclean all

test: all
	./$(NAME)