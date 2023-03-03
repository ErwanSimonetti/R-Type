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
					../utils/JSON/ReadJson.cpp
					

OBJ_SFML		=	$(SRC_SFML:.cpp=.o)

INC_SFML		=	$(INC_GRAPHICS) -I graphics/SFML/include

LDFLAGS_SFML	=	-fPIC -shared -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio -ljsoncpp

# RAYLIB

NAME_RAYLIB	=	raylib.so

SRC_RAYLIB	=	graphics/Raylib/src/Raylib.cpp \
				graphics/Raylib/src/RaylibWindow.cpp \
				../utils/JSON/ReadJson.cpp

OBJ_RAYLIB	=	$(SRC_RAYLIB:.cpp=.o)

INC_RAYLIB		=	$(INC_GRAPHICS) -I graphics/Raylib/include

LDFLAGS_RAYLIB	=	-fPIC -shared -lraylib -ljsoncpp


#---------- GAMES ----------#

# RTYPE

NAME_RTYPE		=	rtype.so

SRC_RTYPE		=	games/RTYPE_game/src/Rtype.cpp \
					../ECS/src/registry.cpp \
					../ECS/src/FollowPath.cpp \

OBJ_RTYPE		=	$(SRC_RTYPE:.cpp=.o)

INC_RTYPE		=	$(INC_GAMES) -I games/RTYPE_game/include -fPIC -shared

# OTHERG

NAME_OTHERG		=	otherg.so

SRC_OTHERG		=	games/Other_game/src/OtherGame.cpp \
					../ECS/src/registry.cpp \
					../ECS/src/FollowPath.cpp \

OBJ_OTHERG		=	$(SRC_OTHERG:.cpp=.o)

INC_OTHERG		=	$(INC_GAMES) -I games/Other_game/include -fPIC -shared


#---------- RULES ----------#

all:		sfml raylib rtype otherg

sfml:		$(NAME_SFML)

raylib:		$(NAME_RAYLIB)

rtype:		$(NAME_RTYPE)

otherg:		$(NAME_OTHERG)

clean: 
	rm *.so

re: clean all


$(NAME_SFML):	
	$(CXX) $(SRC_SFML) -o $(NAME_SFML) $(INC) $(INC_SFML) $(LDFLAGS_SFML)


$(NAME_RAYLIB): 
	$(CXX) $(SRC_RAYLIB) -o $(NAME_RAYLIB) $(INC) $(INC_RAYLIB) $(LDFLAGS_RAYLIB)

$(NAME_RTYPE):
	$(CXX) $(SRC_RTYPE) -o $(NAME_RTYPE) $(INC) $(INC_RTYPE)

$(NAME_OTHERG):
	$(CXX) $(SRC_OTHERG) -o $(NAME_OTHERG) $(INC) $(INC_OTHERG)

