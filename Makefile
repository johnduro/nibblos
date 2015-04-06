
NAME				=		nibbler

SRC_DIR				=		srcs_snake
SRC_TOOLS_DIR		=		tools

INCLUDE_DIR			=		includes
OBJ_DIR				=		objs
TOOLS_OBJ			=		objs_tools


SRC_LIB				=		libraries
LIB_NCURSES			=		lib_ncurses
LIB_OPENGL			=		lib_opengl
LIB_SDLIMAGES		=		lib_sdlimages
LIB_FMOD			=		lib_fmod
LIB_MENU			=		lib_menu

NCURSE_SO			=		NCLIB.so
OPENGL_SO			=		OGLLIB.so
SDLIMAGES_SO		=		SDLIMAGESLIB.so
FMOD_SO				=		FMOD.so
MENU_SO				=		MENU.so


OK					=		"\033[35m"OK"\033[00m"

COMPILER			=		g++
DLFLAGS				=		-shared -fPIC -I $(INCLUDE_DIR)
CFLAGS				=		-std=c++1y -g3 -Wall -Wextra -Werror -c -I $(INCLUDE_DIR)

SRC					=		main.cpp		\
							GameManager.cpp		\
							Player.cpp

SRC_TOOLS			=		Vector2.class.cpp \
							Vector3.class.cpp \
							ft_timer.cpp \
							LibraryException.cpp

OBJ					=		$(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cpp=.o)))
TOOLS				=		$(addprefix $(TOOLS_OBJ)/, $(notdir $(SRC_TOOLS:.cpp=.o)))

all: $(NAME)

$(NAME): | $(TOOLS)  $(OBJ) libz
	$(COMPILER) -o  $@ $(OBJ) $(TOOLS)
	@echo [ $(NAME) ] " compilation ... " $(OK)

# TOOLS

$(TOOLS): | $(TOOLS_OBJ)

$(TOOLS_OBJ):
	mkdir -p $@

$(TOOLS_OBJ)/%.o: $(SRC_TOOLS_DIR)/%.cpp
	$(COMPILER) $(CFLAGS) -o $@ $<

# LIBZ

libz: $(NCURSE_SO) $(SDLIMAGES_SO) $(OPENGL_SO) $(FMOD_SO) $(MENU_SO)
	@echo "Librairies compilation ... " $(OK)

$(NCURSE_SO): $(wildcard $(SRC_LIB)/$(LIB_NCURSES)*.cpp) $(wildcard $(SRC_TOOLS_DIR)/*.cpp)
	$(COMPILER) $(DLFLAGS) -lncurses -o $(NCURSE_SO) $(wildcard $(SRC_LIB)/$(LIB_NCURSES)/*.cpp) $(OBJ_DIR)/Player.o $(TOOLS)
	@echo "Compiling " [ $(NCURSE_SO) ] " ... " $(OK)

$(OPENGL_SO): $(wildcard $(SRC_LIB)/$(LIB_OPENGL)/*.cpp) $(wildcard $(SRC_TOOLS_DIR)/*.cpp)
	$(COMPILER) $(DLFLAGS) -F ~/Library/Frameworks -framework SDL2 -I ~/Library/Frameworks/SDL2.framework/Headers -framework OpenGL -framework SDL2_ttf -framework SDL2_image \
	-o $(OPENGL_SO) $(wildcard $(SRC_LIB)/$(LIB_OPENGL)/*.cpp) $(OBJ_DIR)/Player.o $(TOOLS)
	@echo "Compiling " [ $(OPENGL_SO) ] " ... " $(OK)

$(SDLIMAGES_SO): $(wildcard $(SRC_LIB)/$(LIB_SDLIMAGES)/*.cpp) $(wildcard $(SRC_TOOLS_DIR)/*.cpp)
	$(COMPILER) $(DLFLAGS) -F ~/Library/Frameworks -framework SDL2 -I ~/Library/Frameworks/SDL2.framework/Headers -I ~/Library/Frameworks/SDL2_image.framework/Headers -framework SDL2_image -I ~/Library/Frameworks/SDL2_ttf.framework/Headers -framework SDL2_ttf \
	-o $(SDLIMAGES_SO) $(wildcard $(SRC_LIB)/$(LIB_SDLIMAGES)/*.cpp) $(OBJ_DIR)/Player.o $(TOOLS)
	@echo "Compiling " [ $(SDLIMAGES_SO) ] " ... " $(OK)

$(FMOD_SO): $(wildcard $(SRC_LIB)/$(LIB_FMOD)/*.cpp) $(wildcard $(SRC_TOOLS_DIR)/*.cpp)
	$(COMPILER) $(DLFLAGS) -L $(SRC_LIB)/$(LIB_FMOD)/lib -lfmod -o $(FMOD_SO) $(wildcard $(SRC_LIB)/$(LIB_FMOD)/*.cpp) $(TOOLS)
	install_name_tool -add_rpath $(SRC_LIB)/$(LIB_FMOD)/lib $(FMOD_SO)
	@echo "Compiling " [ $(FMOD_SO) ] " ... " $(OK)

$(MENU_SO): $(wildcard $(SRC_LIB)/$(LIB_MENU)*.cpp) $(wildcard $(SRC_TOOLS_DIR)/*.cpp)
	$(COMPILER) $(DLFLAGS) -lncurses -o $(MENU_SO) $(wildcard $(SRC_LIB)/$(LIB_MENU)/*.cpp) $(TOOLS)
	@echo "Compiling " [ $(MENU_SO) ] " ... " $(OK)

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
	rm -f $(SDLIMAGES_SO)
	rm -f $(FMOD_SO)
	rm -f $(MENU_SO)

clean: toolsClean
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean libClean
	rm -f $(NAME)

re: fclean all
