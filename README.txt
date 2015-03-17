g++ -shared -fPIC -I . -I tools/ -lncurses -o NCLIB.so libz/NCurseLib.cpp tools/Vector2.class.cpp

g++ *.cpp tools/*.cpp -I tools -I libz -I .
