#ifndef SCENEOPENGL_HPP
#define SCENEOPENGL_HPP

// Includes

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
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

    SceneOpenGL( void );
    ~SceneOpenGL( void );

    void	initLibrary( TMap & map );
    void	closeLibrary( void );
    void	printMap( TMap const & map );
    int		getInput( void );
    void	gameOver( std::string toPrint ) const;

private:

	std::vector<Vector3> *		points_high;
	std::vector<Vector3> *		points_down;
	std::vector<Vector3> *		points_left;
	std::vector<Vector3> *		points_right;

    SDL_Rect position;
	SDL_Surface *text;
	TTF_Font *police;
    SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255};

	float   echelle;
	Vector3 scale;

    std::string		m_titreFenetre;
    int				m_largeurFenetre;
    int				m_hauteurFenetre;

    SDL_Window*		m_fenetre;
    SDL_GLContext	m_contexteOpenGL;
    SDL_Event		m_evenements;

    bool			initialiserFenetre( void );
    bool			initGL( void );

	Vector3			setColor(float height, float echelle);
	void			drawDot(Vector3 p);
	void			drawLine(Vector3 p1, Vector3 p2);
	void			drawTriangles(Vector3 p1, Vector3 p2, Vector3 p3, float echelle);
	void			drawQuad(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4);
	float*			getTheFucknColor(float r, float g, float b, float a) const;
	void			drawVox(Vector3 p, int type) const;
	void			drawFace(Vector2 a, Vector2 b, Vector2 c, Vector2 g);
};

extern "C" {
	SceneOpenGL		*createLib( void );
	void			deleteLib( SceneOpenGL * lib );
}

#endif
