g++ -shared -fPIC -I . -I tools/ -lncurses -o NCLIB.so libz/NCurseLib.cpp tools/Vector2.class.cpp

g++ -shared -fPIC -I . -I tools/ -F ~/Library/Frameworks -framework SDL2 -I ~/Library/Frameworks/SDL2.framework/Headers -framework OpenGL -o NGL.so libz/SceneOpenGL.cpp tools/Vector2.class.cpp tools/Vector3.class.cpp

g++ -std=c++11 *.cpp tools/*.cpp -I tools -I libz -I .

il faut que tu telecharge la SDL2.dmg du site SDL
et tu met le dossier SDL2.framework dans Library/Frameworks

g++ -I inc -L lib -lfmod test.cpp
install_name_tool -add_rpath ./ a.out
