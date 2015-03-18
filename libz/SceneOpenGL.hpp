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

#include "tools/Vector3.class.hpp"

// Classe

class SceneOpenGL
{
    public:

    SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
    ~SceneOpenGL();

    bool initialiserFenetre();
    bool initGL();
    void bouclePrincipale(Vector3 **M, int xMax, int yMax);

   private:

   std::vector<Vector3> * points_high;
   std::vector<Vector3> * points_down;
   std::vector<Vector3> * points_left;
   std::vector<Vector3> * points_right;

	Vector3 scale;

    std::string m_titreFenetre;
    int m_largeurFenetre;
    int m_hauteurFenetre;

    SDL_Window* m_fenetre;
    SDL_GLContext m_contexteOpenGL;
    SDL_Event m_evenements;

   Vector3 setColor(float height, float echelle);
   void drawDot(Vector3 p);
   void drawLine(Vector3 p1, Vector3 p2);
   void drawTriangles(Vector3 p1, Vector3 p2, Vector3 p3, float echelle);
   void drawQuad(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4);
   float*   getTheFucknColor(float r, float g, float b, float a);
   void     drawVox(Vector3 p, int porn, int type);
   void     drawFace(Vector3 a, Vector3 b, Vector3 c, Vector3 g, Vector3 h, float echelle);
};

#endif
