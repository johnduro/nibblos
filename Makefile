NAME				=		nibbler

SRC_DIR				=		srcs_snake
SRC_TOOLS_DIR		=		tools

INCLUDE_DIR			=		includes
OBJ_DIR				=		objs
TOOLS_OBJ			=		objs_tools

SRC_LIB				=		libraries
LIB_NCURSES			=		lib_ncurses
LIB_OPENGL			=		lib_opengl
NCURSE_SO			=		NCLIB.so
OPENGL_SO			=		OGLLIB.so

OK					=		"\033[35m"OK"\033[00m"

COMPILER			=		g++
DLFLAGS				=		-shared -fPIC -I $(INCLUDE_DIR)
CFLAGS				=		-std=c++1y -g3 -Wall -Wextra -Werror -c -I $(INCLUDE_DIR)

SRC					=		main.cpp		\
							GameManager.cpp		\
							Player.cpp

SRC_TOOLS			=		Vector2.class.cpp \
							Vector3.class.cpp \
							ft_timer.cpp

OBJ					=		$(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cpp=.o)))
TOOLS				=		$(addprefix $(TOOLS_OBJ)/, $(notdir $(SRC_TOOLS:.cpp=.o)))

all: $(NAME)

$(NAME): | $(TOOLS) libz $(OBJ)
	$(COMPILER) -o  $@ $(OBJ) $(TOOLS)
	@echo [ $(NAME) ] " compilation ... " $(OK)

# TOOLS

$(TOOLS): | $(TOOLS_OBJ)

$(TOOLS_OBJ):
	mkdir -p $@

$(TOOLS_OBJ)/%.o: $(SRC_TOOLS_DIR)/%.cpp
	$(COMPILER) $(CFLAGS) -o $@ $<

# LIBZ

# libz: $(NCURSE_SO) $(OPENGL_SO)
libz: $(NCURSE_SO) $(OPENGL_SO)
	@echo "Librairies compilation ... " $(OK)

$(NCURSE_SO): $(wildcard $(SRC_LIB)/$(LIB_NCURSES)*.cpp) $(wildcard $(SRC_TOOLS_DIR)/*.cpp)
	$(COMPILER) $(DLFLAGS) -lncurses -o $(NCURSE_SO) $(wildcard $(SRC_LIB)/$(LIB_NCURSES)/*.cpp) $(TOOLS)
	@echo "Compiling " [ $(NCURSE_SO) ] " ... " $(OK)

$(OPENGL_SO): $(wildcard $(SRC_LIB)/$(LIB_OPENGL)/*.cpp) $(wildcard $(SRC_TOOLS_DIR)/*.cpp)
	$(COMPILER) $(DLFLAGS) -F ~/Library/Frameworks -framework SDL2 -I ~/Library/Frameworks/SDL2.framework/Headers -framework OpenGL \
	-o $(OPENGL_SO) $(wildcard $(SRC_LIB)/$(LIB_OPENGL)/*.cpp) $(TOOLS)
	@echo "Compiling " [ $(OPENGL_SO) ] " ... " $(OK)

# OBJ

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(COMPILER) $(CFLAGS) $< -o $@

# CLEAN

toolsClean:
	rm -f $(TOOLS)
	rm -rf $(TOOLS_OBJ)

libClean:
	rm -f $(NCURSE_SO)
	rm -f $(OPENGL_SO)

clean: toolsClean
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean libClean
	rm -f $(NAME)

re: fclean all
