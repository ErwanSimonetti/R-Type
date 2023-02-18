##
## EPITECH PROJECT, 2022
## B-OOP-400-PAR-4-1-arcade-timothee.de-boynes
## File description:
## Makefile
##

CXX		=	g++ -std=c++17

INC		=	-I include/ -I ../ECS/include -I ../ECS/include/components -I ../utils/

# SFML

NAME_SFML	=	sfml.so

SRC_SFML	=	src/SFML.cpp

OBJ_SFML	=	$(SRC_SFML:.cpp=.o)

LDFLAGS_SFML	=	-fPIC -shared -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio



all:		$(NAME_SFML)

# $(NAME):		$(OBJ)
# 		$(CXX) -o $(NAME) $(OBJ) $(INC) $(LDFLAGS) -g3


# LIBS

$(NAME_SFML): 
	$(CXX) $(SRC_SFML) -o $(NAME_SFML) $(INC) $(LDFLAGS_SFML)
