g++ -shared -fPIC -I . -I tools/ -lncurses -o NCLIB.so libz/NCurseLib.cpp tools/Vector2.class.cpp

g++ -shared -fPIC -I . -I tools/ -F ~/Library/Frameworks -framework SDL2 -I ~/Library/Frameworks/SDL2.framework/Headers -framework OpenGL -o NGL.so libz/SceneOpenGL.cpp tools/Vector2.class.cpp

g++ -std=c++11 *.cpp tools/*.cpp -I tools -I libz -I .
