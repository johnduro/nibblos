#ifndef SCENEOPENGL_HPP
#define SCENEOPENGL_HPP

// Includes

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

#include "glm/glm.hpp"
#include "IGraphicLib.hpp"
#include "TMap.hpp"

#include "Vector3.class.hpp"

// Classe

class SceneOpenGL : IGraphicLib
{
    public:

    SceneOpenGL();
    ~SceneOpenGL();

    void	initLibrary( TMap & map );
    void closeLibrary();
    void printMap(TMap &map);
    int  getInput();
    void gameOver( std::string toPrint ) const;

   private:

   std::vector<Vector3> * points_high;
   std::vector<Vector3> * points_down;
   std::vector<Vector3> * points_left;
   std::vector<Vector3> * points_right;

   float   echelle;
	Vector3 scale;

    std::string m_titreFenetre;
    int m_largeurFenetre;
    int m_hauteurFenetre;

    SDL_Window* m_fenetre;
    SDL_GLContext m_contexteOpenGL;
    SDL_Event m_evenements;

    bool initialiserFenetre();
    bool initGL();

   Vector3 setColor(float height, float echelle);
   void drawDot(Vector3 p);
   void drawLine(Vector3 p1, Vector3 p2);
   void drawTriangles(Vector3 p1, Vector3 p2, Vector3 p3, float echelle);
   void drawQuad(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4);
   float*   getTheFucknColor(float r, float g, float b, float a) const;
   void     drawVox(Vector3 p, int type) const;
   void     drawFace(Vector2 a, Vector2 b, Vector2 c, Vector2 g);
};

extern "C" {
	SceneOpenGL		*createLib( void );
	void			deleteLib( SceneOpenGL * lib );
}

#endif
