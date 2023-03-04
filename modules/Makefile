##
## EPITECH PROJECT, 2023
## R-Type
## File description:
## Makefile
##

CXX				=	g++ -std=c++17

INC				=	-I include -I ../utils -I ../ECS/include -I ../utils/JSON -I ../ECS/include/components

INC_GRAPHICS	=	-I graphics

INC_GAMES		=	-I games


#---------- GRAPHICS ----------#

# SFML

NAME_SFML		=	sfml.so

SRC_SFML		=	graphics/SFML/src/SFML.cpp \
					../utils/JSON/ReadJson.cpp \
					graphics/Particle.cpp
					

OBJ_SFML		=	$(SRC_SFML:.cpp=.o)

INC_SFML		=	$(INC_GRAPHICS) -I graphics/SFML/include

LDFLAGS_SFML	=	-fPIC -shared -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio -ljsoncpp -lraylib 

# RAYLIB

NAME_RAYLIB	=	raylib.so

SRC_RAYLIB	=	graphics/Raylib/src/Raylib.cpp \
				graphics/Raylib/src/RaylibWindow.cpp \
				graphics/Particle.cpp \
				../utils/JSON/ReadJson.cpp

OBJ_RAYLIB	=	$(SRC_RAYLIB:.cpp=.o)

INC_RAYLIB		=	$(INC_GRAPHICS) -I graphics/Raylib/include

LDFLAGS_RAYLIB	=	-fPIC -shared -lraylib -ljsoncpp -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio -ljsoncpp


#---------- GAMES ----------#

# RTYPE

NAME_RTYPE		=	rtype.so

SRC_RTYPE		=	games/RTYPE_game/src/Rtype.cpp \
					../ECS/src/registry.cpp \
					../ECS/src/FollowPath.cpp \

OBJ_RTYPE		=	$(SRC_RTYPE:.cpp=.o)

INC_RTYPE		=	$(INC_GAMES) -I games/RTYPE_game/include -fPIC -shared


#---------- RULES ----------#

all:		sfml raylib rtype

graphic:	sfml raylib

game:		rtype

sfml:		$(NAME_SFML)

rtype:		$(NAME_RTYPE)

raylib:		$(NAME_RAYLIB)

clean: 
	rm *.so

re: clean all


$(NAME_SFML):	
	$(CXX) $(SRC_SFML) -o $(NAME_SFML) $(INC) $(INC_SFML) $(LDFLAGS_SFML)

$(NAME_RTYPE):
	$(CXX) $(SRC_RTYPE) -o $(NAME_RTYPE) $(INC) $(INC_RTYPE)

$(NAME_RAYLIB): 
	$(CXX) $(SRC_RAYLIB) -o $(NAME_RAYLIB) $(INC) $(INC_RAYLIB) $(LDFLAGS_RAYLIB)