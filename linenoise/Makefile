NAME = libnoise.a

SRC = linenoise.c

all: $(NAME)
	
$(NAME):
	@gcc -c -Wall -Werror -Wextra $(SRC)
	ar -rcs $(NAME) *.o

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)
