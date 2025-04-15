##
## EPITECH PROJECT, 2025
## B-OOP-400-COT-4-1-arcade-james.gbetchedji
## File description:
## Makefile
##

CC = g++

NAME = arcade

SRC_DIR = srcs

INCLUDE_DIR = includes

LIB_DIR = lib

OBJ_DIR = obj

TEST_DIR = tests

FLAGS = -Wall -Wextra -std=c++20 -MMD -MP -fno-gnu-unique

CFLAGS = -g -I./$(INCLUDE_DIR)

LDFLAGS = -ldl -lm

MAIN = srcs/main/main.cpp srcs/src/init.cpp

CORE_SRC = $(SRC_DIR)/Core/ArcadeCore.cpp 			\
		   $(SRC_DIR)/Core/DisplayGames.cpp 		\
           $(SRC_DIR)/Core/EventManager.cpp 		\
           $(SRC_DIR)/Core/ScoreManager.cpp 		\
           $(SRC_DIR)/Core/Menu/Menu_Ncurses.cpp	\
		   $(SRC_DIR)/Core/Menu/Menu_sdl2.cpp		\
		   $(SRC_DIR)/Core/Menu/Menu_SFML.cpp		\
           $(SRC_DIR)/Utils/Error.cpp

GRAPHICS_SOURCES = $(SRC_DIR)/Graphics/NCurses/NCursesDisplay.cpp \
                   $(SRC_DIR)/Graphics/NCurses/NCursesModule.cpp \
                   $(SRC_DIR)/Graphics/SDL2/SDL2Display.cpp \
                   $(SRC_DIR)/Graphics/SDL2/SDL2Module.cpp \
                   $(SRC_DIR)/Graphics/SFML/SFMLDisplay.cpp \
                   $(SRC_DIR)/Graphics/SFML/SFMLModule.cpp

GAMES_SOURCES = $(SRC_DIR)/Games/Snake/Snake.cpp \
                $(SRC_DIR)/Games/Snake/SnakeModule.cpp \
                $(SRC_DIR)/Games/Nibbler/Nibbler.cpp \
                $(SRC_DIR)/Games/Nibbler/NibblerModule.cpp\
                $(SRC_DIR)/Games/Pacman/PacmanModule.cpp\
                $(SRC_DIR)/Games/Pacman/Pacman.cpp



TEST_SOURCES = $(TEST_DIR)/test.cpp

CORE_OBJ = $(CORE_SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
GRAPHICS_OBJ = $(GRAPHICS_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
GAMES_OBJ = $(GAMES_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_OBJ = $(TEST_SOURCES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/tests/%.o)

GR_LIB = $(LIB_DIR)/arcade_
GA_LIB = $(LIB_DIR)/arcade_


GR_OBJ = $(OBJ_DIR)/Graphics
GA_OBJ = $(OBJ_DIR)/Games

GRAPHICS_LIBS = $(GR_LIB)ncurses.so $(GR_LIB)sdl2.so $(GR_LIB)sfml.so

GAMES_LIBS = $(GA_LIB)snake.so $(GA_LIB)nibbler.so $(GA_LIB)pacman.so

NCURSES_FLAGS = -lncurses
SDL2_FLAGS = -lSDL2 -lSDL2_ttf
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

T_FLAGS = $(NCURSES_FLAGS) $(SDL2_FLAGS) $(SFML_FLAGS) -lcriterion -coverage

# Règles de compilation

all: directories games graphicals core

directories:
	@mkdir -p $(OBJ_DIR)/Core $(OBJ_DIR)/Core/Menu $(OBJ_DIR)/Utils
	@mkdir -p $(OBJ_DIR)/Graphics/SDL2 $(OBJ_DIR)/Graphics/SFML
	@mkdir -p $(OBJ_DIR)/Games/Snake $(OBJ_DIR)/Games/Nibbler
	@mkdir -p $(OBJ_DIR)/Games/Pacman
	@mkdir -p $(OBJ_DIR)/tests $(LIB_DIR) $(OBJ_DIR)/Graphics/NCurses
	@mkdir -p /tmp/arcade
	@cp -r assets /tmp/arcade

core: $(NAME)

$(NAME): $(CORE_OBJ)
	@echo "🔨 Building $(NAME)..."
	$(CC) -o $(NAME) $(CORE_OBJ) $(CFLAGS) $(FLAGS) $(SDL2_FLAGS)\
		$(LDFLAGS) $(SFML_FLAGS) $(NCURSES_FLAGS) $(MAIN)

games: $(GAMES_LIBS)

graphicals: $(GRAPHICS_LIBS)

$(GR_LIB)ncurses.so: $(GR_OBJ)/NCurses/NCursesDisplay.o \
	$(GR_OBJ)/NCurses/NCursesModule.o
	@echo "🔨 Building NCurses library..."
	$(CC) -shared -o $@ $^ $(NCURSES_FLAGS) $(FLAGS)

$(GR_LIB)sdl2.so: $(GR_OBJ)/SDL2/SDL2Display.o $(GR_OBJ)/SDL2/SDL2Module.o
	@echo "🔨 Building SDL2 library..."
	$(CC) -shared -o $@ $^ $(SDL2_FLAGS) $(FLAGS)

$(GR_LIB)sfml.so: $(GR_OBJ)/SFML/SFMLDisplay.o $(GR_OBJ)/SFML/SFMLModule.o
	@echo "🔨 Building SFML library..."
	$(CC) -shared -o $@ $^ $(SFML_FLAGS) $(FLAGS)

$(GA_LIB)snake.so: $(GA_OBJ)/Snake/Snake.o $(GA_OBJ)/Snake/SnakeModule.o
	@echo "🔨 Building Snake game..."
	$(CC) -shared -o $@ $^ $(FLAGS)

$(GA_LIB)nibbler.so: $(GA_OBJ)/Nibbler/Nibbler.o \
	$(GA_OBJ)/Nibbler/NibblerModule.o
	@echo "🔨 Building Nibbler game..."
	$(CC) -shared -o $@ $^ $(FLAGS)

$(GA_LIB)pacman.so: $(GA_OBJ)/Pacman/Pacman.o \
	$(GA_OBJ)/Pacman/PacmanModule.o
	@echo "🔨 Building Pacman game..."
	$(CC) -shared -o $@ $^ $(FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "🛠️ Compiling $<..."
	$(CC) -c $< -o $@ $(CFLAGS) $(FLAGS) -fPIC

$(OBJ_DIR)/tests/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "🛠️ Compiling test $<..."
	$(CC) -c $< -o $@ $(CFLAGS) $(FLAGS) -fPIC

TEST_NAME = unit_tests

unit_tests: $(CORE_OBJ:$(OBJ_DIR)/Core/main.o=) $(TEST_OBJ)
	@echo "🧪 Building unit tests..."
	$(CC) -o unit_tests $^ $(CFLAGS) $(FLAGS) $(LDFLAGS) $(T_FLAGS)

tests_run: unit_tests
	@echo "🚀 Running tests..."
	./unit_tests
	gcovr
	gcovr --branches

coverage: tests_run
	@echo "📊 Generating coverage reports..."
	gcovr --html --output coverage.html
	gcovr --xml --output coverage.xml

clean:
	@echo "🧹 Cleaning objects and temp files..."
	rm -rf $(OBJ_DIR)
	rm -f *~ *.log a.out *.gcov *.gcda *.gcno *.html *.xml *.d

fclean: clean
	@echo "🗑️ Full clean (including binaries)..."
	rm -f $(NAME) $(TEST_NAME)
	rm -f $(LIB_DIR)/*.so

re: fclean all


.PHONY: all clean fclean re core games graphicals \
	directories unit_tests tests_run

-include $(CORE_OBJ:.o=.d)
-include $(GRAPHICS_OBJ:.o=.d)
-include $(GAMES_OBJ:.o=.d)
-include $(TEST_OBJ:.o=.d)
