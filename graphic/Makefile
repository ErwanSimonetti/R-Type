##
## EPITECH PROJECT, 2022
## B-OOP-400-PAR-4-1-arcade-timothee.de-boynes
## File description:
## Makefile
##

CXX		=	g++ -std=c++17

INC_SFML		=	-I include/SFML -I ../ECS/include -I ../ECS/include/components -I ../utils/ -I include -I ../utils/JSON

INC_RAYLIB		=	-I include/Raylib -I ../ECS/include -I ../ECS/include/components -I ../utils/ -I include -I ../utils/JSON

# SFML

NAME_SFML	=	sfml.so

SRC_SFML	=	src/SFML.cpp ../utils/JSON/ReadJson.cpp

OBJ_SFML	=	$(SRC_SFML:.cpp=.o)

LDFLAGS_SFML	=	-fPIC -shared -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio -ljsoncpp

# RAYLIB

NAME_RAYLIB	=	raylib.so

SRC_RAYLIB	=	src/Raylib.cpp src/RaylibWindow.cpp ../utils/JSON/ReadJson.cpp

OBJ_RAYLIB	=	$(SRC_RAYLIB:.cpp=.o)

LDFLAGS_RAYLIB	=	-fPIC -shared -lraylib -ljsoncpp



all:		$(NAME_SFML) $(NAME_RAYLIB)

# LIBS

sfml:	$(NAME_SFML)

raylib:	$(NAME_RAYLIB)

clean:
	rm *.so

re: clean all

$(NAME_SFML): 
	$(CXX) $(SRC_SFML) -o $(NAME_SFML) $(INC_SFML) $(LDFLAGS_SFML)

$(NAME_RAYLIB): 
	$(CXX) $(SRC_RAYLIB) -o $(NAME_RAYLIB) $(INC_RAYLIB) $(LDFLAGS_RAYLIB)
