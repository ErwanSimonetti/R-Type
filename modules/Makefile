##
## EPITECH PROJECT, 2023
## R-Type
## File description:
## Makefile
##

CXX				=	g++ -std=c++17

INC				=	-I include/ -I ../ECS/include -I ../ECS/include/components -I ../utils/

INC_GRAPHICS	=	-I graphics

INC_GAMES		=	-I games


#---------- GRAPHICS ----------#

# SFML

NAME_SFML		=	sfml.so

SRC_SFML		=	graphics/SFML/src/SFML.cpp

OBJ_SFML		=	$(SRC_SFML:.cpp=.o)

INC_SFML		=	$(INC_GRAPHICS) -I graphics/SFML/include

LDFLAGS_SFML	=	-fPIC -shared -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio


#---------- GAMES ----------#

# RTYPE

NAME_RTYPE		=	rtype.so

SRC_RTYPE		=	games/RTYPE_game/src/Rtype.cpp \
					../ECS/src/registry.cpp \
					../ECS/src/FollowPath.cpp \

OBJ_RTYPE		=	$(SRC_RTYPE:.cpp=.o)

INC_RTYPE		=	$(INC_GAMES) -I games/RTYPE_game/include -fPIC -shared


#---------- RULES ----------#

all:		sfml rtype

sfml:		$(NAME_SFML)

rtype:		$(NAME_RTYPE)

clean: 
	rm *.so

re: clean all


$(NAME_SFML):	
	$(CXX) $(SRC_SFML) -o $(NAME_SFML) $(INC) $(INC_SFML) $(LDFLAGS_SFML)

$(NAME_RTYPE):
	$(CXX) $(SRC_RTYPE) -o $(NAME_RTYPE) $(INC) $(INC_RTYPE)
# $(NAME):		$(OBJ)
# 		$(CXX) -o $(NAME) $(OBJ) $(INC) $(LDFLAGS) -g3

