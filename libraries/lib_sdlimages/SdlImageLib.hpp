
#ifndef SCENEOPENGL_HPP
#define SCENEOPENGL_HPP

// Includes

// #include <OpenGL/gl.h>
// #include <OpenGL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

// #include "glm/glm.hpp"
#include "IGraphicLib.hpp"
#include "TMap.hpp"

#include "Vector3.class.hpp"

# define BLOCK_SIZE 25

// Classe

class SdlImageLib : IGraphicLib
{
public:

    SdlImageLib();
    ~SdlImageLib();

    void		initLibrary( TMap & map );
    void		closeLibrary( void );
    void		printMap( TMap & map );
    int			getInput( void );
    void		gameOver( std::string toPrint ) const;

private:

	// std::vector<Vector3> * points_high;
	// std::vector<Vector3> * points_down;
	// std::vector<Vector3> * points_left;
	// std::vector<Vector3> * points_right;

	// float		echelle;
	// Vector3		scale;

    std::string		m_titreFenetre;
    int				m_largeurFenetre;
    int				m_hauteurFenetre;

	SDL_Surface		*rock;
	SDL_Surface		*food;
	SDL_Surface		*body;
	SDL_Surface		*head_u;
	SDL_Surface		*head_d;
	SDL_Surface		*head_l;
	SDL_Surface		*head_r;

	SDL_Rect food_form;
	SDL_Rect rock_form;
	SDL_Rect snake_form;

	SDL_Rect item_form;

    SDL_Window*		m_fenetre;
	SDL_Surface*	m_windowsurface;    // SDL_GLContext	m_contexteOpenGL;
    SDL_Event		m_evenements;

    // bool		initialiserFenetre();
    // bool		initGL();

   // Vector3		setColor(float height, float echelle);
   // void			drawDot(Vector3 p);
   // void			drawLine(Vector3 p1, Vector3 p2);
   // void			drawTriangles(Vector3 p1, Vector3 p2, Vector3 p3, float echelle);
   // void			drawQuad(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4);
   // float*   	getTheFucknColor(float r, float g, float b, float a) const;
   // void     	drawVox(Vector3 p, int type) const;
   // void     	drawFace(Vector2 a, Vector2 b, Vector2 c, Vector2 g);
};

extern "C" {
	SdlImageLib		*createLib( void );
	void			deleteLib( SdlImageLib * lib );
}

#endif
