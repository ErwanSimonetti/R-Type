##
## EPITECH PROJECT, 2023
## R-TYPE
## File description:
## Makefile
##

CC =		g++

SRC =		main.cpp

SRCTEST	=	src/tests/sample_test.cpp

OBJ =		$(SRC:.cpp=.o)

NAME =		rtype

NAMETEST	=	tests

CPPFLAGS =	-W -Wall -Wextra -ldl -fno-gnu-unique

TESTFLAGS	=	-lcriterion

all: game

game:
	$(CC) $(CPPFLAGS) $(SRC) -o $(NAME)

tests:
	$(CC) $(TESTFLAGS) $(SRCTEST) -o $(NAMETEST)
	./tests

debug:	CPPFLAGS += -g3
debug:	$(NAME)

clean:
	$(RM) $(OBJ) *~ \#*\#

fclean: clean
	$(RM) -f $(NAME) $(NAMETEST)

re: fclean all

.PHONY: all debug clean fclean re test
